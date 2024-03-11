#include <functional>
#include <genesis/sequence/formats/fastq_reader.hpp>
#include <genesis/sequence/functions/quality.hpp>
#include <genesis/sequence/sequence.hpp>
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

void bind_genesis_sequence_functions_quality(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// genesis::sequence::error_probability_to_solexa_score(double) file:genesis/sequence/functions/quality.hpp line:230
	M("genesis::sequence").def("error_probability_to_solexa_score", (signed char (*)(double)) &genesis::sequence::error_probability_to_solexa_score, "C++: genesis::sequence::error_probability_to_solexa_score(double) --> signed char", pybind11::arg("error_probability"));

	// genesis::sequence::error_probability_to_solexa_score(class std::vector<double, class std::allocator<double> >) file:genesis/sequence/functions/quality.hpp line:231
	M("genesis::sequence").def("error_probability_to_solexa_score", (class std::vector<signed char, class std::allocator<signed char> > (*)(class std::vector<double, class std::allocator<double> >)) &genesis::sequence::error_probability_to_solexa_score, "C++: genesis::sequence::error_probability_to_solexa_score(class std::vector<double, class std::allocator<double> >) --> class std::vector<signed char, class std::allocator<signed char> >", pybind11::arg("error_probability"));

	// genesis::sequence::solexa_score_to_error_probability(signed char) file:genesis/sequence/functions/quality.hpp line:233
	M("genesis::sequence").def("solexa_score_to_error_probability", (double (*)(signed char)) &genesis::sequence::solexa_score_to_error_probability, "C++: genesis::sequence::solexa_score_to_error_probability(signed char) --> double", pybind11::arg("solexa_score"));

	// genesis::sequence::solexa_score_to_error_probability(class std::vector<signed char, class std::allocator<signed char> >) file:genesis/sequence/functions/quality.hpp line:234
	M("genesis::sequence").def("solexa_score_to_error_probability", (class std::vector<double, class std::allocator<double> > (*)(class std::vector<signed char, class std::allocator<signed char> >)) &genesis::sequence::solexa_score_to_error_probability, "C++: genesis::sequence::solexa_score_to_error_probability(class std::vector<signed char, class std::allocator<signed char> >) --> class std::vector<double, class std::allocator<double> >", pybind11::arg("solexa_score"));

	// genesis::sequence::phred_score_to_solexa_score(unsigned char) file:genesis/sequence/functions/quality.hpp line:236
	M("genesis::sequence").def("phred_score_to_solexa_score", (signed char (*)(unsigned char)) &genesis::sequence::phred_score_to_solexa_score, "C++: genesis::sequence::phred_score_to_solexa_score(unsigned char) --> signed char", pybind11::arg("phred_score"));

	// genesis::sequence::phred_score_to_solexa_score(class std::vector<unsigned char, class std::allocator<unsigned char> >) file:genesis/sequence/functions/quality.hpp line:237
	M("genesis::sequence").def("phred_score_to_solexa_score", (class std::vector<signed char, class std::allocator<signed char> > (*)(class std::vector<unsigned char, class std::allocator<unsigned char> >)) &genesis::sequence::phred_score_to_solexa_score, "C++: genesis::sequence::phred_score_to_solexa_score(class std::vector<unsigned char, class std::allocator<unsigned char> >) --> class std::vector<signed char, class std::allocator<signed char> >", pybind11::arg("phred_score"));

	// genesis::sequence::solexa_score_to_phred_score(signed char) file:genesis/sequence/functions/quality.hpp line:239
	M("genesis::sequence").def("solexa_score_to_phred_score", (unsigned char (*)(signed char)) &genesis::sequence::solexa_score_to_phred_score, "C++: genesis::sequence::solexa_score_to_phred_score(signed char) --> unsigned char", pybind11::arg("solexa_score"));

	// genesis::sequence::solexa_score_to_phred_score(class std::vector<signed char, class std::allocator<signed char> >) file:genesis/sequence/functions/quality.hpp line:240
	M("genesis::sequence").def("solexa_score_to_phred_score", (class std::vector<unsigned char, class std::allocator<unsigned char> > (*)(class std::vector<signed char, class std::allocator<signed char> >)) &genesis::sequence::solexa_score_to_phred_score, "C++: genesis::sequence::solexa_score_to_phred_score(class std::vector<signed char, class std::allocator<signed char> >) --> class std::vector<unsigned char, class std::allocator<unsigned char> >", pybind11::arg("solexa_score"));

	{ // genesis::sequence::FastqReader file:genesis/sequence/formats/fastq_reader.hpp line:149
		pybind11::class_<genesis::sequence::FastqReader, std::shared_ptr<genesis::sequence::FastqReader>> cl(M("genesis::sequence"), "FastqReader", "Read Fastq sequence data.\n\n This class provides simple facilities for reading Fastq data.\n\n Exemplary usage:\n\n     std::string infile = \"path/to/file.fastq\";\n     SequenceSet sequence_set;\n\n     FastqReader()\n         .site_casing( SiteCasing::kUnchanged )\n         .valid_chars( nucleic_acid_codes_all() )\n         .read( utils::from_file( infile ), sequence_set );\n\n The expected data format is:\n\n  1. Line 1 begins with a '@' character and is followed by a sequence identifier (label)\n     and an optional description (like a FASTA title line, see FastaReader for details).\n  2. Line 2 (or more) is the raw sequence letters. In contrast to most other readers,\n     we allow the sequence to use several lines.\n  3. Line 3 begins with a '+' character and is optionally followed by the same sequence identifier\n     (and any description) again. If this line is not empty, it has to be identical to line 1.\n  4. Line 4 (or more) encodes the quality values for the sequence in Line 2, and must contain\n     the same number of symbols as there were letters in the sequence (line 2).\n\n See https://en.wikipedia.org/wiki/FASTQ_format for details.\n\n As the encoding for the quality values can be substantially different depending on the sequencing\n techonology used, parsing fastq files is more difficult than fasta. Two issues arise:\n\n  *  The quality encoding can be different depending on the used sequencing techonology. The most\n     prominent difference is the used ASCII base for the phred quality scores.\n     See https://en.wikipedia.org/wiki/FASTQ_format for a thorough discussion, or the article\n     cited below [1]. Solexa even uses a different function to compute scores, making it even more\n     complicated. We tried to make the standard use case as easy as possible, as explained below.\n  *  Most parsers expect the four lines as above without line breaks in between them. This is because\n     the quality encoding might use the characters '@' and '+', which are also used as the starting\n     characters for the first and third line, respectively (we here ignore the fact that,\n     in theory, the seqeunce letters themselves could also be different than 'ACGT' and their\n     degenerates, as this is also not defined in the format...).\n     This simple format does work here as well. However, we are nice and also\n     support line breaks. \n     There is only one edge case where this breaks. If the sequence sites (line 2) contain a '+'\n     character at the beginning of a wrapped line (i.e., immediately after a line break),\n     we cannot distinguish this from the beginning of line 3.\n     Unfortunately, this is an issue of the format itself that cannot be solved in a parser, as\n     this is simply ill-defined. \n     However, standard nucleic acid or amino acid codes do not use the `+` character, so\n     this should rarely be an issue in practice.\n\n By default, we interpret quality values as phred scores in the Sanger format, that is,\n use an ASCII offset of 33, where '!' stands for the lowest phred quality score of 0.\n To change the encoding, use the quality_encoding() function, which accepts Sanger, Solexa,\n and different Illumina versions.\n\n For even more advanced used cases, the whole function for parsing the quality string can be changed\n as well, by setting the quality_string_plugin() function. This is for example useful if the\n quality scores are not needed at all (simply provide an empty function in this case), or if\n the file is first parsed once to detect the most probably encoding - see\n guess_fastq_quality_encoding() for an example.\n\n To set the the quality_string_plugin(), use for example the following:\n\n     auto reader = FastqReader();\n     reader.quality_string_plugin(\n         [&]( std::string const& quality_string, Sequence& sequence )\n         {\n             // do something with the quality_string, and potentially store it in the sequence\n         }\n     );\n     reader.read( utils::from_file( infile ), sequence_set );\n\n More information on the format can be found at:\n\n > [1] P. Cock, C. Fields, N. Goto, M. Heuer, P. Rice.\n > \"The Sanger FASTQ file format for sequences with quality scores,\n > and the Solexa/Illumina FASTQ variants.\"\n > Nucleic Acids Research, 38(6), 1767–1771, 2009.\n > https://doi.org/10.1093/nar/gkp1137\n\n Using site_casing(), the sequences can automatically be turned into upper or lower case letter.\n Also, see valid_chars( std::string const& chars ) for a way of checking correct input sequences.");
		cl.def( pybind11::init( [](){ return new genesis::sequence::FastqReader(); } ) );
		cl.def( pybind11::init( [](genesis::sequence::FastqReader const &o){ return new genesis::sequence::FastqReader(o); } ) );

		pybind11::enum_<genesis::sequence::FastqReader::SiteCasing>(cl, "SiteCasing", "Enumeration of casing methods to apply to each site of a Sequence.")
			.value("kUnchanged", genesis::sequence::FastqReader::SiteCasing::kUnchanged)
			.value("kToUpper", genesis::sequence::FastqReader::SiteCasing::kToUpper)
			.value("kToLower", genesis::sequence::FastqReader::SiteCasing::kToLower);

		cl.def("assign", (class genesis::sequence::FastqReader & (genesis::sequence::FastqReader::*)(const class genesis::sequence::FastqReader &)) &genesis::sequence::FastqReader::operator=, "C++: genesis::sequence::FastqReader::operator=(const class genesis::sequence::FastqReader &) --> class genesis::sequence::FastqReader &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("read", (class genesis::sequence::SequenceSet (genesis::sequence::FastqReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>) const) &genesis::sequence::FastqReader::read, "Read all Sequence%s from an input source in Fastq format and return them as a\n SequenceSet.\n\n Use functions such as utils::from_file() and utils::from_string() to conveniently\n get an input source that can be used here.\n\nC++: genesis::sequence::FastqReader::read(class std::shared_ptr<class genesis::utils::BaseInputSource>) const --> class genesis::sequence::SequenceSet", pybind11::arg("source"));
		cl.def("read", (void (genesis::sequence::FastqReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>, class genesis::sequence::SequenceSet &) const) &genesis::sequence::FastqReader::read, "Read all Sequence%s from an input source in Fastq format into a SequenceSet.\n\n The Sequences are added to the SequenceSet, whose existing Sequences are kept. Thus, by\n repeatedly calling this or similar read functions, multiple input files can easily be read\n into one SequenceSet.\n\n Use functions such as utils::from_file() and utils::from_string() to conveniently\n get an input source that can be used here.\n\nC++: genesis::sequence::FastqReader::read(class std::shared_ptr<class genesis::utils::BaseInputSource>, class genesis::sequence::SequenceSet &) const --> void", pybind11::arg("source"), pybind11::arg("sequence_set"));
		cl.def("parse_document", (void (genesis::sequence::FastqReader::*)(class genesis::utils::InputStream &, class genesis::sequence::SequenceSet &) const) &genesis::sequence::FastqReader::parse_document, "Parse a whole fastq document into a SequenceSet.\n\n This function is mainly used internally by the reading functions read().\n It is however also fine to call it from the outside.\n\nC++: genesis::sequence::FastqReader::parse_document(class genesis::utils::InputStream &, class genesis::sequence::SequenceSet &) const --> void", pybind11::arg("input_stream"), pybind11::arg("sequence_set"));
		cl.def("parse_sequence", (bool (genesis::sequence::FastqReader::*)(class genesis::utils::InputStream &, class genesis::sequence::Sequence &) const) &genesis::sequence::FastqReader::parse_sequence, "Parse a Sequence in Fastq format.\n\n This function takes an utils::InputStream and interprets it as a Fastq formatted sequence.\n It extracts the data and writes it into the given Sequence object. See the class description\n of FastqReader for the expected data format.\n\n The function stops after parsing one such sequence, and leaves the stream at the first\n character of the next line that follows the quality score string. It returns true if a\n sequence was extracted and false if the stream is empty. If the input is not in the correct\n format, an `std::runtime_error` exception is thrown indicating the malicious position in the\n input stream.\n\nC++: genesis::sequence::FastqReader::parse_sequence(class genesis::utils::InputStream &, class genesis::sequence::Sequence &) const --> bool", pybind11::arg("input_stream"), pybind11::arg("sequence"));
		cl.def("site_casing", (class genesis::sequence::FastqReader & (genesis::sequence::FastqReader::*)(enum genesis::sequence::FastqReader::SiteCasing)) &genesis::sequence::FastqReader::site_casing, "Set whether Sequence sites are automatically turned into upper or lower case.\n\n Default is SiteCasing::kToUpper, that is, all sites of the read Sequences are turned into\n upper case letters automatically. This is typical behaviour, although not standardized.\n The function returns the FastqReader object to allow for fluent interfaces.\n\nC++: genesis::sequence::FastqReader::site_casing(enum genesis::sequence::FastqReader::SiteCasing) --> class genesis::sequence::FastqReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("site_casing", (enum genesis::sequence::FastqReader::SiteCasing (genesis::sequence::FastqReader::*)() const) &genesis::sequence::FastqReader::site_casing, "Return whether Sequence sites are automatically turned into upper or lower case.\n\nC++: genesis::sequence::FastqReader::site_casing() const --> enum genesis::sequence::FastqReader::SiteCasing");
		cl.def("valid_chars", (class genesis::sequence::FastqReader & (genesis::sequence::FastqReader::*)(const std::string &)) &genesis::sequence::FastqReader::valid_chars, "Set the chars that are used for validating Sequence sites when reading them.\n\n When this function is called with a string of chars, those chars are used to validate the\n sites when reading them. That is, only sequences consisting of the given chars are valid.\n\n If set to an empty string, this check is deactivated. This is also the default, meaning that\n no checking is done.\n\n In case that site_casing() is set to a value other than `SiteCasing::kUnchanged`:\n The validation is done after changing the casing, so that only lower or capital letters have\n to be provided for validation. In case that site_casing() is set to `SiteCasing::kUnchanged`:\n All chars that are to be considered valid have to be provided for validation.\n\n See `nucleic_acid_codes...()` and `amino_acid_codes...()` functions for presettings of chars\n that can be used for validation here.\n\nC++: genesis::sequence::FastqReader::valid_chars(const std::string &) --> class genesis::sequence::FastqReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("chars"));
		cl.def("valid_chars", (std::string (genesis::sequence::FastqReader::*)() const) &genesis::sequence::FastqReader::valid_chars, "Return the currently set chars used for validating Sequence sites.\n\n An empty string means that no validation is done.\n\nC++: genesis::sequence::FastqReader::valid_chars() const --> std::string");
		cl.def("valid_char_lookup", (class genesis::utils::CharLookup<bool> & (genesis::sequence::FastqReader::*)()) &genesis::sequence::FastqReader::valid_char_lookup, "Return the internal CharLookup that is used for validating the Sequence sites.\n\n This function is provided in case direct access to the lookup is needed. Usually, the\n valid_chars() function should suffice. See there for details.\n\nC++: genesis::sequence::FastqReader::valid_char_lookup() --> class genesis::utils::CharLookup<bool> &", pybind11::return_value_policy::reference_internal);
		cl.def("quality_encoding", (class genesis::sequence::FastqReader & (genesis::sequence::FastqReader::*)(enum genesis::sequence::QualityEncoding)) &genesis::sequence::FastqReader::quality_encoding, "Set the QualityEncoding used for decoding the quality score line of the Fastq file.\n\n By default, we use Sanger encoding. This can be changed here.\n\nC++: genesis::sequence::FastqReader::quality_encoding(enum genesis::sequence::QualityEncoding) --> class genesis::sequence::FastqReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("encoding"));
		cl.def("quality_encoding", (enum genesis::sequence::QualityEncoding (genesis::sequence::FastqReader::*)()) &genesis::sequence::FastqReader::quality_encoding, "Return the currently set QualityEncoding that is used for decoding the quality score\n line of the Fastq file.\n\nC++: genesis::sequence::FastqReader::quality_encoding() --> enum genesis::sequence::QualityEncoding");
		cl.def("quality_string_plugin", (class genesis::sequence::FastqReader & (genesis::sequence::FastqReader::*)(const class std::function<void (const std::string &, class genesis::sequence::Sequence &)> &)) &genesis::sequence::FastqReader::quality_string_plugin, "Functional that can be set to process the quality string found in fastq files.\n\n See the class description for details.\n\nC++: genesis::sequence::FastqReader::quality_string_plugin(const class std::function<void (const std::string &, class genesis::sequence::Sequence &)> &) --> class genesis::sequence::FastqReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("plugin"));
	}
}
