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
 * @ingroup test
 */

#include "src/common.hpp"

#include "genesis/population/formats/simple_pileup_input_iterator.hpp"
#include "genesis/population/formats/simple_pileup_reader.hpp"
#include "genesis/population/formats/variant_input_iterator.hpp"
#include "genesis/population/window/functions.hpp"
#include "genesis/population/window/chromosome_iterator.hpp"
#include "genesis/population/window/window.hpp"
#include "genesis/population/window/window_view.hpp"
#include "genesis/utils/containers/lambda_iterator.hpp"

using namespace genesis::population;
using namespace genesis::utils;

TEST( WindowIterator, ChromosomeIteratorChromosome )
{
    // Skip test if no data availabe.
    NEEDS_TEST_DATA;

    // Empty file
    {
        std::string const infile = environment->data_dir + "population/empty.pileup";
        // std::string const infile = environment->data_dir + "population/example.pileup";

        // Make a Lambda Iterator over the data stream,
        // and set up the window iterator. Rename to `win_it` to use it with the below test code.
        auto data_gen = make_variant_input_iterator_from_pileup_file( infile );
        auto win_it = make_default_chromosome_iterator( data_gen.begin(), data_gen.end() );

        // Run the tests.
        std::vector<size_t> pos_per_chr;
        for( auto it = win_it.begin(); it != win_it.end(); ++it ) {
            pos_per_chr.push_back(0);
            // LOG_DBG << "chr " << it->chromosome();
            for( auto const& elem : *it ) {
                // LOG_DBG1 << "at " << elem.position;
                (void) elem;
                ++pos_per_chr.back();
            }
            // LOG_DBG << "done " << cnt;
        }

        // Tests
        EXPECT_EQ( 0, pos_per_chr.size() );
    }

    // Single chromosome
    {
        std::string const infile = environment->data_dir + "population/78.pileup.gz";
        // std::string const infile = environment->data_dir + "population/example.pileup";

        // Make a Lambda Iterator over the data stream,
        // and set up the window iterator. Rename to `win_it` to use it with the below test code.
        auto data_gen = make_variant_input_iterator_from_pileup_file( infile );
        auto win_it = make_default_chromosome_iterator( data_gen.begin(), data_gen.end() );

        // Run the tests.
        std::vector<size_t> pos_per_chr;
        for( auto it = win_it.begin(); it != win_it.end(); ++it ) {
            pos_per_chr.push_back(0);
            // LOG_DBG << "chr " << it->chromosome();
            for( auto const& elem : *it ) {
                // LOG_DBG1 << "at " << elem.position;
                (void) elem;
                ++pos_per_chr.back();
            }
            // LOG_DBG << "done " << cnt;
        }

        // Tests
        ASSERT_EQ( 1, pos_per_chr.size() );
        EXPECT_EQ( 50000, pos_per_chr[0] );
    }

    // Multiple chromosomes
    {
        std::string const infile = environment->data_dir + "population/ex1.bam";

        // Make a Lambda Iterator over the data stream,
        // and set up the window iterator. Rename to `win_it` to use it with the below test code.
        auto data_gen = make_variant_input_iterator_from_sam_file( infile );
        auto win_it = make_default_chromosome_iterator( data_gen.begin(), data_gen.end() );

        // Run the tests.
        std::vector<size_t> pos_per_chr;
        for( auto it = win_it.begin(); it != win_it.end(); ++it ) {
            pos_per_chr.push_back(0);
            // LOG_DBG << "chr " << it->chromosome();
            for( auto const& elem : *it ) {
                // LOG_DBG1 << "at " << elem.position;
                (void) elem;
                ++pos_per_chr.back();
            }
            // LOG_DBG << "done " << cnt;
        }

        // Tests
        ASSERT_EQ( 2, pos_per_chr.size() );
        EXPECT_EQ( 1569, pos_per_chr[0] );
        EXPECT_EQ( 1567, pos_per_chr[1] );
    }
}

TEST( WindowIterator, ChromosomeIteratorWholeGenome )
{
    // Almost exactly the same as above... we could refactor this to avoid the duplication...
    // Good enough for now, fix later.

    // Skip test if no data availabe.
    NEEDS_TEST_DATA;

    // Empty file
    {
        std::string const infile = environment->data_dir + "population/empty.pileup";
        // std::string const infile = environment->data_dir + "population/example.pileup";

        // Make a Lambda Iterator over the data stream,
        // and set up the window iterator. Rename to `win_it` to use it with the below test code.
        auto data_gen = make_variant_input_iterator_from_pileup_file( infile );
        auto win_it = make_default_genome_iterator( data_gen.begin(), data_gen.end() );

        // Run the tests.
        std::vector<size_t> pos_per_chr;
        for( auto it = win_it.begin(); it != win_it.end(); ++it ) {
            pos_per_chr.push_back(0);
            // LOG_DBG << "chr " << it->chromosome();
            for( auto const& elem : *it ) {
                // LOG_DBG1 << "at " << elem.position;
                (void) elem;
                ++pos_per_chr.back();
            }
            // LOG_DBG << "done " << cnt;
        }

        // Tests
        EXPECT_EQ( 0, pos_per_chr.size() );
    }

    // Single chromosome
    {
        std::string const infile = environment->data_dir + "population/78.pileup.gz";
        // std::string const infile = environment->data_dir + "population/example.pileup";

        // Make a Lambda Iterator over the data stream,
        // and set up the window iterator. Rename to `win_it` to use it with the below test code.
        auto data_gen = make_variant_input_iterator_from_pileup_file( infile );
        auto win_it = make_default_genome_iterator( data_gen.begin(), data_gen.end() );

        // Run the tests.
        std::vector<size_t> pos_per_chr;
        for( auto it = win_it.begin(); it != win_it.end(); ++it ) {
            pos_per_chr.push_back(0);
            // LOG_DBG << "chr " << it->chromosome();
            for( auto const& elem : *it ) {
                // LOG_DBG1 << "at " << elem.position;
                (void) elem;
                ++pos_per_chr.back();
            }
            // LOG_DBG << "done " << cnt;
        }

        // Tests
        ASSERT_EQ( 1, pos_per_chr.size() );
        EXPECT_EQ( 50000, pos_per_chr[0] );
    }

    // Multiple chromosomes
    {
        std::string const infile = environment->data_dir + "population/ex1.bam";

        // Make a Lambda Iterator over the data stream,
        // and set up the window iterator. Rename to `win_it` to use it with the below test code.
        auto data_gen = make_variant_input_iterator_from_sam_file( infile );
        auto win_it = make_default_genome_iterator( data_gen.begin(), data_gen.end() );

        // Run the tests.
        std::vector<size_t> pos_per_chr;
        for( auto it = win_it.begin(); it != win_it.end(); ++it ) {
            pos_per_chr.push_back(0);
            // LOG_DBG << "chr " << it->chromosome();
            for( auto const& elem : *it ) {
                // LOG_DBG1 << "at " << elem.position;
                (void) elem;
                ++pos_per_chr.back();
            }
            // LOG_DBG << "done " << cnt;
        }

        // Tests
        ASSERT_EQ( 1, pos_per_chr.size() );
        EXPECT_EQ( 3136, pos_per_chr[0] );
    }
}
