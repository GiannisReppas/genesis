#ifndef GENESIS_SEQUENCE_FORMATS_PHYLIP_READER_H_
#define GENESIS_SEQUENCE_FORMATS_PHYLIP_READER_H_

/*
    Genesis - A toolkit for working with phylogenetic data.
    Copyright (C) 2014-2017 Lucas Czech

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
    Lucas Czech <lucas.czech@h-its.org>
    Exelixis Lab, Heidelberg Institute for Theoretical Studies
    Schloss-Wolfsbrunnenweg 35, D-69118 Heidelberg, Germany
*/

/**
 * @brief
 *
 * @file
 * @ingroup sequence
 */

#include "utils/tools/char_lookup.hpp"

#include <iosfwd>
#include <string>

namespace genesis {

// =================================================================================================
//     Forward Declarations
// =================================================================================================

namespace utils {

class InputStream;

} // namespace utils

namespace sequence {

class SequenceSet;
class Sequence;

// =================================================================================================
//     Phylip Reader
// =================================================================================================

/**
 * @brief Read Phylip data.
 *
 * This class provides simple facilities for reading Phylip data. It supports to read
 *
 *   * from_stream()
 *   * from_file()
 *   * from_string()
 *
 * Exemplary usage:
 *
 *     std::string infile = "path/to/file.phylip";
 *     SequenceSet sset;
 *
 *     PhylipReader()
 *         .to_upper()
 *         .valid_chars( nucleic_acid_codes_all() )
 *         .from_file( infile, sset );
 *
 * The expected data format roughly follows
 * [the original definition](http://evolution.genetics.washington.edu/phylip/doc/sequence.html).
 * See mode( Mode ) to selected between sequential, interleaved and automatic mode.
 * We furthermore support a relaxed version (by default), where the label can be of any length.
 * See label_length( size_t ) for more information.
 *
 * Using to_upper( bool ), the sequences can automatically be turned into upper case letter.
 * Also, see valid_chars( std::string const& ) for a way of checking correct input sequences.
 */
class PhylipReader
{
public:

    // ---------------------------------------------------------------------
    //     Types and Enums
    // ---------------------------------------------------------------------

    /**
     * @brief Helper that stores the header information of a Phylip file.
     */
    struct Header
    {
        /**
         * @brief Number of sequences in the Phylip file.
         */
        size_t      num_sequences = 0;

        /**
         * @brief Length of the sequences in the Phylip file.
         */
        size_t      len_sequences = 0;

        /**
         * @brief Store metadata at the end of the header line.
         *
         * Some Phylip files contain data after the two mandatory numbers in the header line.
         * This data can be stored here.
         *
         * There are magic values for this metadata: If the (trimmed) remainder of the
         * header line is simply "s" or "i", this is used as a trigger to distinguish
         * between sequential and interleaved Phylip files. This is however only used if
         * Mode::kAutomatic is selected, see mode( Mode ) for more information.
         */
        std::string remainder;
    };

    /**
     * @brief Enum to distinguish between the different file variants of Phylip.
     * See mode( Mode value ) for more details.
     */
    enum class Mode
    {
        /**
         * @brief Read the data in Phylip sequential mode.
         */
        kSequential,

        /**
        * @brief Read the data in Phylip interleaved mode.
        */
        kInterleaved,

        /**
        * @brief Infer the Phylip mode via trial and error.
        */
        kAutomatic
    };

    // ---------------------------------------------------------------------
    //     Constructor and Rule of Five
    // ---------------------------------------------------------------------

    PhylipReader();
    ~PhylipReader() = default;

    PhylipReader( PhylipReader const& ) = default;
    PhylipReader( PhylipReader&& )      = default;

    PhylipReader& operator= ( PhylipReader const& ) = default;
    PhylipReader& operator= ( PhylipReader&& )      = default;

    // ---------------------------------------------------------------------
    //     Reading
    // ---------------------------------------------------------------------

    void from_stream ( std::istream&      input_stream, SequenceSet& sequence_set ) const;
    void from_file   ( std::string const& file_name,    SequenceSet& sequence_set ) const;
    void from_string ( std::string const& input_string, SequenceSet& sequence_set ) const;

    // ---------------------------------------------------------------------
    //     Parsing
    // ---------------------------------------------------------------------

    Header parse_phylip_header(
        utils::InputStream& it
    ) const;

    std::string parse_phylip_label(
        utils::InputStream& it
    ) const;

    std::string parse_phylip_sequence_line(
        utils::InputStream& it
    ) const;

    void parse_phylip_interleaved(
        utils::InputStream& it,
        SequenceSet& sset
    ) const;

    void parse_phylip_sequential(
        utils::InputStream& it,
        SequenceSet& sset
    ) const;

    // ---------------------------------------------------------------------
    //     Properties
    // ---------------------------------------------------------------------

    PhylipReader& mode( Mode value );
    Mode          mode() const;

    PhylipReader& label_length( size_t value );
    size_t        label_length() const;

    PhylipReader& to_upper( bool value );
    bool          to_upper() const;

    PhylipReader& valid_chars( std::string const& chars );
    std::string   valid_chars() const;

    utils::CharLookup<bool>& valid_char_lookup();

    // ---------------------------------------------------------------------
    //     Members
    // ---------------------------------------------------------------------

private:

    Mode                    mode_           = Mode::kSequential;
    size_t                  label_length_   = 0;

    bool                    to_upper_       = true;
    bool                    use_validation_ = false;
    utils::CharLookup<bool> lookup_;

};

} // namespace sequence
} // namespace genesis

#endif // include guard
