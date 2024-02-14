/*
    Genesis - A toolkit for working with phylogenetic data.
    Copyright (C) 2014-2024 Lucas Czech

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
 * @ingroup test
 */

#include "src/common.hpp"

#include "genesis/population/formats/simple_pileup_input_iterator.hpp"
#include "genesis/population/formats/simple_pileup_reader.hpp"
#include "genesis/population/iterators/variant_input_iterator.hpp"
#include "genesis/population/window/functions.hpp"
#include "genesis/population/window/sliding_entries_window_iterator.hpp"
#include "genesis/population/window/variant_window_iterator.hpp"
#include "genesis/population/window/window.hpp"
#include "genesis/utils/containers/lambda_iterator.hpp"

#include <unordered_map>

using namespace genesis::population;
using namespace genesis::utils;

template<class WindowIterator>
void test_sliding_entries_iterator_( WindowIterator& win_it, size_t count )
{
    bool found_first_win = false;
    bool found_last_win = false;

    // Also test that the observer functions get executed once per window.
    size_t observe_cnt = 0;
    using ValueType = typename WindowIterator::InputIteratorType::value_type;
    win_it.add_observer( [&observe_cnt]( Window<ValueType> const& ){
        // LOG_DBG << "at " << observe_cnt;
        ++observe_cnt;
    });

    // DBG  2R : 7790001 7790001-7800000 # 1
    // DBG  2R : 7800001 7800001-7810000 # 9874
    // DBG  2R : 7810001 7810001-7820000 # 9972
    // DBG  2R : 7820001 7820001-7830000 # 9909
    // DBG  2R : 7830001 7830001-7840000 # 10000
    // DBG  2R : 7840001 7840001-7850000 # 9997
    // DBG  2R : 7850001 7850001-7860000 # 247

    std::vector<size_t> window_first_positions;
    std::vector<size_t> window_last_positions;
    std::vector<size_t> window_sizes;

    if( count == 9000 ) {
        window_first_positions = std::vector<size_t>{
            7800000, 7809126, 7818154, 7827245, 7836245, 7845248
        };
        window_last_positions = std::vector<size_t>{
            7809125, 7818153, 7827244, 7836244, 7845247, 7850275
        };
        window_sizes = std::vector<size_t>{
            9000, 9000, 9000, 9000, 9000, 5000
        };
    } else if( count == 10000 ) {
        window_first_positions = std::vector<size_t>{
            7800000, 7810126, 7820154, 7830245, 7840245
        };
        window_last_positions = std::vector<size_t>{
            7810125, 7820153, 7830244, 7840244, 7850275
        };
        window_sizes = std::vector<size_t>{
            10000, 10000, 10000, 10000, 10000
        };
    } else {
        ASSERT_TRUE( false );
    }
    ASSERT_EQ( window_sizes.size(), window_first_positions.size() );
    ASSERT_EQ( window_sizes.size(), window_last_positions.size() );

    size_t window_cnt = 0;
    for( auto it = win_it.begin(); it != win_it.end(); ++it ) {
        auto const& window = *it;

        // LOG_DBG << window.chromosome() << " : "
        //         << anchor_position( window ) << " "
        //         << window.first_position() << "-" << window.last_position()
        //         << " # " << window.entry_count();

        // LOG_DBG << "first " << window.first_position()
        //         << " last " << window.last_position()
        //         << " size " << window.size();

        if( it.is_first_window() ) {
            EXPECT_FALSE( found_first_win );
            found_first_win = true;
        }
        if( it.is_last_window() ) {
            EXPECT_FALSE( found_last_win );
            found_last_win = true;
        }

        EXPECT_TRUE( window_cnt < window_first_positions.size() );
        EXPECT_TRUE( window_cnt < window_last_positions.size() );
        EXPECT_TRUE( window_cnt < window_sizes.size() );
        EXPECT_EQ( window_first_positions[window_cnt], window.first_position() );
        EXPECT_EQ( window_last_positions[window_cnt], window.last_position() );
        EXPECT_EQ( window_sizes[window_cnt], window.size() );

        EXPECT_TRUE( window.first_position() >= 7790001 );
        EXPECT_TRUE( window.first_position() <= 7850001 );
        EXPECT_TRUE( window.last_position() >= 7800000 );
        EXPECT_TRUE( window.last_position() <= 7860000 );

        ++window_cnt;
    }
    EXPECT_EQ( window_sizes.size(), window_cnt );
    EXPECT_EQ( window_sizes.size(), observe_cnt );

    EXPECT_TRUE( found_first_win );
    EXPECT_TRUE( found_last_win );
}

void test_window_iterator_sliding_entries_direct( size_t count )
{
    // Skip test if no data availabe.
    NEEDS_TEST_DATA;
    std::string const infile = environment->data_dir + "population/78.pileup.gz";
    // std::string const infile = environment->data_dir + "population/example.pileup";

    // Make an underlying data iterator over some variants.
    auto pileup_begin = SimplePileupInputIterator<>( from_file( infile ));
    auto pileup_end = SimplePileupInputIterator<>();

    // Set up the window iterator. Rename to `win_it` to use it with the below test code.
    auto win_it = make_default_sliding_entries_window_iterator(
        pileup_begin, pileup_end, count
    );

    // Run the tests.
    test_sliding_entries_iterator_( win_it, count );

    // auto window_range = make_sliding_window_range(
    // auto win_it = make_sliding_window_iterator<SimplePileupReader::Record>(
    //     pileup_begin, pileup_end,
    //     []( SimplePileupReader::Record const& record ) -> SimplePileupReader::Record const& {
    //         return record;
    //     },
    //     []( SimplePileupReader::Record const& record ) -> std::string const& {
    //         return record.chromosome;
    //     },
    //     []( SimplePileupReader::Record const& record ){
    //         return record.position;
    //     },
    //     WindowType::kInterval, 10000, 10000
    // );

    // auto win_it = window_range.begin();
    // while( win_it != window_range.end() ) {
    //     LOG_DBG << win_it->chromosome() << " : " << win_it->anchor_position();
    //     ++win_it;
    // }
}

