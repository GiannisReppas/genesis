#ifndef GENESIS_POPULATION_FORMATS_VCF_RECORD_H_
#define GENESIS_POPULATION_FORMATS_VCF_RECORD_H_

/*
    Genesis - A toolkit for working with phylogenetic data.
    Copyright (C) 2014-2020 Lucas Czech

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
 * @ingroup population
 */

#include "genesis/population/formats/vcf_header.hpp"

#include <string>
#include <vector>

extern "C" {
    #include <htslib/hts.h>
    #include <htslib/vcf.h>
}

// =================================================================================================
//     Forward Declarations
// =================================================================================================

namespace genesis {
namespace population {

class HtsFile;
class VcfHeader;

// =================================================================================================
//     VCF/BCF Record
// =================================================================================================

/**
 * @brief Capture the information of a single SNP/variant line in a VCF/BCF file.
 */
class VcfRecord
{
public:

    // -------------------------------------------------------------------------
    //     Typedefs and Enums
    // -------------------------------------------------------------------------

    /**
     * @brief Types of variants of alleles that can occur in a record.
     *
     * Corresponds to the `VCF_*` macro constants defined by htslib. We statically assert
     * that these have the same values.
     */
    enum class VariantType : int {
        kRef      =  0,
        kSnp      =  1,
        kMnp      =  2,
        kIndel    =  4,
        kOther    =  8,
        kBreakend = 16, // Breakend
        kOverlap  = 32, // Overlapping deletion, ALT=*
    };

    /**
     * @brief And-operator for VariantType%s.
     *
     * The function get_variant_types() returns the or'ed (union) values of all variant types that
     * appear in the alternative alleles of the record. Hence, this and-operator can be used
     * to disentangle them and test whether a particular variant occurs in the record:
     *
     *     if( record.get_variant_types() & Record::VariantType::kSnp ) {
     *         ...
     *     }
     *
     * See get_variant_types() for details.
     *
     * It's a bit ugly to return a bool from such a comparison, but for now, it works.
     * Should more complex use cases arise in the future, this might change.
     */
    friend bool operator& ( VcfRecord::VariantType a, VcfRecord::VariantType b )
    {
        return ( static_cast<int>(a) & static_cast<int>(b) );
    }

    // -------------------------------------------------------------------------
    //     Constructors and Rule of Five
    // -------------------------------------------------------------------------

    /**
     * @brief Create a default (empty) instance.
     */
    VcfRecord();

    /**
     * @brief Create an instance based on a VCF/BCF header.
     *
     * This is the most common use case, where we create a record instance for a given VCF/BCF file,
     * using its header information for access to details laters.
     */
    explicit VcfRecord( VcfHeader& header );

    /**
     * @brief Create an instance by copy.
     *
     * This calls ::bcf_dup() from htslib to create a copy of the given record.
     * The provided @p bcf1 record hence has to be freed elsewhere.
     */
    VcfRecord( VcfHeader& header, ::bcf1_t* bcf1 );

    ~VcfRecord();

    VcfRecord( VcfRecord const& ) = delete;
    VcfRecord( VcfRecord&& )      = default;

    VcfRecord& operator= ( VcfRecord const& ) = delete;
    VcfRecord& operator= ( VcfRecord&& )      = default;

    // -------------------------------------------------------------------------
    //     Accessors
    // -------------------------------------------------------------------------

    ::bcf1_t* data()
    {
        return record_;
    }

    // -------------------------------------------------------------------------
    //     Simple Fixed Columns
    // -------------------------------------------------------------------------

    /**
     * @brief Get the name of a chromosome/contig/sequence (`CHROM`, first column of the line).
     */
    std::string get_chrom() const;

    /**
     * @brief Get the position within the chromosome/contig (`POS`, second column of the line).
     *
     * We report the position as given in the VCF/BCF file, that is, 1-based!
     */
    size_t get_position() const;

    /**
     * @brief Get the ID string of the variant (`ID`, third column of the line).
     *
     * Another instance where the overloaded term "ID" is used in VCF and in htslib. Here,
     * it stands for the identifier list of the line for SNP databases.
     */
    std::string get_id() const;

    /**
     * @brief Get the reference allele/sequence of the variant (`REF`, fourth column of the line).
     */
    std::string get_reference() const;

    /**
     * @brief Get the alternative alleles/sequences of the variant (`ALT`, fifth column of the line).
     */
    std::vector<std::string> get_alternatives() const;

    /**
     * @brief Get the number of alternative alleles/sequences of the variant
     * (`ALT`, fifth column of the line).
     *
     * This simply gives their count, which is identical to `get_alternatives().size()`.
     */
    size_t get_alternatives_count() const;

    /**
     * @brief Shortcut to get both the reference (`REF`, fourth column of the line) and the alternative
     * (`ALT`, fifth column of the line) alleles/sequences of the line.
     *
     * This simply combines get_reference() and get_alternatives(). Note that hence the indices
     * of the alternatives are shifted as compared to get_alternatives().
     */
    std::vector<std::string> get_variants() const;

