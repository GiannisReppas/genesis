#include <array>
#include <functional>
#include <genesis/population/base_counts.hpp>
#include <genesis/population/formats/simple_pileup_reader.hpp>
#include <genesis/population/variant.hpp>
#include <genesis/sequence/functions/quality.hpp>
#include <genesis/utils/io/base_input_source.hpp>
#include <genesis/utils/io/input_stream.hpp>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <utility>
#include <vector>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>
#include <pybind11/functional.h>
#include <../python/custom_bindings/extensions/matrix.hpp>
#include <genesis/utils/tools/color/functions.hpp>
#include <../python/custom_bindings/extensions/bitvector.hpp>
#include <../python/custom_bindings/extensions/range.hpp>
#include <../python/custom_bindings/extensions/quality.hpp>
#include <../python/custom_bindings/extensions/sequence_set.hpp>
#include <../python/custom_bindings/extensions/sequence_dict.hpp>
#include <../python/custom_bindings/extensions/fasta_input_iterator.hpp>
#include <../python/custom_bindings/extensions/fastq_input_iterator.hpp>
#include <../python/custom_bindings/extensions/fasta_output_iterator.hpp>
#include <../python/custom_bindings/extensions/taxopath.hpp>
#include <../python/custom_bindings/extensions/functions_taxonomy.hpp>
#include <../python/custom_bindings/extensions/tree.hpp>
#include <../python/custom_bindings/extensions/functions_tree.hpp>
#include <genesis/population/genome_region_list.hpp>
#include <pybind11/stl.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_genesis_population_base_counts(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // genesis::population::BaseCounts file:genesis/population/base_counts.hpp line:54
		pybind11::class_<genesis::population::BaseCounts, std::shared_ptr<genesis::population::BaseCounts>> cl(M("genesis::population"), "BaseCounts", "One set of nucleotide base counts, for example for a given sample that represents a pool\n of sequenced individuals.\n\n This class is a general representation of the read counts (frequencies) contained in the\n variants/SNPs of (a pool of) individuals at a certain chromosome position.\n The class only stores theses counts; for the additional container that also captures the\n chromosome and position, see Variant.");
		cl.def( pybind11::init( [](){ return new genesis::population::BaseCounts(); } ) );
		cl.def( pybind11::init( [](genesis::population::BaseCounts const &o){ return new genesis::population::BaseCounts(o); } ) );
		cl.def_readwrite("a_count", &genesis::population::BaseCounts::a_count);
		cl.def_readwrite("c_count", &genesis::population::BaseCounts::c_count);
		cl.def_readwrite("g_count", &genesis::population::BaseCounts::g_count);
		cl.def_readwrite("t_count", &genesis::population::BaseCounts::t_count);
		cl.def_readwrite("n_count", &genesis::population::BaseCounts::n_count);
		cl.def_readwrite("d_count", &genesis::population::BaseCounts::d_count);
		cl.def("clear", (void (genesis::population::BaseCounts::*)()) &genesis::population::BaseCounts::clear, "Reset all counts to 0.\n\nC++: genesis::population::BaseCounts::clear() --> void");
		cl.def("assign", (struct genesis::population::BaseCounts & (genesis::population::BaseCounts::*)(const struct genesis::population::BaseCounts &)) &genesis::population::BaseCounts::operator=, "C++: genesis::population::BaseCounts::operator=(const struct genesis::population::BaseCounts &) --> struct genesis::population::BaseCounts &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
	}
	{ // genesis::population::SortedBaseCounts file:genesis/population/base_counts.hpp line:115
		pybind11::class_<genesis::population::SortedBaseCounts, std::shared_ptr<genesis::population::SortedBaseCounts>> cl(M("genesis::population"), "SortedBaseCounts", "Ordered array of base counts for the four nucleotides.\n\n Some functions need the bases sorted by their count. This structure is used to keep that data,\n with the highest count base first.");
		cl.def( pybind11::init( [](){ return new genesis::population::SortedBaseCounts(); } ) );
		cl.def( pybind11::init<char, unsigned long, char, unsigned long, char, unsigned long, char, unsigned long>(), pybind11::arg("b0"), pybind11::arg("c0"), pybind11::arg("b1"), pybind11::arg("c1"), pybind11::arg("b2"), pybind11::arg("c2"), pybind11::arg("b3"), pybind11::arg("c3") );

		cl.def_readwrite("data", &genesis::population::SortedBaseCounts::data);
		cl.def("__getitem__", (struct genesis::population::SortedBaseCounts::BaseCount & (genesis::population::SortedBaseCounts::*)(unsigned long)) &genesis::population::SortedBaseCounts::operator[], "C++: genesis::population::SortedBaseCounts::operator[](unsigned long) --> struct genesis::population::SortedBaseCounts::BaseCount &", pybind11::return_value_policy::reference_internal, pybind11::arg("index"));

		{ // genesis::population::SortedBaseCounts::BaseCount file:genesis/population/base_counts.hpp line:120
			auto & enclosing_class = cl;
			pybind11::class_<genesis::population::SortedBaseCounts::BaseCount, std::shared_ptr<genesis::population::SortedBaseCounts::BaseCount>> cl(enclosing_class, "BaseCount", "Combination of a nucleotide base and its count.");
			cl.def( pybind11::init( [](){ return new genesis::population::SortedBaseCounts::BaseCount(); } ) );
			cl.def( pybind11::init<char, unsigned long>(), pybind11::arg("b"), pybind11::arg("c") );

			cl.def( pybind11::init( [](genesis::population::SortedBaseCounts::BaseCount const &o){ return new genesis::population::SortedBaseCounts::BaseCount(o); } ) );
			cl.def_readwrite("base", &genesis::population::SortedBaseCounts::BaseCount::base);
			cl.def_readwrite("count", &genesis::population::SortedBaseCounts::BaseCount::count);
		}

	}
	{ // genesis::population::Variant file:genesis/population/variant.hpp line:62
		pybind11::class_<genesis::population::Variant, std::shared_ptr<genesis::population::Variant>> cl(M("genesis::population"), "Variant", "A single variant at a position in a chromosome, along with BaseCounts for a set of samples.\n\n Typically, this class is used as a general representation of the variants/SNPs at a given\n chromosome position, for example coming from a line in a VCF file or (m)pileup file.\n\n The class consists of the following data fields:\n\n   * A chromosome and position, 1-based.\n   * The reference base and alternative base at that position (which might not always be available\n     in the input file format, in which case we use 'N'). Note that we currently only support\n     one alternative base here, that is, biallelic variants only.\n   * A set of BaseCounts%s, that is, information on the counts of nucleotide bases of thereads\n     of a set of pool samples or individuals that cover this variants/SNPs at that position.\n     See BaseCounts for details on the latter.");
		cl.def( pybind11::init( [](genesis::population::Variant const &o){ return new genesis::population::Variant(o); } ) );
		cl.def( pybind11::init( [](){ return new genesis::population::Variant(); } ) );
		cl.def_readwrite("chromosome", &genesis::population::Variant::chromosome);
		cl.def_readwrite("position", &genesis::population::Variant::position);
		cl.def_readwrite("reference_base", &genesis::population::Variant::reference_base);
		cl.def_readwrite("alternative_base", &genesis::population::Variant::alternative_base);
		cl.def_readwrite("samples", &genesis::population::Variant::samples);
		cl.def("assign", (struct genesis::population::Variant & (genesis::population::Variant::*)(const struct genesis::population::Variant &)) &genesis::population::Variant::operator=, "C++: genesis::population::Variant::operator=(const struct genesis::population::Variant &) --> struct genesis::population::Variant &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
	}
	{ // genesis::population::SimplePileupReader file:genesis/population/formats/simple_pileup_reader.hpp line:78
		pybind11::class_<genesis::population::SimplePileupReader, std::shared_ptr<genesis::population::SimplePileupReader>> cl(M("genesis::population"), "SimplePileupReader", "Reader for line-by-line assessment of (m)pileup files.\n\n This simple reader processes (m)pileup files line by line. That is, it does not take into\n consideration which mapped read starts at which position, but instead gives a quick and simple\n tally of the bases of all reads that cover a given position.\n This makes it fast in cases where only per-position, but no per-read information is needed.\n\n For each processed line, a SimplePileupReader::Record is produced when using the `record`\n versions of the read and parse function, which captures the basic\n information of the line, as well as a tally for each sample in the line, collected in\n SimplePileupReader::Sample. One such sample consists of two or more columns in the file.\n\n The number of columns per sample depends on the additional information contained in the file.\n As we have no way of deciding this automatically, these columns have to be activated beforehand:\n\n   - Quality scores, set with_quality_string()\n   - Ancestral alles, set with_ancestral_base()\n\n More columns might be needed in the future, and potentially their ordering might need to be\n adapted. But for now, we only have these use cases.\n\n Alternatvely, using the `variant` versions of the read and parse functions, instead of producing\n a SimplePileupReader::Record, a Variant per line in the mpileup file can be produced.\n This tends to be slightly faster, and elimiates the need to do downstream conversion.\n That is, instead of yielding per-line tallied bases and phred quality scores,\n these functions directly yields their summed up counts of bases per line.");
		cl.def( pybind11::init( [](){ return new genesis::population::SimplePileupReader(); } ) );
		cl.def( pybind11::init( [](genesis::population::SimplePileupReader const &o){ return new genesis::population::SimplePileupReader(o); } ) );
		cl.def("assign", (class genesis::population::SimplePileupReader & (genesis::population::SimplePileupReader::*)(const class genesis::population::SimplePileupReader &)) &genesis::population::SimplePileupReader::operator=, "C++: genesis::population::SimplePileupReader::operator=(const class genesis::population::SimplePileupReader &) --> class genesis::population::SimplePileupReader &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("read_records", (class std::vector<struct genesis::population::SimplePileupReader::Record, class std::allocator<struct genesis::population::SimplePileupReader::Record> > (genesis::population::SimplePileupReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>) const) &genesis::population::SimplePileupReader::read_records, "Read an (m)pileup file line by line, as pileup Record%s.\n\nC++: genesis::population::SimplePileupReader::read_records(class std::shared_ptr<class genesis::utils::BaseInputSource>) const --> class std::vector<struct genesis::population::SimplePileupReader::Record, class std::allocator<struct genesis::population::SimplePileupReader::Record> >", pybind11::arg("source"));
		cl.def("read_records", (class std::vector<struct genesis::population::SimplePileupReader::Record, class std::allocator<struct genesis::population::SimplePileupReader::Record> > (genesis::population::SimplePileupReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>, const class std::vector<bool, class std::allocator<bool> > &) const) &genesis::population::SimplePileupReader::read_records, "Read an (m)pileup file line by line, but only the samples at which the\n  is `true`, as pileup Record%s.\n\n We expect this filter to contain the same number of values as the record has samples.\n\nC++: genesis::population::SimplePileupReader::read_records(class std::shared_ptr<class genesis::utils::BaseInputSource>, const class std::vector<bool, class std::allocator<bool> > &) const --> class std::vector<struct genesis::population::SimplePileupReader::Record, class std::allocator<struct genesis::population::SimplePileupReader::Record> >", pybind11::arg("source"), pybind11::arg("sample_filter"));
		cl.def("read_variants", (class std::vector<struct genesis::population::Variant, class std::allocator<struct genesis::population::Variant> > (genesis::population::SimplePileupReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>) const) &genesis::population::SimplePileupReader::read_variants, "Read an (m)pileup file line by line, as Variant%s.\n\nC++: genesis::population::SimplePileupReader::read_variants(class std::shared_ptr<class genesis::utils::BaseInputSource>) const --> class std::vector<struct genesis::population::Variant, class std::allocator<struct genesis::population::Variant> >", pybind11::arg("source"));
		cl.def("read_variants", (class std::vector<struct genesis::population::Variant, class std::allocator<struct genesis::population::Variant> > (genesis::population::SimplePileupReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>, const class std::vector<bool, class std::allocator<bool> > &) const) &genesis::population::SimplePileupReader::read_variants, "Read an (m)pileup file line by line, but only the samples at which the\n  is `true`, as Variant%s.\n\n We expect this filter to contain the same number of values as the record has samples.\n\nC++: genesis::population::SimplePileupReader::read_variants(class std::shared_ptr<class genesis::utils::BaseInputSource>, const class std::vector<bool, class std::allocator<bool> > &) const --> class std::vector<struct genesis::population::Variant, class std::allocator<struct genesis::population::Variant> >", pybind11::arg("source"), pybind11::arg("sample_filter"));
		cl.def("parse_line_record", (bool (genesis::population::SimplePileupReader::*)(class genesis::utils::InputStream &, struct genesis::population::SimplePileupReader::Record &) const) &genesis::population::SimplePileupReader::parse_line_record, "Read an (m)pileup line, as a Record.\n\n Note that this only handles a single line, and hence cannot check that the correct order\n of chromosomes and positions in the input is kept. A well-formed (m)pileup file will have\n the correct order, so that should not be an issue. Use the `read_...` functions, or\n the SimplePileupInputIterator for ways to read in (m)pileup data that have this check.\n\nC++: genesis::population::SimplePileupReader::parse_line_record(class genesis::utils::InputStream &, struct genesis::population::SimplePileupReader::Record &) const --> bool", pybind11::arg("input_stream"), pybind11::arg("record"));
		cl.def("parse_line_record", (bool (genesis::population::SimplePileupReader::*)(class genesis::utils::InputStream &, struct genesis::population::SimplePileupReader::Record &, const class std::vector<bool, class std::allocator<bool> > &) const) &genesis::population::SimplePileupReader::parse_line_record, "Read an (m)pileup line, but only the samples at which the  is `true`,\n as a Record.\n\n We expect this filter to contain the same number of values as the record has samples.\n\n  SimplePileupReader::parse_line_record( utils::InputStream&, SimplePileupReader::Record& ) const\n\nC++: genesis::population::SimplePileupReader::parse_line_record(class genesis::utils::InputStream &, struct genesis::population::SimplePileupReader::Record &, const class std::vector<bool, class std::allocator<bool> > &) const --> bool", pybind11::arg("input_stream"), pybind11::arg("record"), pybind11::arg("sample_filter"));
		cl.def("parse_line_variant", (bool (genesis::population::SimplePileupReader::*)(class genesis::utils::InputStream &, struct genesis::population::Variant &) const) &genesis::population::SimplePileupReader::parse_line_variant, "Read an (m)pileup line, as a Variant.\n\n  SimplePileupReader::parse_line_record( utils::InputStream&, SimplePileupReader::Record& ) const\n\nC++: genesis::population::SimplePileupReader::parse_line_variant(class genesis::utils::InputStream &, struct genesis::population::Variant &) const --> bool", pybind11::arg("input_stream"), pybind11::arg("variant"));
		cl.def("parse_line_variant", (bool (genesis::population::SimplePileupReader::*)(class genesis::utils::InputStream &, struct genesis::population::Variant &, const class std::vector<bool, class std::allocator<bool> > &) const) &genesis::population::SimplePileupReader::parse_line_variant, "Read an (m)pileup line, but only the samples at which the  is `true`,\n as a Variant.\n\n We expect this filter to contain the same number of values as the record has samples.\n\n  SimplePileupReader::parse_line_record( utils::InputStream&, SimplePileupReader::Record& ) const\n\nC++: genesis::population::SimplePileupReader::parse_line_variant(class genesis::utils::InputStream &, struct genesis::population::Variant &, const class std::vector<bool, class std::allocator<bool> > &) const --> bool", pybind11::arg("input_stream"), pybind11::arg("variant"), pybind11::arg("sample_filter"));
		cl.def("strict_bases", (bool (genesis::population::SimplePileupReader::*)() const) &genesis::population::SimplePileupReader::strict_bases, "C++: genesis::population::SimplePileupReader::strict_bases() const --> bool");
		cl.def("strict_bases", (class genesis::population::SimplePileupReader & (genesis::population::SimplePileupReader::*)(bool)) &genesis::population::SimplePileupReader::strict_bases, "Set whether to strictly require bases to be in `ACGTN`.\n\n If set to `true`, we expect bases to be `ACGTN`, and throw otherwise.\n If set to `false`, we will change any other base to be `N`.\n\nC++: genesis::population::SimplePileupReader::strict_bases(bool) --> class genesis::population::SimplePileupReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("with_quality_string", (bool (genesis::population::SimplePileupReader::*)() const) &genesis::population::SimplePileupReader::with_quality_string, "C++: genesis::population::SimplePileupReader::with_quality_string() const --> bool");
		cl.def("with_quality_string", (class genesis::population::SimplePileupReader & (genesis::population::SimplePileupReader::*)(bool)) &genesis::population::SimplePileupReader::with_quality_string, "Set whether to expect a phred-scaled, ASCII-encoded quality code string per\n sample.\n\n A typical line from a pileup file looks like\n\n     seq1 272 T 24  ,.$.....,,.,.,...,,,.,..^+. <<<+;<<<<<<<<<<<=<;<;7<&\n\n with the last field being quality codes. However, this last field is optional, and hence\n we offer this option. If `true` (default), the field is expected to be there; if `false`,\n it is expected not to be there. That is, at the moment, we have no automatic setting for this.\n\n See quality_encoding() for changing the encoding that is used in this column. Default\n is Sanger encoding. See ::genesis::sequence::QualityEncoding for details.\n\nC++: genesis::population::SimplePileupReader::with_quality_string(bool) --> class genesis::population::SimplePileupReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("quality_encoding", (enum genesis::sequence::QualityEncoding (genesis::population::SimplePileupReader::*)() const) &genesis::population::SimplePileupReader::quality_encoding, "C++: genesis::population::SimplePileupReader::quality_encoding() const --> enum genesis::sequence::QualityEncoding");
		cl.def("quality_encoding", (class genesis::population::SimplePileupReader & (genesis::population::SimplePileupReader::*)(enum genesis::sequence::QualityEncoding)) &genesis::population::SimplePileupReader::quality_encoding, "Set the type of encoding for the quality code string.\n\n If with_quality_string() is set to `true` (default), this encoding is used to transform\n the ASCII-encoded string into actual phred-scaled scores. See\n sequence::quality_decode_to_phred_score() for details.\n\nC++: genesis::population::SimplePileupReader::quality_encoding(enum genesis::sequence::QualityEncoding) --> class genesis::population::SimplePileupReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("quality_code_counts", (const struct std::array<unsigned long, 128> & (genesis::population::SimplePileupReader::*)() const) &genesis::population::SimplePileupReader::quality_code_counts, "Return the counts for all quality base codes found so far when parsing an input.\n\n Only available when read_records() or parse_line_record() are used;\n not availablef or the Variant-based reading functions.\n\n While parsing with_quality_string(), we keep track of the counts of each quality code found,\n so that we can check that the right encoding was used (for user friendliness).\n Counts here are simply indexed by their ASCII values.\n\nC++: genesis::population::SimplePileupReader::quality_code_counts() const --> const struct std::array<unsigned long, 128> &", pybind11::return_value_policy::reference_internal);
		cl.def("with_ancestral_base", (bool (genesis::population::SimplePileupReader::*)() const) &genesis::population::SimplePileupReader::with_ancestral_base, "C++: genesis::population::SimplePileupReader::with_ancestral_base() const --> bool");
		cl.def("with_ancestral_base", (class genesis::population::SimplePileupReader & (genesis::population::SimplePileupReader::*)(bool)) &genesis::population::SimplePileupReader::with_ancestral_base, "Set whether to expect the base of the ancestral allele as the last part of each\n sample in a record line.\n\n This is a pileup extension used by Pool-HMM (Boitard et al 2013) to denote the ancestral\n allele of each position directly within the pipleup file. Set to true when this is present\n in the input.\n\n A typical line from a pileup file with ancestral bases looks like\n\n     2L	30	A	15	aaaAaaaAaAAaaAa	PY^`ZaaV[_S	A\n\n which contains the three fixed columns, and then four columns for the sample, with the\n last one `A` being the ancestral allele for that sample.\n\nC++: genesis::population::SimplePileupReader::with_ancestral_base(bool) --> class genesis::population::SimplePileupReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("min_base_quality", (unsigned long (genesis::population::SimplePileupReader::*)() const) &genesis::population::SimplePileupReader::min_base_quality, "Get the currently set minimum phred quality score that a base needs to have\n to be added to the Variant BaseCounts for a sample.\n\n This is only used for the reading and parsing functions that return Variant%s.\n\nC++: genesis::population::SimplePileupReader::min_base_quality() const --> unsigned long");
		cl.def("min_base_quality", (class genesis::population::SimplePileupReader & (genesis::population::SimplePileupReader::*)(unsigned long)) &genesis::population::SimplePileupReader::min_base_quality, "Set the minimum phred quality score that a base needs to have\n to be added to the Variant BaseCounts for a sample.\n\n Bases below this quality score are ignored when summing up the counts per sample.\n Default is 0, meaning that all bases are used.\n\n This is only used for the reading and parsing functions that return Variant%s.\n When reading a Sample instead, all bases and their quality scores are in the output.\n\nC++: genesis::population::SimplePileupReader::min_base_quality(unsigned long) --> class genesis::population::SimplePileupReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));

		{ // genesis::population::SimplePileupReader::Sample file:genesis/population/formats/simple_pileup_reader.hpp line:103
			auto & enclosing_class = cl;
			pybind11::class_<genesis::population::SimplePileupReader::Sample, std::shared_ptr<genesis::population::SimplePileupReader::Sample>> cl(enclosing_class, "Sample", "One sample in a pileup line/record.\n\n Each sample in a pileup file corresponds to the reads of one sample that cover a certain\n position on a chromosome, and consists of two or three entries/columns in the file:\n\n  1. A read count.\n  2. A list of bases (and some other information on read start and end etc) from the reads\n     that cover the given position on the chromosome.\n  3. (Optionally) A list of phread-scaled ASCII-encoded quality scores for the list of bases.\n  4. (Optionally) The ancestral base at the position (some pileup files have this).\n\n As this here is a simple reader, we ignore the information on read starts/ends, as well as\n potential insertions and deletions (indels), and instead simply tally up the number of\n actual bases of the reads that cover a position. This Sample struct here collects this\n information.");
			cl.def( pybind11::init( [](genesis::population::SimplePileupReader::Sample const &o){ return new genesis::population::SimplePileupReader::Sample(o); } ) );
			cl.def( pybind11::init( [](){ return new genesis::population::SimplePileupReader::Sample(); } ) );
			cl.def_readwrite("read_coverage", &genesis::population::SimplePileupReader::Sample::read_coverage);
			cl.def_readwrite("read_bases", &genesis::population::SimplePileupReader::Sample::read_bases);
			cl.def_readwrite("phred_scores", &genesis::population::SimplePileupReader::Sample::phred_scores);
			cl.def_readwrite("ancestral_base", &genesis::population::SimplePileupReader::Sample::ancestral_base);
			cl.def("assign", (struct genesis::population::SimplePileupReader::Sample & (genesis::population::SimplePileupReader::Sample::*)(const struct genesis::population::SimplePileupReader::Sample &)) &genesis::population::SimplePileupReader::Sample::operator=, "C++: genesis::population::SimplePileupReader::Sample::operator=(const struct genesis::population::SimplePileupReader::Sample &) --> struct genesis::population::SimplePileupReader::Sample &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		}

		{ // genesis::population::SimplePileupReader::Record file:genesis/population/formats/simple_pileup_reader.hpp line:152
			auto & enclosing_class = cl;
			pybind11::class_<genesis::population::SimplePileupReader::Record, std::shared_ptr<genesis::population::SimplePileupReader::Record>> cl(enclosing_class, "Record", "Single line/record from a pileup file.\n\n A line consists of a chromosome and position, the reference base at that position,\n as well as one or more Sample%s, that is, information on reads (and optionally, their quality\n scores) that cover that position. See Sample for details on the latter.");
			cl.def( pybind11::init( [](genesis::population::SimplePileupReader::Record const &o){ return new genesis::population::SimplePileupReader::Record(o); } ) );
			cl.def( pybind11::init( [](){ return new genesis::population::SimplePileupReader::Record(); } ) );
			cl.def_readwrite("chromosome", &genesis::population::SimplePileupReader::Record::chromosome);
			cl.def_readwrite("position", &genesis::population::SimplePileupReader::Record::position);
			cl.def_readwrite("reference_base", &genesis::population::SimplePileupReader::Record::reference_base);
			cl.def_readwrite("samples", &genesis::population::SimplePileupReader::Record::samples);
			cl.def("assign", (struct genesis::population::SimplePileupReader::Record & (genesis::population::SimplePileupReader::Record::*)(const struct genesis::population::SimplePileupReader::Record &)) &genesis::population::SimplePileupReader::Record::operator=, "C++: genesis::population::SimplePileupReader::Record::operator=(const struct genesis::population::SimplePileupReader::Record &) --> struct genesis::population::SimplePileupReader::Record &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		}

	}
}
