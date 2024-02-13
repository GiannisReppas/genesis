/*
    Genesis - A toolkit for working with phylogenetic data.
    Copyright (C) 2014-2024 Lucas Czech

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation,  either version 3 of the License,  or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not,  see <http://www.gnu.org/licenses/>.

    Contact:
    Lucas Czech <lczech@carnegiescience.edu>
    Department of Plant Biology, Carnegie Institution For Science
    260 Panama Street, Stanford, CA 94305, USA
*/

/**
 * @brief
 *
 * @file
 * @ingroup utils
 */

#include "genesis/utils/math/correlation.hpp"

#include "genesis/utils/math/common.hpp"
#include "genesis/utils/core/std.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <unordered_map>
#include <vector>

namespace genesis {
namespace utils {

// =================================================================================================
//     General Helper Functions
// =================================================================================================

/**
 * @brief Helper function to count the number of unique values in both lists,
 * using only those entris that are finite in both.
 */
size_t kendalls_tau_count_tau_c_m_(
    std::vector<double> const& x,
    std::vector<double> const& y
) {
    // Collect all unique values, counting how often each of them occurs.
    // We need to skip nan values here, as we also omit them in all other calculations.
    std::unordered_map<double, size_t> unique_x;
    std::unordered_map<double, size_t> unique_y;
    assert( x.size() == y.size() );
    for( size_t i = 0; i < x.size(); ++i ) {
        if( std::isfinite(x[i]) && std::isfinite(y[i]) ) {
            ++unique_x[x[i]];
            ++unique_y[y[i]];
        }
    }
    return std::min( unique_x.size(), unique_y.size() );
}

/**
 * @brief Given counts of concordant and discordant pairs, compute the final value,
 * applying the requested adjustments.
 *
 * We take all values as inputs, as in the presence of nan values, these better be computed
 * correclty by the two algorithms directly, instead of inferring, e.g., n from the list size...
 */
double kendalls_tau_method_(
    std::vector<double> const& x, std::vector<double> const& y,
    size_t const concordant, size_t const discordant,
    size_t const n, size_t const n0, size_t const n1, size_t const n2, size_t const n3,
    KendallsTauMethod method
) {
    double tau = std::numeric_limits<double>::quiet_NaN();
    assert( x.size() == y.size() );

    // All invariants of the process. The last one is the important one,
    // where all pairs need to be accounted for.
    assert( n0 == n * (n - 1) / 2 );
    assert( n1 <= n0 && n2 <= n0 );
    assert( n3 <= n1 && n3 <= n2 );
    assert( concordant <= n0 );
    assert( discordant <= n0 );
    assert( n0 == concordant + discordant + n1 + n2 - n3 );
    (void) n3; // Only used for the assertion here.

    // Compute the numerator, common to all tau methods.
    // We first cast to signed int, so that the difference computation is exact,
    // and then cast the results to double, as we are doing a division next.
    double const num = static_cast<int64_t>(concordant) - static_cast<int64_t>(discordant);

    switch( method ) {
        case KendallsTauMethod::kTauA: {
            double const den = concordant + discordant;
            if( den != 0.0 ) {
                tau = num / den;
            }
            break;
        }

        case KendallsTauMethod::kTauB: {
            // Compute the Tau-b denominator via differences in ints, so that they are exact,
            // but then convert to double so that the multiplication does not overflow.
            double const den = std::sqrt(
                static_cast<double>(n0 - n1) * static_cast<double>(n0 - n2)
            );
            if( std::isfinite(den) && den != 0.0 ) {
                tau = num / den;
            }
            break;
        }

        case KendallsTauMethod::kTauC: {
            // Minimum of the number of unique values in x and y.
            double const m = kendalls_tau_count_tau_c_m_( x, y );
            double const den = squared(n) * ( m - 1 ) / m;
            if( std::isfinite(den) && den != 0.0 && m > 0 ) {
                tau = 2.0 * num / den;
            }
            break;
        }

        default: {
            throw std::invalid_argument( "Invalid value for KendallsTauMethod" );
        }
    }

    assert( !std::isfinite(tau) || ( -1.0 <= tau && tau <= 1.0 ));
    return tau;
}

// =================================================================================================
//     Kendall Tau using Knight's Algorithm
// =================================================================================================

/**
 * @brief Helper function for kendalls_tau_correlation_coefficient() to do a merge sort that
 * counts the number of inversions performed.
 */
size_t kendalls_tau_merge_count_(
    std::vector<double>& data, std::vector<double>& temp,
    size_t left, size_t mid, size_t right
) {
    size_t i = left;
    size_t j = mid;
    size_t k = left;
    size_t inversions = 0;

    // Merge sort, counting inversions (as if we were doing bubble sort)
    while( i < mid && j <= right ) {
        if( data[i] <= data[j] ) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
            inversions += mid - i;
        }
    }

