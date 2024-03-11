#include <functional>
#include <genesis/sequence/formats/fasta_reader.hpp>
#include <genesis/sequence/reference_genome.hpp>
#include <genesis/sequence/sequence.hpp>
#include <genesis/sequence/sequence_dict.hpp>
#include <genesis/sequence/sequence_set.hpp>
#include <genesis/utils/io/base_input_source.hpp>
#include <genesis/utils/io/input_stream.hpp>
#include <genesis/utils/tools/char_lookup.hpp>
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
#include <../python/custom_bindings/extensions/utils/matrix.hpp>
#include <genesis/utils/color/functions.hpp>
#include <../python/custom_bindings/extensions/utils/bitvector.hpp>
#include <../python/custom_bindings/extensions/utils/range.hpp>
#include <../python/custom_bindings/extensions/string_target.hpp>
#include <../python/custom_bindings/extensions/sequence/quality.hpp>
#include <../python/custom_bindings/extensions/sequence/sequence_set.hpp>
#include <../python/custom_bindings/extensions/sequence/sequence_dict.hpp>
#include <../python/custom_bindings/extensions/sequence/fasta_input_iterator.hpp>
#include <../python/custom_bindings/extensions/sequence/fastq_input_iterator.hpp>
#include <../python/custom_bindings/extensions/sequence/reference_genome.hpp>
#include <../python/custom_bindings/extensions/taxonomy/taxopath.hpp>
#include <../python/custom_bindings/extensions/taxonomy/iterator.hpp>
#include <../python/custom_bindings/extensions/tree/tree.hpp>
#include <../python/custom_bindings/extensions/tree/functions_tree.hpp>
#include <pybind11/stl.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_genesis_sequence_reference_genome(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // genesis::sequence::ReferenceGenome file:genesis/sequence/reference_genome.hpp line:65
		pybind11::class_<genesis::sequence::ReferenceGenome, std::shared_ptr<genesis::sequence::ReferenceGenome>> cl(M("genesis::sequence"), "ReferenceGenome", "Lookup of Sequence%s of a reference genome.\n\n The class stores Sequence%s in the order they are added, but also stores a hash map for quickly\n finding a Sequence given its name/label, as well as a lookup of bases at positions in the genome.\n\n \n SequenceDict");
		cl.def( pybind11::init( [](){ return new genesis::sequence::ReferenceGenome(); } ) );
		cl.def("size", (unsigned long (genesis::sequence::ReferenceGenome::*)() const) &genesis::sequence::ReferenceGenome::size, "Return the number of Sequence%s in the ReferenceGenome.\n\nC++: genesis::sequence::ReferenceGenome::size() const --> unsigned long");
		cl.def("empty", (bool (genesis::sequence::ReferenceGenome::*)() const) &genesis::sequence::ReferenceGenome::empty, "Return whether the ReferenceGenome is empty, i.e. whether its size() is 0.\n\nC++: genesis::sequence::ReferenceGenome::empty() const --> bool");
		cl.def("contains", (bool (genesis::sequence::ReferenceGenome::*)(const std::string &) const) &genesis::sequence::ReferenceGenome::contains, "C++: genesis::sequence::ReferenceGenome::contains(const std::string &) const --> bool", pybind11::arg("label"));
		cl.def("get", (const class genesis::sequence::Sequence & (genesis::sequence::ReferenceGenome::*)(const std::string &) const) &genesis::sequence::ReferenceGenome::get, "Same as find(), but returns the sequence directly, or throws if not present.\n\nC++: genesis::sequence::ReferenceGenome::get(const std::string &) const --> const class genesis::sequence::Sequence &", pybind11::return_value_policy::reference_internal, pybind11::arg("label"));
		cl.def("get_base", [](genesis::sequence::ReferenceGenome const &o, const std::string & a0, unsigned long const & a1) -> char { return o.get_base(a0, a1); }, "", pybind11::arg("chromosome"), pybind11::arg("position"));
		cl.def("get_base", (char (genesis::sequence::ReferenceGenome::*)(const std::string &, unsigned long, bool) const) &genesis::sequence::ReferenceGenome::get_base, "Get a particular base at a given chromosome and position.\n\n Reference genomes are often used to look up a particular base, so we offer this functionality\n here directly. The function throws if either the chromosome is not part of the genome,\n or if the position is outside of the size of the chromosome.\n\n Important: We here use 1-based indexing for the position, which differs from a direct lookup\n using the sites of the sequence directly, but is more in line with the usage in our\n population functions.\n\nC++: genesis::sequence::ReferenceGenome::get_base(const std::string &, unsigned long, bool) const --> char", pybind11::arg("chromosome"), pybind11::arg("position"), pybind11::arg("to_upper"));
		cl.def("get_base", [](genesis::sequence::ReferenceGenome const &o, class __gnu_cxx::__normal_iterator<const class genesis::sequence::Sequence *, class std::vector<class genesis::sequence::Sequence, class std::allocator<class genesis::sequence::Sequence> > > const & a0, unsigned long const & a1) -> char { return o.get_base(a0, a1); }, "", pybind11::arg("it"), pybind11::arg("position"));
		cl.def("get_base", (char (genesis::sequence::ReferenceGenome::*)(class __gnu_cxx::__normal_iterator<const class genesis::sequence::Sequence *, class std::vector<class genesis::sequence::Sequence, class std::allocator<class genesis::sequence::Sequence> > >, unsigned long, bool) const) &genesis::sequence::ReferenceGenome::get_base, "Get a particular base at the given sequence iterator and position.\n\n This is intended as an optimization, when an iterator returned from find() is cached.\n That way, the lookup does not have to be performed for every position in the genome.\n\nC++: genesis::sequence::ReferenceGenome::get_base(class __gnu_cxx::__normal_iterator<const class genesis::sequence::Sequence *, class std::vector<class genesis::sequence::Sequence, class std::allocator<class genesis::sequence::Sequence> > >, unsigned long, bool) const --> char", pybind11::arg("it"), pybind11::arg("position"), pybind11::arg("to_upper"));
		cl.def("add", [](genesis::sequence::ReferenceGenome &o, const class genesis::sequence::Sequence & a0) -> const genesis::sequence::Sequence & { return o.add(a0); }, "", pybind11::return_value_policy::reference_internal, pybind11::arg("seq"));
		cl.def("add", (const class genesis::sequence::Sequence & (genesis::sequence::ReferenceGenome::*)(const class genesis::sequence::Sequence &, bool)) &genesis::sequence::ReferenceGenome::add, "Add a Sequence to the ReferenceGenome by copying it, and return a const_reference to it.\n\n If  is set (true by default), we add an additional look up name for\n the added sequence:\n In addition to its full name, it can also be looked up with just the first word, that is,\n until the first tab or space character, in case there are any, as this is what typical fasta\n indexing tools also seem to do. The sequence is still stored with its original name though,\n and just that additional lookup is added for using find() or get().\n\nC++: genesis::sequence::ReferenceGenome::add(const class genesis::sequence::Sequence &, bool) --> const class genesis::sequence::Sequence &", pybind11::return_value_policy::reference_internal, pybind11::arg("seq"), pybind11::arg("also_look_up_first_word"));
		cl.def("clear", (void (genesis::sequence::ReferenceGenome::*)()) &genesis::sequence::ReferenceGenome::clear, "Remove all Sequence%s from the ReferenceGenome, leaving it with a size() of 0.\n\nC++: genesis::sequence::ReferenceGenome::clear() --> void");
		cl.def("cbegin", (class __gnu_cxx::__normal_iterator<const class genesis::sequence::Sequence *, class std::vector<class genesis::sequence::Sequence, class std::allocator<class genesis::sequence::Sequence> > > (genesis::sequence::ReferenceGenome::*)() const) &genesis::sequence::ReferenceGenome::cbegin, "C++: genesis::sequence::ReferenceGenome::cbegin() const --> class __gnu_cxx::__normal_iterator<const class genesis::sequence::Sequence *, class std::vector<class genesis::sequence::Sequence, class std::allocator<class genesis::sequence::Sequence> > >");
		cl.def("cend", (class __gnu_cxx::__normal_iterator<const class genesis::sequence::Sequence *, class std::vector<class genesis::sequence::Sequence, class std::allocator<class genesis::sequence::Sequence> > > (genesis::sequence::ReferenceGenome::*)() const) &genesis::sequence::ReferenceGenome::cend, "C++: genesis::sequence::ReferenceGenome::cend() const --> class __gnu_cxx::__normal_iterator<const class genesis::sequence::Sequence *, class std::vector<class genesis::sequence::Sequence, class std::allocator<class genesis::sequence::Sequence> > >");

		extend_reference_genome(cl);
	}
	{ // genesis::sequence::FastaReader file:genesis/sequence/formats/fasta_reader.hpp line:91
		pybind11::class_<genesis::sequence::FastaReader, std::shared_ptr<genesis::sequence::FastaReader>> cl(M("genesis::sequence"), "FastaReader", "Read Fasta sequence data.\n\n This class provides simple facilities for reading Fasta data.\n\n Exemplary usage:\n\n     std::string infile = \"path/to/file.fasta\";\n     SequenceSet sequence_set;\n\n     FastaReader()\n         .site_casing( SiteCasing::kUnchanged )\n         .valid_chars( nucleic_acid_codes_all() )\n         .read( utils::from_file( infile ), sequence_set );\n\n The expected data format:\n\n   1. Has to start with a '>' character, followed by a label, ended by a '\\n'.\n   2. An arbitrary number of comment lines, starting with ';', can follow, but are ignored.\n   3. After that, a sequence has to follow, over one or more lines.\n\n More information on the format can be found at:\n\n    * http://en.wikipedia.org/wiki/FASTA_format\n    * http://blast.ncbi.nlm.nih.gov/blastcgihelp.shtml\n    * http://zhanglab.ccmb.med.umich.edu/FASTA/\n\n Using site_casing(), the sequences can automatically be turned into upper or lower case letter.\n Also, see valid_chars( std::string const& chars ) for a way of checking correct input sequences.");
		cl.def( pybind11::init( [](){ return new genesis::sequence::FastaReader(); } ) );
		cl.def( pybind11::init( [](genesis::sequence::FastaReader const &o){ return new genesis::sequence::FastaReader(o); } ) );

		pybind11::enum_<genesis::sequence::FastaReader::ParsingMethod>(cl, "ParsingMethod", "Enumeration of the available methods for parsing Fasta sequences.")
			.value("kDefault", genesis::sequence::FastaReader::ParsingMethod::kDefault)
			.value("kPedantic", genesis::sequence::FastaReader::ParsingMethod::kPedantic);


		pybind11::enum_<genesis::sequence::FastaReader::SiteCasing>(cl, "SiteCasing", "Enumeration of casing methods to apply to each site of a Sequence.")
			.value("kUnchanged", genesis::sequence::FastaReader::SiteCasing::kUnchanged)
			.value("kToUpper", genesis::sequence::FastaReader::SiteCasing::kToUpper)
			.value("kToLower", genesis::sequence::FastaReader::SiteCasing::kToLower);

		cl.def("assign", (class genesis::sequence::FastaReader & (genesis::sequence::FastaReader::*)(const class genesis::sequence::FastaReader &)) &genesis::sequence::FastaReader::operator=, "C++: genesis::sequence::FastaReader::operator=(const class genesis::sequence::FastaReader &) --> class genesis::sequence::FastaReader &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("read", (class genesis::sequence::SequenceSet (genesis::sequence::FastaReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>) const) &genesis::sequence::FastaReader::read, "Read all Sequence%s from an input source in Fasta format and return them as a\n SequenceSet.\n\n Use functions such as utils::from_file() and utils::from_string() to conveniently\n get an input source that can be used here.\n\nC++: genesis::sequence::FastaReader::read(class std::shared_ptr<class genesis::utils::BaseInputSource>) const --> class genesis::sequence::SequenceSet", pybind11::arg("source"));
		cl.def("read", (void (genesis::sequence::FastaReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>, class genesis::sequence::SequenceSet &) const) &genesis::sequence::FastaReader::read, "Read all Sequence%s from an input source in Fasta format into a SequenceSet.\n\n The Sequences are added to the SequenceSet, whose existing Sequences are kept. Thus, by\n repeatedly calling this or similar read functions, multiple input files can easily be read\n into one SequenceSet.\n\n Use functions such as utils::from_file() and utils::from_string() to conveniently\n get an input source that can be used here.\n\nC++: genesis::sequence::FastaReader::read(class std::shared_ptr<class genesis::utils::BaseInputSource>, class genesis::sequence::SequenceSet &) const --> void", pybind11::arg("source"), pybind11::arg("sequence_set"));
		cl.def("read_dict", (class genesis::sequence::SequenceDict (genesis::sequence::FastaReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>) const) &genesis::sequence::FastaReader::read_dict, "Read all Sequence%s from an input source in fasta format, but only return their\n names and lengths as a SequenceDict.\n\nC++: genesis::sequence::FastaReader::read_dict(class std::shared_ptr<class genesis::utils::BaseInputSource>) const --> class genesis::sequence::SequenceDict", pybind11::arg("source"));
		cl.def("read_reference_genome", [](genesis::sequence::FastaReader const &o, class std::shared_ptr<class genesis::utils::BaseInputSource> const & a0) -> genesis::sequence::ReferenceGenome { return o.read_reference_genome(a0); }, "", pybind11::arg("source"));
		cl.def("read_reference_genome", (class genesis::sequence::ReferenceGenome (genesis::sequence::FastaReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>, bool) const) &genesis::sequence::FastaReader::read_reference_genome, "Read all Sequence%s from an input source in fasta format into a ReferenceGenome.\n\n This allows fast lookup of sequences by their name, while maintaining their order.\n See ReferenceGenome for details, and for the explanation of \n     \n\nC++: genesis::sequence::FastaReader::read_reference_genome(class std::shared_ptr<class genesis::utils::BaseInputSource>, bool) const --> class genesis::sequence::ReferenceGenome", pybind11::arg("source"), pybind11::arg("also_look_up_first_word"));
		cl.def("parse_document", (void (genesis::sequence::FastaReader::*)(class genesis::utils::InputStream &, class genesis::sequence::SequenceSet &) const) &genesis::sequence::FastaReader::parse_document, "Parse a whole fasta document into a SequenceSet.\n\n This function is mainly used internally by the reading functions read().\n It uses the currently set parsing_method() for parsing the data.\n\nC++: genesis::sequence::FastaReader::parse_document(class genesis::utils::InputStream &, class genesis::sequence::SequenceSet &) const --> void", pybind11::arg("input_stream"), pybind11::arg("sequence_set"));
		cl.def("parse_sequence", (bool (genesis::sequence::FastaReader::*)(class genesis::utils::InputStream &, class genesis::sequence::Sequence &) const) &genesis::sequence::FastaReader::parse_sequence, "Parse a Sequence in Fasta format.\n\n This function takes an InputStream and interprets it as a Fasta formatted sequence. It extracts\n the data and writes it into the given Sequence object. See the class description of FastaReader\n for the expected data format.\n\n The function stops after parsing one such sequence. It returns true if a sequence was extracted\n and false if the stream is empty. If the input is not in the correct format, an\n `std::runtime_error` exception is thrown indicating the malicious position in the input stream.\n\nC++: genesis::sequence::FastaReader::parse_sequence(class genesis::utils::InputStream &, class genesis::sequence::Sequence &) const --> bool", pybind11::arg("input_stream"), pybind11::arg("sequence"));
		cl.def("parse_sequence_pedantic", (bool (genesis::sequence::FastaReader::*)(class genesis::utils::InputStream &, class genesis::sequence::Sequence &) const) &genesis::sequence::FastaReader::parse_sequence_pedantic, "Parse a Sequence in Fasta format.\n\n This function takes an InputStream and interprets it as a Fasta formatted sequence. It extracts\n the data and writes it into the given Sequence object. See the class description of FastaReader\n for the expected data format.\n\n The function stops after parsing one such sequence. It returns true if a sequence was extracted\n and false if the stream is empty. If the input is not in the correct format, an\n `std::runtime_error` exception is thrown indicating the malicious position in the input stream.\n\n Compared to parse_sequence(), this function reports errors at the exact line and column\n where they occur. It is however slower.\n Apart from that, there are no differences. See FastaReader::ParsingMethod for details.\n\nC++: genesis::sequence::FastaReader::parse_sequence_pedantic(class genesis::utils::InputStream &, class genesis::sequence::Sequence &) const --> bool", pybind11::arg("input_stream"), pybind11::arg("sequence"));
		cl.def("parsing_method", (class genesis::sequence::FastaReader & (genesis::sequence::FastaReader::*)(enum genesis::sequence::FastaReader::ParsingMethod)) &genesis::sequence::FastaReader::parsing_method, "Set the parsing method.\n\n The parsing method is used for all the reader functions and parse_document().\n See the \n\n\n\nC++: genesis::sequence::FastaReader::parsing_method(enum genesis::sequence::FastaReader::ParsingMethod) --> class genesis::sequence::FastaReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("parsing_method", (enum genesis::sequence::FastaReader::ParsingMethod (genesis::sequence::FastaReader::*)() const) &genesis::sequence::FastaReader::parsing_method, "Return the currently set parsing method.\n\n See the \n\n\nC++: genesis::sequence::FastaReader::parsing_method() const --> enum genesis::sequence::FastaReader::ParsingMethod");
		cl.def("site_casing", (class genesis::sequence::FastaReader & (genesis::sequence::FastaReader::*)(enum genesis::sequence::FastaReader::SiteCasing)) &genesis::sequence::FastaReader::site_casing, "Set whether Sequence sites are automatically turned into upper or lower case.\n\n Default is SiteCasing::kToUpper, that is, all sites of the read Sequences are turned into\n upper case letters automatically. This is demanded by the Fasta standard.\n The function returns the FastaReader object to allow for fluent interfaces.\n\nC++: genesis::sequence::FastaReader::site_casing(enum genesis::sequence::FastaReader::SiteCasing) --> class genesis::sequence::FastaReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("site_casing", (enum genesis::sequence::FastaReader::SiteCasing (genesis::sequence::FastaReader::*)() const) &genesis::sequence::FastaReader::site_casing, "Return whether Sequence sites are automatically turned into upper or lower case.\n\nC++: genesis::sequence::FastaReader::site_casing() const --> enum genesis::sequence::FastaReader::SiteCasing");
		cl.def("guess_abundances", (class genesis::sequence::FastaReader & (genesis::sequence::FastaReader::*)(bool)) &genesis::sequence::FastaReader::guess_abundances, "Set whether Sequence labels are used to guess/extract Sequence abundances\n\n Default is `false`, that is, labels are just taken as they are in the input.\n If set to `true`, the label is used to guess an abundance count, which is set in the Sequence.\n See guess_sequence_abundance( Sequence const& ) for the valid formats of such abundances.\n\nC++: genesis::sequence::FastaReader::guess_abundances(bool) --> class genesis::sequence::FastaReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("guess_abundances", (bool (genesis::sequence::FastaReader::*)() const) &genesis::sequence::FastaReader::guess_abundances, "Return whether the label is used to guess/extracat Sequence abundances.\n\nC++: genesis::sequence::FastaReader::guess_abundances() const --> bool");
		cl.def("valid_chars", (class genesis::sequence::FastaReader & (genesis::sequence::FastaReader::*)(const std::string &)) &genesis::sequence::FastaReader::valid_chars, "Set the chars that are used for validating Sequence sites when reading them.\n\n When this function is called with a string of chars, those chars are used to validate the\n sites when reading them. That is, only sequences consisting of the given chars are valid.\n\n If set to an empty string, this check is deactivated. This is also the default, meaning that\n no checking is done.\n\n In case that site_casing() is set to a value other than `SiteCasing::kUnchanged`:\n The validation is done after changing the casing, so that only lower or capital letters have\n to be provided for validation. In case that site_casing() is set to `SiteCasing::kUnchanged`:\n All chars that are to be considered valid have to be provided for validation.\n\n See `nucleic_acid_codes...()` and `amino_acid_codes...()` functions for presettings of chars\n that can be used for validation here.\n\nC++: genesis::sequence::FastaReader::valid_chars(const std::string &) --> class genesis::sequence::FastaReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("chars"));
		cl.def("valid_chars", (std::string (genesis::sequence::FastaReader::*)() const) &genesis::sequence::FastaReader::valid_chars, "Return the currently set chars used for validating Sequence sites.\n\n An empty string means that no validation is done.\n\nC++: genesis::sequence::FastaReader::valid_chars() const --> std::string");
		cl.def("valid_char_lookup", (class genesis::utils::CharLookup<bool> & (genesis::sequence::FastaReader::*)()) &genesis::sequence::FastaReader::valid_char_lookup, "Return the internal CharLookup that is used for validating the Sequence sites.\n\n This function is provided in case direct access to the lookup is needed. Usually, the\n valid_chars() function should suffice. See there for details.\n\nC++: genesis::sequence::FastaReader::valid_char_lookup() --> class genesis::utils::CharLookup<bool> &", pybind11::return_value_policy::reference_internal);
	}
}