    /**
     * @brief Get the or'ed (union) value of all variant types of the alternative alleles/sequences
     * of the record.
     *
     * This can be used to simply test whether a particular type of variant appears at all in
     * a given record:
     *
     *     if( record.get_variant_types() & VcfRecord::VariantType::kSnp ) {
     *         ...
     *     }
     *
     * See operator& ( VariantType a, VariantType b ) for details.
     *
     * This is a simple wrapper for ::bcf_get_variant_types() from htslib, which however is not
     * ideally named, as "variants" seems to mean REF+ALT in VCF terminology, but the flag for REF
     * has value 0 and hence is (in a sense) always set in the result. Of course, this makes sense,
     * as we always have a reference variant. But technically, we cannot test for this, so this
     * function only is useful for alternative alleles, and not all variants. Still, we follow their
     * terminology here.
     */
    VariantType get_variant_types() const;

    /**
     * @brief Get the variant type of a particular alternative allele/sequence.
     *
     * The @p alt_index is the 0-based index of the alternative allele/sequence for which we want
     * the variant type. This corresponds to the indices in the get_alternatives() result vector,
     * which are hence in the range `[ 0, get_alternatives_count() )`.
     */
    VariantType get_variant_type( size_t alt_index ) const;

    /**
     * @brief Return whether this variant is a SNP.
     *
     * This is simply a wrapper for the htslib function ::bcf_is_snp(). It returns `true` iff
     * the reference and all alternative alleles/sequence are single characters
     * (and none of them is a `'*'` missing allele).
     */
    bool is_snp() const;

    /**
     * @brief Get the quality score (`QUAL`, sixth column of the line).
     */
    double get_quality() const;

    // -------------------------------------------------------------------------
    //     Filter Column
    // -------------------------------------------------------------------------

    /**
     * @brief Get the list of all filter values (`PASS` or the names of the non-passing filters)
     * that are applied to the record.
     *
     * For example, the lines
     *
     *     #CHROM POS      ID         REF   ALT    QUAL  FILTER  [...]
     *     20     14370    rs6054257  G     A      29    PASS    [...]
     *     20     17330    .          T     A      3     q10     [...]
     *
     * would return `{"PASS"}` and `{"q10"}`, respectively.
     */
    std::vector<std::string> get_filter_ids() const;

    /**
     * @brief Return whether the record has a given @p filter set.
     *
     * For example, provided with `filter == "q10"`, the function returns whether the `q10` filter
     * is set for the record (indicating that the record failed that filter test).
     */
    bool has_filter( std::string const& filter ) const;

    /**
     * @brief Return whether the record passes the filters, that is, whether `PASS` is set.
     *
     * This is identical to calling has_filter() with the argument `"PASS"`.
     */
    bool pass_filter() const;

    // -------------------------------------------------------------------------
    //     Info Column
    // -------------------------------------------------------------------------

    /**
     * @brief Get the list of all info IDs (`INFO` column) that the record contains.
     *
     * For example, the line
     *
     *     #CHROM POS      ID         REF   ALT    QUAL  FILTER  INFO                     [...]
     *     20     14370    rs6054257  G     A      29    PASS    NS=3;DP=14;AF=0.5;DB;H2  [...]
     *
     * would return a list containing `{"NS", "DP", "AF", "DB", "H2"}`.
     */
    std::vector<std::string> get_info_ids() const;

    /**
     * @brief Return whether the record has a given @p info key.
     */
    bool has_info( std::string const& id ) const;

    std::string get_info_string( std::string const& id ) const;

    void get_info_string( std::string const& id, std::string& destination ) const;

    std::vector<double> get_info_float( std::string const& id ) const;

    void get_info_float( std::string const& id, std::vector<double>& destination ) const;

    std::vector<int32_t> get_info_int( std::string const& id ) const;

    void get_info_int( std::string const& id, std::vector<int32_t>& destination ) const;

    bool get_info_flag( std::string const& id ) const;

    // -------------------------------------------------------------------------
    //     Format Column
    // -------------------------------------------------------------------------

    // -------------------------------------------------------------------------
    //     Sample Columns
    // -------------------------------------------------------------------------

    // -------------------------------------------------------------------------
    //     Modifiers
    // -------------------------------------------------------------------------

    bool read( HtsFile& source );

    // -------------------------------------------------------------------------
    //     Internal Members
    // -------------------------------------------------------------------------

private:

    int get_info_ptr_( std::string const& id, int ht_type, void** dest, int* ndest ) const;

    // -------------------------------------------------------------------------
    //     Data Members
    // -------------------------------------------------------------------------

private:

    // We keep a pointer to the header here, but do not free it, because that is managed
    // by the VcfHeader class. Here, we only manage the record_ instance.
    ::bcf_hdr_t* header_ = nullptr;
    ::bcf1_t* record_ = nullptr;

    // htslib wants to copy values all the time, so we reserve buffers to avoid reallocations.
    mutable char*    info_dest_string_  = nullptr;
    mutable float*   info_dest_float_   = nullptr;
    mutable int32_t* info_dest_int_     = nullptr;
    mutable int      info_ndest_string_ = 0;
    mutable int      info_ndest_float_  = 0;
    mutable int      info_ndest_int_    = 0;
};

} // namespace population
} // namespace genesis

#endif // include guard