    // Copy the remaining elements
    while( i < mid ) {
        temp[k++] = data[i++];
    }
    while( j <= right ) {
        temp[k++] = data[j++];
    }

    // Copy back to the original vector
    for( i = left; i <= right; ++i ) {
        data[i] = temp[i];
    }

    return inversions;
}

/**
 * @brief Helper function for kendalls_tau_correlation_coefficient() to sort a list using merge
 * sort, while counting the number of inversions performed.
 */
size_t kendalls_tau_sort_and_count_(
    std::vector<double>& data, std::vector<double>& temp, size_t left, size_t right
) {
    if( left >= right ) {
        return 0;
    }

    // Count the number of inversions done by merge sorting the list.
    size_t const mid = left + (right - left) / 2;
    size_t const inv_l = kendalls_tau_sort_and_count_( data, temp, left, mid );
    size_t const inv_r = kendalls_tau_sort_and_count_( data, temp, mid + 1, right );
    size_t const inv_m = kendalls_tau_merge_count_( data, temp, left, mid + 1, right );

    return inv_l + inv_r + inv_m;
}

/**
 * @brief Helper for computing hashes of pairs.
 */
struct kendalls_tau_pair_hash_ {
    template <class T1, class T2>
    std::size_t operator () ( std::pair<T1,T2> const& value ) const {
        auto h1 = std::hash<T1>{}(value.first);
        auto h2 = std::hash<T2>{}(value.second);
        return combine_hashes( h1, h2 );
    }
};

/**
 * @brief Helper function to count the number of pairs that have ties.
 */
size_t kendalls_tau_count_tied_pairs_(
    std::vector<std::pair<double, double>> const& pairs
) {
    // Collect all unique values, counting how often each of them occurs.
    // We need to skip nan values here, as we also omit them in all other calculations.
    std::unordered_map<std::pair<double, double>, size_t, kendalls_tau_pair_hash_> unique_counts;
    for( auto val : pairs ) {
        ++unique_counts[val];
    }

    // The number of ties for the purposes of the algorithm needs to account for the duplicates
    // occurring in all combinations of pairs, so we use a triangular number.
    size_t tie_sum = 0;
    for( auto const& pair : unique_counts ) {
        if( pair.second > 1 ) {
            tie_sum += pair.second * (pair.second - 1) / 2;
        }
    }
    return tie_sum;
}

/**
 * @brief Helper function to count the number of tied pairs.
 */
size_t kendalls_tau_count_ties_(
    std::vector<double> const& data
) {
    // Collect all unique values, counting how often each of them occurs.
    // We need to skip nan values here, as we also omit them in all other calculations.
    std::unordered_map<double, size_t> unique_counts;
    for( auto val : data ) {
        if( std::isfinite(val) ) {
            ++unique_counts[val];
        }
    }

    // The number of ties for the purposes of the algorithm needs to account for the duplicates
    // occurring in all combinations of pairs, so we use a triangular number.
    size_t tie_sum = 0;
    for( auto const& pair : unique_counts ) {
        if( pair.second > 1 ) {
            tie_sum += pair.second * (pair.second - 1) / 2;
        }
    }
    return tie_sum;
}

/**
 * @brief Compute Kendall's Tau, expecting clean input without nan values, using Knight's algorithm.
 */
double kendalls_tau_correlation_coefficient_clean_(
    std::vector<double> const& x,
    std::vector<double> const& y,
    KendallsTauMethod method
) {
    assert( x.size() == y.size() );
    if( x.size() < 2 ) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    // Create a vector of indices sorted by the corresponding values in x,
    // breaking ties in x by secondary sort on y.
    size_t const n = x.size();
    std::vector<size_t> rank_x(n);
    std::iota( rank_x.begin(), rank_x.end(), 0 );
    std::sort( rank_x.begin(), rank_x.end(),
        [&]( size_t i, size_t j ) {
            return x[i] == x[j] ? y[i] < y[j] : x[i] < x[j];
        }
    );

    // Create a vector of y values sorted according to x
    std::vector<double> sorted_y(n);
    for( size_t i = 0; i < n; ++i ) {
        sorted_y[i] = y[rank_x[i]];
    }

    // Use merge sort to count inversions in sorted_y, which are discordant pairs.
    // We use a temporary vector for merge sort, to avoid re-allocating memory in each step.
    std::vector<double> temp(n);
    size_t const discordant = kendalls_tau_sort_and_count_( sorted_y, temp, 0, n - 1 );
    assert( std::is_sorted( temp.begin(), temp.end() ));
    temp.clear();

    // We only count the discordant pairs as the number of inversions made in the merge sort above.
    // To get the correct number of concordant pairs, we need to know the ties, including the pairs
    // that are tied in x _and_ y, called n3. This could potentially be inferred from the above
    // sorted lists, but we already have a hash-map based function for this above, and so use that
    // here for simplicity. If this function needs to be more optimized in the future,
    // this is a good place to start.
    std::vector<std::pair<double, double>> pairs;
    for( size_t i = 0; i < x.size(); ++i ) {
        assert( std::isfinite(x[i]) );
        assert( std::isfinite(y[i]) );

        pairs.emplace_back( x[i], y[i] );
    }
    size_t const n3 = kendalls_tau_count_tied_pairs_( pairs );
    pairs.clear();

    // We also compute n0 = number of pairs, n1 and n2 = number of ties in x and y, respectively.
    size_t const n0 = n * (n - 1) / 2;
    size_t const n1 = kendalls_tau_count_ties_(x);
    size_t const n2 = kendalls_tau_count_ties_(y);
    assert( n0 >= n1 && n0 >= n2 );

    // Now we can compute the number of concordant pairs.
    size_t const concordant = n0 - n1 - n2 + n3 - discordant;
    assert( concordant <= n0 );
    assert( discordant <= n0 );

    // Compute the final value, using corrections as needed.
    return kendalls_tau_method_( x, y, concordant, discordant, n, n0, n1, n2, n3, method );
}

double kendalls_tau_correlation_coefficient(
    std::vector<double> const& x,
    std::vector<double> const& y,
    KendallsTauMethod method
) {
    // Errors and boundary cases
    if( x.size() != y.size() ) {
        throw std::invalid_argument(
            "kendalls_tau_correlation_coefficient: Input with differing numbers of elements."
        );
    }

    // In the presence of nan values, we make a copy of the values, omitting pairs with nans.
    // Maybe there is a way to avoid this, but Knight's algorithm uses rank sorting, which gets
    // so much more complicated when values need to be skipped/masked... So for now, this is what
    // we do for simplicity. At least, in the case without nan values, we can avoid the copy.
    size_t nan_count = 0;
    for( size_t i = 0; i < x.size(); ++i ) {
        if( !std::isfinite(x[i]) || !std::isfinite(y[i]) ) {
            ++nan_count;
        }
    }
    if( nan_count > 0 ) {
        assert( nan_count <= x.size() );
        std::vector<double> x_clean;
        std::vector<double> y_clean;
        x_clean.reserve( x.size() - nan_count );
        y_clean.reserve( x.size() - nan_count );
        for( size_t i = 0; i < x.size(); ++i ) {
            if( std::isfinite(x[i]) && std::isfinite(y[i]) ) {
                x_clean.push_back(x[i]);
                y_clean.push_back(y[i]);
            }
        }

        return kendalls_tau_correlation_coefficient_clean_( x_clean, y_clean, method );
    } else {
        return kendalls_tau_correlation_coefficient_clean_( x, y, method );
    }
}

// =================================================================================================
//     Kendall Tau Naive Algorithm
// =================================================================================================

double kendalls_tau_correlation_coefficient_naive(
    std::vector<double> const& x,
    std::vector<double> const& y,
    KendallsTauMethod method
) {
    // Boundary checks.
    if( x.size() != y.size() ) {
        throw std::invalid_argument(
            "kendalls_tau_correlation_coefficient: Input with differing numbers of elements."
        );
    }

    // Count number of pairs for the numerator.
    size_t concordant = 0;
    size_t discordant = 0;

    // n0 = total number of pairs, n1 = ties in x, n2 = ties in y, n3 = ties in both
    size_t n0 = 0;
    size_t n1 = 0;
    size_t n2 = 0;
    size_t n3 = 0;

    // We also count n, the size of the list that was used, i.e. excluding pairs that have nans.
    size_t n = 0;

    // Iterate through all pairs of indices and accumulate concordant and discordant pairs.
    for( size_t i = 0; i < x.size(); ++i ) {
        if( std::isfinite(x[i]) && std::isfinite(y[i]) ) {
            ++n;
        }

        for( size_t j = i + 1; j < x.size(); ++j ) {
            // Skip any pair with non-finite values.
            if(
                !std::isfinite(x[i]) || !std::isfinite(y[i]) ||
                !std::isfinite(x[j]) || !std::isfinite(y[j])
            ) {
                continue;
            }

            // Get pair ordering.
            double const dx = x[i] - x[j];
            double const dy = y[i] - y[j];
            assert( std::isfinite(dx) && std::isfinite(dy) );
            ++n0;

            // Count concordances and ties.
            if( dx == 0 && dy == 0 ) {
                // Both pairs are ties
                ++n1;
                ++n2;
                ++n3;
            } else if( dx == 0 ) {
                ++n1;
            } else if( dy == 0 ) {
                ++n2;
            } else if( dx * dy > 0 ) {
                ++concordant;
            } else if( dx * dy < 0 ) {
                ++discordant;
            } else {
                // We have exhausted all cases that can occur with finite values.
                assert( false );
            }
        }
    }

    // Compute the final value, using corrections as needed.
    return kendalls_tau_method_( x, y, concordant, discordant, n, n0, n1, n2, n3, method );
}

} // namespace utils
} // namespace genesis