TEST( WindowIterator, SlidingEntriesDirect )
{
    test_window_iterator_sliding_entries_direct(  9000 );
    test_window_iterator_sliding_entries_direct( 10000 );
}

void test_window_iterator_sliding_entries_lambda( size_t count )
{
    // Skip test if no data availabe.
    NEEDS_TEST_DATA;
    std::string const infile = environment->data_dir + "population/78.pileup.gz";
    // std::string const infile = environment->data_dir + "population/example.pileup";

    // Make a Lambda Iterator over the data stream.
    auto data_gen = make_variant_input_iterator_from_pileup_file( infile );
    // data_gen.block_size( 1024 * 1024 );
    data_gen.block_size(0);
    auto pileup_begin = data_gen.begin();
    auto pileup_end   = data_gen.end();

    // Create a window iterator based on the lambda iterator.
    auto win_it = make_default_sliding_entries_window_iterator(
        pileup_begin, pileup_end, count
    );

    test_sliding_entries_iterator_( win_it, count );
}

TEST( WindowIterator, SlidingEntriesLambda )
{
    test_window_iterator_sliding_entries_lambda(  9000 );
    test_window_iterator_sliding_entries_lambda( 10000 );
}

void run_sliding_entries_window_view_variant_test_( VariantWindowViewIterator& win_it )
{
    size_t window_cnt = 0;
    for( auto it = win_it.begin(); it != win_it.end(); ++it ) {
        auto const& window = *it;

        EXPECT_TRUE( window.first_position() >= 7790001 );
        EXPECT_TRUE( window.first_position() <= 7850001 );
        EXPECT_TRUE( window.last_position() >= 7800000 );
        EXPECT_TRUE( window.last_position() <= 7860000 );

        ++window_cnt;
    }
    EXPECT_EQ( 6, window_cnt );
}

TEST( WindowIterator, SlidingEntriesWindowView )
{
    // Skip test if no data availabe.
    NEEDS_TEST_DATA;
    std::string const infile = environment->data_dir + "population/78.pileup.gz";
    // std::string const infile = environment->data_dir + "population/example.pileup";

    // Make a Lambda Iterator over the data stream.
    auto data_gen = make_variant_input_iterator_from_pileup_file( infile );
    // data_gen.block_size( 1024 * 1024 );
    data_gen.block_size(0);
    auto pileup_begin = data_gen.begin();
    auto pileup_end   = data_gen.end();

    // Create a window iterator based on the lambda iterator.
    auto win_it = make_default_sliding_entries_window_view_iterator(
        pileup_begin, pileup_end, 9000
    );

    // Also test that the observer functions get executed once per window.
    size_t observe_cnt = 0;
    win_it.add_observer( [&observe_cnt]( WindowView<Variant> const& ){
        // LOG_DBG << "at " << observe_cnt;
        ++observe_cnt;
    });

    // We use a test function that takes our abstract type, to see if we set this up correctly.
    run_sliding_entries_window_view_variant_test_( win_it );
    EXPECT_EQ( 6, observe_cnt );

    // size_t window_cnt = 0;
    // for( auto it = win_it.begin(); it != win_it.end(); ++it ) {
    //     ++window_cnt;
    // }
    // EXPECT_EQ( 6, window_cnt );
}

TEST( WindowIterator, SlidingEntriesEmpty )
{
    // Skip test if no data availabe.
    NEEDS_TEST_DATA;
    std::string const infile = environment->data_dir + "population/empty.pileup";

    // Make a Lambda Iterator over the data stream.
    auto data_gen = make_variant_input_iterator_from_pileup_file( infile );
    auto pileup_begin = data_gen.begin();
    auto pileup_end   = data_gen.end();

    // Create a window iterator based on the lambda iterator.
    auto win_it = make_default_sliding_entries_window_iterator(
        pileup_begin, pileup_end, 10000
    );

    // Also test that the observer functions get executed once per window.
    size_t observe_cnt = 0;
    win_it.add_observer( [&observe_cnt]( Window<Variant> const& ){
        // LOG_DBG << "at " << observe_cnt;
        ++observe_cnt;
    });

    size_t window_cnt = 0;
    for( auto it = win_it.begin(); it != win_it.end(); ++it ) {

        // This body should never be exectuted.
        // We access the iterator still, to make sure that this thing gets compiled properly,
        // without optimizing anything away by accident.
        // EXPECT_ANY_THROW( it->chromosome() );
        EXPECT_TRUE( it.is_first_window() );
        EXPECT_TRUE( it.is_last_window() );
        LOG_DBG << "-" << it->chromosome() << "-";

        ++window_cnt;
    }
    EXPECT_EQ( 0, window_cnt );
    EXPECT_EQ( 0, observe_cnt );
}
