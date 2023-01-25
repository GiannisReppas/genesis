#ifndef GENESIS_POPULATION_WINDOW_CHROMOSOME_ITERATOR_H_
#define GENESIS_POPULATION_WINDOW_CHROMOSOME_ITERATOR_H_

/*
    Genesis - A toolkit for working with phylogenetic data.
    Copyright (C) 2014-2023 Lucas Czech

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Contact:
    Lucas Czech <lczech@carnegiescience.edu>
    Department of Plant Biology, Carnegie Institution For Science
    260 Panama Street, Stanford, CA 94305, USA
*/

/**
 * @brief
 *
 * @file
 * @ingroup population
 */

#include "genesis/population/window/base_window_iterator.hpp"
#include "genesis/population/window/window_view.hpp"

#include <cassert>
#include <functional>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <utility>

namespace genesis {
namespace population {

// =================================================================================================
//     Chromosome Iterator
// =================================================================================================

/**
 * @brief Iterator for traversing each chromosome as a whole, or the entire genome,
 * with an inner WindowView iterator over the positions of each chromosome.
 *
 * With each step of the iteration, an inner WindowView iterator is yielded that traverses all
 * positions on a chromosome of the underlying input data stream (or the whole genome).
 * Then, when incrementing the main iterator, we move forward to the next chromosome (if available).
 *
 * This class is merely meant as a simplification over manually keeping track of the current
 * chromosome, for example when computing a statistic for whole chromosomes, so that those
 * algorithms do not need to take care of when to produce their output.
 * Instead, they can simply use this class, and produce output at each step of the main iterator.
 * This class contains a quite unfortunate amount of boiler plate, but hopefully makes downstream
 * algorithms easier to write.
 *
 * In order to traverse the whole genome at once, instead of iterating over individual chromosomes,
 * use whole_genome(); see there for details.
 *
 * The three functors
 *
 *  * #entry_input_function,
 *  * #chromosome_function, and
 *  * #position_function
 *
 * have to be set in the class prior to starting the iteration for the chromosome iterator.
 * For the whole genome case, only the first of them has to be set, as we internally do not need
 * access to the chromosome and position information of the underlying data iterator.
 * See make_chromosome_iterator() and make_default_chromosome_iterator()
 * for helper functions that take care of this for most of our data types.
 *
 * See BaseWindowIterator for more details on the three functors, the template parameters.
 * This class here however does not derive from the BaseWindowIterator over normal Window%s,
 * but behaves in a similar way - with the exception that it does not produce Window%s in each
 * step of the iteration, as we do not want to keep the positions of a whole chromosome in memory.
 * Hence, instead, it yields a WindowView iterator, directly streaming over the positions of the
 * chromosome, without keeping all data in memory.
 *
 *
 * @see make_chromosome_iterator()
 * @see make_default_chromosome_iterator()
 */
template<class InputIterator, class DataType = typename InputIterator::value_type>
class ChromosomeIterator final : public BaseWindowIterator<
    InputIterator, DataType, ::genesis::population::WindowView<DataType>
>
{
public:

    // -------------------------------------------------------------------------
    //     Typedefs and Enums
    // -------------------------------------------------------------------------

    using WindowViewType = ::genesis::population::WindowView<DataType>;
    using self_type = ChromosomeIterator<InputIterator, DataType>;
    using base_type = BaseWindowIterator<InputIterator, DataType, WindowViewType>;

    // The input types that we take from the underlying iterator over genome positions.
    using InputType         = typename InputIterator::value_type;
    // using Entry             = typename Window::Entry;

    // This class produces an iterator of type WindowView.
    // That WindowView then iterates over the actual values of the input.
    using iterator_category = std::input_iterator_tag;
    using value_type        = WindowViewType;
    using pointer           = value_type*;
    using reference         = value_type&;
    using const_reference   = value_type const&;

    // ======================================================================================
    //      Internal Iterator
    // ======================================================================================

    /**
     * @brief Internal iterator that produces WindowView%s.
     */
    class DerivedIterator final : public BaseWindowIterator<
        InputIterator, DataType, WindowViewType
    >::BaseIterator
    {
    public:

        // -------------------------------------------------------------------------
        //     Constructors and Rule of Five
        // -------------------------------------------------------------------------

        using self_type = typename ChromosomeIterator<
            InputIterator, DataType
        >::DerivedIterator;

        // using base_iterator_type = typename base_type::BaseIterator;
        using base_iterator_type = typename BaseWindowIterator<
            InputIterator, DataType, WindowViewType
        >::BaseIterator;

        // using WindowViewType    = WindowViewType;
        // using Window            = ::genesis::population::Window<DataType>;
        // using Entry             = typename Window::Entry;
        using InputType         = typename InputIterator::value_type;

        using iterator_category = std::input_iterator_tag;
        using value_type        = WindowViewType;
        using pointer           = value_type*;
        using reference         = value_type&;
        using const_reference   = value_type const&;

    private:

        DerivedIterator() = default;

        DerivedIterator(
            ChromosomeIterator const* parent
        )
            : base_iterator_type( parent )
            , parent_( parent )
            // , window_( base_iterator_type::current_, base_iterator_type::end_ )
            // , window_( parent )
        {
            // Edge case check. See Base for details.
            if( ! parent_ ) {
                return;
            }

            // For this particular iterator, where we process the whole chromosome or genome,
            // we are always at the "first" and "last" window of a chromosome, in a sense...
            base_iterator_type::is_first_window_ = true;
            base_iterator_type::is_last_window_ = true;

            // Let's get going. For the whole genome case, we only need to do the init once,
            // and then are done, as the iterator will do the whole thing in one pass, so there
            // never is a second iteration, and hence, increment is never called.
            if( parent_->whole_genome_ ) {
                init_whole_genome_();
            } else {
                increment_chromosome_();
            }
        }

    public:

        ~DerivedIterator() = default;

        DerivedIterator( self_type const& ) = default;
        DerivedIterator( self_type&& )      = default;

        DerivedIterator& operator= ( self_type const& ) = default;
        DerivedIterator& operator= ( self_type&& )      = default;

        friend ChromosomeIterator;

        // -------------------------------------------------------------------------
        //     Internal and Virtual Members
        // -------------------------------------------------------------------------

    private:

        void increment_() override final
        {
            // Check that we are still good. If not, this function being called is likely a user
            // error by trying to increment a past-the-end iterator.
            assert( parent_ );

            // Select which type of increment we need.
            // For whole chromosome, we always reach the end after incrementing,
            // and don't need to do anything, except for singalling that end.
            if( parent_->whole_genome_ ) {
                parent_ = nullptr;
            } else {
                increment_chromosome_();
            }
        }

        void increment_chromosome_()
        {
            // Basic check again.
            assert( parent_ );

            // Move to the next chromosome. This is only important if this increment function
            // is called before the inner window view iterator has finished the whole chromsome,
            // so if for example a break is called within.
            while(
                base_iterator_type::current_ != base_iterator_type::end_ &&
                parent_->chromosome_function( *base_iterator_type::current_ ) == window_.chromosome()
            ) {
                ++base_iterator_type::current_;
            }

            // Now check whether there is any data left. If not, we are done here.
            if( base_iterator_type::current_ == base_iterator_type::end_ ) {
                parent_ = nullptr;
                return;
            }

            // Now we know there is still data, but it belongs to a different chromsome.
            assert( base_iterator_type::current_ != base_iterator_type::end_ );
            assert(
                parent_->chromosome_function( *base_iterator_type::current_ ) != window_.chromosome()
            );

            // We need pointer variables to the iterators and other elements,
            // which can be used as copy-inits for the lambda below.
            // We need to access the underlying iterator throw the self type of the class,
            // see here https://stackoverflow.com/a/28623297/4184258
            // (we could do this in all other instances as well, but it only matters here).
            auto& cur = self_type::current_;
            auto& end = self_type::end_;
            auto const par = parent_;
            auto const chr = parent_->chromosome_function( *base_iterator_type::current_ );

            // Check that we do not have invalid data where chromosomes are repeated.
            if( processed_chromosomes_.count( chr ) > 0 ) {
                throw std::runtime_error(
                    "Chromosome " + chr + " occurs multiple times in the input."
                );
            }
            processed_chromosomes_.insert( chr );

            // We reset the window view, so that it's a new iterator for the new chromosome,
            // starting from the first position, with a fitting increment function.
            window_ = WindowViewType( chr );
            window_.get_next_element = [ &cur, &end, par, chr ]( bool is_first ) mutable -> DataType* {
                // If this is the first call of the function, we are initializing the WindowView
                // with the current entry of the underlying iterator. If not, we first move to the
                // next position (if there is any), before getting the data.
                if( is_first ) {
                    assert( cur != end );
                    return &*cur;
                }

                // Now we are in the case that we want to move to the next position first.
                // Move to the next position, and check that it is in the correct order.
                assert( cur != end );
                auto const old_pos = par->position_function( *cur );
                ++cur;
                auto const new_pos = par->position_function( *cur );
                if( cur != end && par->chromosome_function( *cur ) == chr && old_pos >= new_pos ) {
                    throw std::runtime_error(
                        "Invalid order on chromosome " + chr + " with position " +
                        std::to_string( old_pos ) + " followed by position " +
                        std::to_string( new_pos )
                    );
                }

                // Now check whether we are done with the chromosome.
                // If not, we return the current element that we just moved to.
                if( cur == end || par->chromosome_function( *cur ) != chr ) {
                    return nullptr;
                }
                return &*cur;
            };
        }

        void init_whole_genome_()
        {
            assert( parent_ );

            // Need to check whether there is any data at all. If not, we are done here.
            if( base_iterator_type::current_ == base_iterator_type::end_ ) {
                parent_ = nullptr;
                return;
            }

            // Similar to the above, we need pointer variables to the iterators and other elements.
            auto& cur = self_type::current_;
            auto& end = self_type::end_;

            // We reset the window view, so that it's a new iterator for the new chromosome,
            // starting from the first position, with a fitting increment function.
            window_ = WindowViewType();
            window_.get_next_element = [ &cur, &end ]( bool is_first ) mutable -> DataType* {
                assert( cur != end );

                // If this is the first call of the function, we are initializing the WindowView
                // with the current entry of the underlying iterator. If not, we first move to the
                // next position (if there is any), before getting the data.
                if( is_first ) {
                    return &*cur;
                }

                // Now we are in the case that we want to move to the next position first.
                // Move to the next position, and check that it is in the correct order.
                ++cur;

                // Now check whether we are done with the chromosome.
                // If not, we return the current element that we just moved to.
                if( cur == end ) {
                    return nullptr;
                }
                return &*cur;
            };
        }

        value_type& get_current_window_() const override final
        {
            return const_cast<value_type&>( window_ );
        }

        base_type const* get_parent_() const override final
        {
            return parent_;
        }

    private:

        // Parent. Needs to live here to have the correct derived type.
        ChromosomeIterator const* parent_ = nullptr;

        WindowViewType window_;

        // We keep track of which chromosomes we have seen yet, in order to allow random order,
        // but not repeated chromosomes.
        std::unordered_set<std::string> processed_chromosomes_;

    };

    // ======================================================================================
    //      Main Class
    // ======================================================================================

    // -------------------------------------------------------------------------
    //     Constructors and Rule of Five
    // -------------------------------------------------------------------------

    ChromosomeIterator(
        InputIterator begin, InputIterator end
    )
        : base_type( begin, end )
    {}

    ~ChromosomeIterator() = default;

    ChromosomeIterator( ChromosomeIterator const& ) = default;
    ChromosomeIterator( ChromosomeIterator&& )      = default;

    ChromosomeIterator& operator= ( ChromosomeIterator const& ) = default;
    ChromosomeIterator& operator= ( ChromosomeIterator&& )      = default;

    friend DerivedIterator;

    // -------------------------------------------------------------------------
    //     Settings
    // -------------------------------------------------------------------------

    bool whole_genome() const
    {
        return whole_genome_;
    }

    /**
     * @brief If set, iterate the whole genome at once, instead of each chromosome individually.
     *
     * This means that the whole input data is iterated at once, so that the inner iterator,
     * as provided by the WindowView, only gets instanciated once, and that WindowView then
     * traverses the genome.
     */
    self_type& whole_genome( bool value )
    {
        whole_genome_ = value;
        return *this;
    }

    // -------------------------------------------------------------------------
    //     Virtual Members
    // -------------------------------------------------------------------------

protected:

    std::unique_ptr<typename base_type::BaseIterator>
    get_begin_iterator_() override final
    {
        // Cannot use make_unique here, as the Iterator constructor is private,
        // and trying to make make_unique a friend does not seem to be working...
        return std::unique_ptr<DerivedIterator>( new DerivedIterator( this ));
        // return utils::make_unique<DerivedIterator>( this );
    }

    std::unique_ptr<typename base_type::BaseIterator>
    get_end_iterator_() override final
    {
        return std::unique_ptr<DerivedIterator>( new DerivedIterator( nullptr ));
        // return utils::make_unique<DerivedIterator>( nullptr );
    }

    // -------------------------------------------------------------------------
    //     Data Members
    // -------------------------------------------------------------------------

private:

    bool whole_genome_ = false;

};

// =================================================================================================
//     Make Chromosome Window View Iterator
// =================================================================================================

/**
 * @brief Helper function to instantiate a ChromosomeIterator for each chromosome,
 * without the need to specify the template parameters manually.
 */
template<class InputIterator, class DataType = typename InputIterator::value_type>
ChromosomeIterator<InputIterator, DataType>
make_chromosome_iterator(
    InputIterator begin, InputIterator end
) {
    return ChromosomeIterator<InputIterator, DataType>( begin, end );
}

/**
 * @brief Helper function to instantiate a ChromosomeIterator for each chromosome,
 * for a default use case.
 *
 * This helper assumes that the underlying type of the input data stream and of the data
 * that we are sliding over are of the same type, that is, we do no conversion in the
 * `entry_input_function` functor of the ChromosomeIterator. It further assumes that this
 * data type has public member variables `chromosome` and `position` that are accessed by the
 * `chromosome_function` and `position_function` functors of the ChromosomeIterator.
 * For example, a data type that this works for is Variant data.
 */
template<class InputIterator>
ChromosomeIterator<InputIterator>
make_default_chromosome_iterator(
    InputIterator begin, InputIterator end
) {
    using DataType = typename InputIterator::value_type;

    // Set functors.
    auto it = ChromosomeIterator<InputIterator>( begin, end );
    it.entry_input_function = []( DataType const& variant ) {
        return variant;
    };
    it.chromosome_function = []( DataType const& variant ) {
        return variant.chromosome;
    };
    it.position_function = []( DataType const& variant ) {
        return variant.position;
    };

    // Set properties and return.
    return it;
}

// =================================================================================================
//     Make Genome Window View Iterator
// =================================================================================================

/**
 * @brief Helper function to instantiate a ChromosomeIterator for the whole genome,
 * without the need to specify the template parameters manually.
 *
 * This helper function creates a ChromosomeIterator from the given pair of iterators,
 * and sets ChromosomeIterator::whole_genome() to `true`, so that the whole genome is traversed
 * without stopping at individual chromosomes in each iteration.
 */
template<class InputIterator, class DataType = typename InputIterator::value_type>
ChromosomeIterator<InputIterator, DataType>
make_genome_iterator(
    InputIterator begin, InputIterator end
) {
    auto it = ChromosomeIterator<InputIterator, DataType>( begin, end );
    it.whole_genome( true );
    return it;
}

/**
 * @brief Helper function to instantiate a ChromosomeIterator for the whole genome,
 * for a default use case.
 *
 * @copydetails make_default_chromosome_iterator
 *
 * This helper function creates a ChromosomeIterator from the given pair of iterators,
 * and sets ChromosomeIterator::whole_genome() to `true`, so that the whole genome is traversed
 * without stopping at individual chromosomes in each iteration.
 */
template<class InputIterator>
ChromosomeIterator<InputIterator>
make_default_genome_iterator(
    InputIterator begin, InputIterator end
) {
    auto it = make_default_chromosome_iterator( begin, end );
    it.whole_genome( true );
    return it;
}

} // namespace population
} // namespace genesis

#endif // include guard
