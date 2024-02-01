#include <functional>
#include <genesis/sequence/counts.hpp>
#include <genesis/sequence/formats/phylip_reader.hpp>
#include <genesis/sequence/functions/consensus.hpp>
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
#include <../python/custom_bindings/extensions/to_string.hpp>
#include <../python/custom_bindings/extensions/sequence/quality.hpp>
#include <../python/custom_bindings/extensions/sequence/sequence_set.hpp>
#include <../python/custom_bindings/extensions/sequence/sequence_dict.hpp>
#include <../python/custom_bindings/extensions/sequence/fasta_input_iterator.hpp>
#include <../python/custom_bindings/extensions/sequence/fastq_input_iterator.hpp>
#include <../python/custom_bindings/extensions/sequence/fasta_output_iterator.hpp>
#include <../python/custom_bindings/extensions/sequence/reference_genome.hpp>
#include <../python/custom_bindings/extensions/taxonomy/taxopath.hpp>
#include <../python/custom_bindings/extensions/taxonomy/iterator.hpp>
#include <../python/custom_bindings/extensions/tree/tree.hpp>
#include <../python/custom_bindings/extensions/tree/functions_tree.hpp>
#include <genesis/population/genome_region_list.hpp>
#include <../python/custom_bindings/extensions/population/chromosome_iterator.hpp>
#include <pybind11/stl.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_genesis_sequence_formats_phylip_reader(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // genesis::sequence::PhylipReader file:genesis/sequence/formats/phylip_reader.hpp line:86
		pybind11::class_<genesis::sequence::PhylipReader, std::shared_ptr<genesis::sequence::PhylipReader>> cl(M("genesis::sequence"), "PhylipReader", "Read Phylip sequence data.\n\n This class provides simple facilities for reading Phylip data.\n\n Exemplary usage:\n\n     std::string infile = \"path/to/file.phylip\";\n     SequenceSet sset;\n\n     PhylipReader()\n         .site_casing( SiteCasing::kUnchanged )\n         .valid_chars( nucleic_acid_codes_all() )\n         .read( utils::from_file( infile ), sset );\n\n The expected data format roughly follows\n [the original definition](http://evolution.genetics.washington.edu/phylip/doc/sequence.html).\n See mode( Mode ) to selected between sequential and interleaved mode, which are the two\n variants of Phylip files.\n We furthermore support a relaxed version (by default), where the label can be of any length.\n See label_length( size_t ) for more information.\n\n Using site_casing(), the sequences can automatically be turned into upper or lower case letter.\n Also, see valid_chars( std::string const& ) for a way of checking correct input sequences.");
		cl.def( pybind11::init( [](){ return new genesis::sequence::PhylipReader(); } ) );
		cl.def( pybind11::init( [](genesis::sequence::PhylipReader const &o){ return new genesis::sequence::PhylipReader(o); } ) );

		pybind11::enum_<genesis::sequence::PhylipReader::Mode>(cl, "Mode", "Enum to distinguish between the different file variants of Phylip.\n See mode( Mode value ) for more details.")
			.value("kSequential", genesis::sequence::PhylipReader::Mode::kSequential)
			.value("kInterleaved", genesis::sequence::PhylipReader::Mode::kInterleaved);


		pybind11::enum_<genesis::sequence::PhylipReader::SiteCasing>(cl, "SiteCasing", "Enumeration of casing methods to apply to each site of a Sequence.")
			.value("kUnchanged", genesis::sequence::PhylipReader::SiteCasing::kUnchanged)
			.value("kToUpper", genesis::sequence::PhylipReader::SiteCasing::kToUpper)
			.value("kToLower", genesis::sequence::PhylipReader::SiteCasing::kToLower);

		cl.def("assign", (class genesis::sequence::PhylipReader & (genesis::sequence::PhylipReader::*)(const class genesis::sequence::PhylipReader &)) &genesis::sequence::PhylipReader::operator=, "C++: genesis::sequence::PhylipReader::operator=(const class genesis::sequence::PhylipReader &) --> class genesis::sequence::PhylipReader &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("read", (class genesis::sequence::SequenceSet (genesis::sequence::PhylipReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>) const) &genesis::sequence::PhylipReader::read, "Read all Sequence%s from an input source in Phylip format and return them as a\n SequenceSet.\n\n Use functions such as utils::from_file() and utils::from_string() to conveniently\n get an input source that can be used here.\n\nC++: genesis::sequence::PhylipReader::read(class std::shared_ptr<class genesis::utils::BaseInputSource>) const --> class genesis::sequence::SequenceSet", pybind11::arg("source"));
		cl.def("read", (void (genesis::sequence::PhylipReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>, class genesis::sequence::SequenceSet &) const) &genesis::sequence::PhylipReader::read, "Read all Sequence%s from an input source in Phylip format and return them as a\n SequenceSet.\n\n The Sequences are added to the SequenceSet, whose existing Sequences are kept. Thus, by\n repeatedly calling this or similar read functions, multiple input files can easily be read\n into one SequenceSet.\n\n Use functions such as utils::from_file() and utils::from_string() to conveniently\n get an input source that can be used here.\n\nC++: genesis::sequence::PhylipReader::read(class std::shared_ptr<class genesis::utils::BaseInputSource>, class genesis::sequence::SequenceSet &) const --> void", pybind11::arg("source"), pybind11::arg("target"));
		cl.def("parse_phylip_header", (struct genesis::sequence::PhylipReader::Header (genesis::sequence::PhylipReader::*)(class genesis::utils::InputStream &) const) &genesis::sequence::PhylipReader::parse_phylip_header, "Parse a Phylip header and return the contained sequence count and length.\n\n This helper function expects to find a Phylip header line in the form `x y`, which describes\n the number of sequences `x` in the Phylip data and their length `y`. The remainder of the\n header line is interpreted as Phylip options. See Header struct for more information.\n\n The function then advances the stream and skips potential empty lines after the header. It\n thus leaves the stream at the beginning of the first sequence line.\n\nC++: genesis::sequence::PhylipReader::parse_phylip_header(class genesis::utils::InputStream &) const --> struct genesis::sequence::PhylipReader::Header", pybind11::arg("it"));
		cl.def("parse_phylip_label", (std::string (genesis::sequence::PhylipReader::*)(class genesis::utils::InputStream &) const) &genesis::sequence::PhylipReader::parse_phylip_label, "Parse and return a Phylip label.\n\n This helper functions either takes the first `label_length` chars as a label or, if\n `label_length == 0` takes all chars until the first blank as label. It returns the trimmed\n label and leaves the stream at the next char after the label (and after subsequent blanks).\n\nC++: genesis::sequence::PhylipReader::parse_phylip_label(class genesis::utils::InputStream &) const --> std::string", pybind11::arg("it"));
		cl.def("parse_phylip_sequence_line", (std::string (genesis::sequence::PhylipReader::*)(class genesis::utils::InputStream &) const) &genesis::sequence::PhylipReader::parse_phylip_sequence_line, "Parse one sequence line.\n\n The line (which can also start after a label) is parsed until the first '\\n' char.\n While parsing, the options site_casing() and valid_chars() are applied according to their\n settings. The stream is left at the beginning of the next line.\n\nC++: genesis::sequence::PhylipReader::parse_phylip_sequence_line(class genesis::utils::InputStream &) const --> std::string", pybind11::arg("it"));
		cl.def("parse_phylip_sequential", (void (genesis::sequence::PhylipReader::*)(class genesis::utils::InputStream &, class genesis::sequence::SequenceSet &) const) &genesis::sequence::PhylipReader::parse_phylip_sequential, "Parse a whole Phylip file using the sequential variant (Mode::kSequential).\n\nC++: genesis::sequence::PhylipReader::parse_phylip_sequential(class genesis::utils::InputStream &, class genesis::sequence::SequenceSet &) const --> void", pybind11::arg("it"), pybind11::arg("sset"));
		cl.def("parse_phylip_interleaved", (void (genesis::sequence::PhylipReader::*)(class genesis::utils::InputStream &, class genesis::sequence::SequenceSet &) const) &genesis::sequence::PhylipReader::parse_phylip_interleaved, "Parse a whole Phylip file using the interleaved variant (Mode::kInterleaved).\n\nC++: genesis::sequence::PhylipReader::parse_phylip_interleaved(class genesis::utils::InputStream &, class genesis::sequence::SequenceSet &) const --> void", pybind11::arg("it"), pybind11::arg("sset"));
		cl.def("mode", (class genesis::sequence::PhylipReader & (genesis::sequence::PhylipReader::*)(enum genesis::sequence::PhylipReader::Mode)) &genesis::sequence::PhylipReader::mode, "Set the mode for reading sequences.\n\n Phylip offers two variants for storing the sequences: sequential and interleaved. As there\n is no option or flag needed to distinguish between them in the file itself, there is no\n chance of knowing the variant without trying to parse it. If one fails but not the other,\n it is proabably the latter variant. However, there are instances where both variants are\n valid at the same time, but yield different sequences. So, in general detecting the correct\n variant is undecidable, making Phylip a non-well-defined format.\n If possible, try to avoid Phylip files.\n\n In order to avoid those problems, this function explicitly sets the variant being used for\n parsing. By default, it is set to Mode::kSequential. Use Mode::kInterleaved for the other\n variant.\n\nC++: genesis::sequence::PhylipReader::mode(enum genesis::sequence::PhylipReader::Mode) --> class genesis::sequence::PhylipReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("mode", (enum genesis::sequence::PhylipReader::Mode (genesis::sequence::PhylipReader::*)() const) &genesis::sequence::PhylipReader::mode, "Return the currently set mode for parsing Phylip.\n\n See the setter mode( Mode ) for details.\n\nC++: genesis::sequence::PhylipReader::mode() const --> enum genesis::sequence::PhylipReader::Mode");
		cl.def("label_length", (class genesis::sequence::PhylipReader & (genesis::sequence::PhylipReader::*)(unsigned long)) &genesis::sequence::PhylipReader::label_length, "Set the length of the label in front of the sequences.\n\n Phylip has the weird property that labels are written in front of sequences and do not need\n to have a delimiter, but instead are simply the first `n` characters of the string. This\n value determines after how many chars the label ends and the actual sequence begins.\n\n If set to a value greater than 0, exaclty this many characters are read as label. Thus, they\n can also contain spaces. Spaces at the beginning or end of a label are stripped. The length\n that is dictated by the Phylip standard is 10, but any other length can also be used.\n\n If set to 0 (default), a relaxed version of Phylip is used instead, where the sequence begin\n is automatically detected. Labels can then be of arbitrary lengths, as long as they do not\n contain white spaces. However, in this case, there has to be at least one space or tab\n character between the label and the sequence. After the whitespace(s), the rest of the line\n is then treated as sequence data.\n\n The function returns the PhylipReader object to allow for fluent interfaces.\n\nC++: genesis::sequence::PhylipReader::label_length(unsigned long) --> class genesis::sequence::PhylipReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("label_length", (unsigned long (genesis::sequence::PhylipReader::*)() const) &genesis::sequence::PhylipReader::label_length, "Return the currently set label length.\n\n See the setter label_length( size_t ) for details.\n\nC++: genesis::sequence::PhylipReader::label_length() const --> unsigned long");
		cl.def("site_casing", (class genesis::sequence::PhylipReader & (genesis::sequence::PhylipReader::*)(enum genesis::sequence::PhylipReader::SiteCasing)) &genesis::sequence::PhylipReader::site_casing, "Set whether Sequence sites are automatically turned into upper or lower case.\n\n Default is SiteCasing::kToUpper, that is, all sites of the read Sequences are turned into\n upper case letters automatically.\n The function returns the PhylipReader object to allow for fluent interfaces.\n\nC++: genesis::sequence::PhylipReader::site_casing(enum genesis::sequence::PhylipReader::SiteCasing) --> class genesis::sequence::PhylipReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("site_casing", (enum genesis::sequence::PhylipReader::SiteCasing (genesis::sequence::PhylipReader::*)() const) &genesis::sequence::PhylipReader::site_casing, "Return whether Sequence sites are automatically turned into upper or lower case.\n\nC++: genesis::sequence::PhylipReader::site_casing() const --> enum genesis::sequence::PhylipReader::SiteCasing");
		cl.def("remove_digits", (class genesis::sequence::PhylipReader & (genesis::sequence::PhylipReader::*)(bool)) &genesis::sequence::PhylipReader::remove_digits, "Set whether digits in the Sequence should be kept (default) or removed.\n\n Usually, sequences do not contain digits. However, some Phylip variants allow to annotate\n sequences with positions in between, for example\n\n     2 10\n     foofoofoo AAGCC\n     5 TTGGC\n     barbarbar AAACC\n     5 CTTGC\n\n See http://evolution.genetics.washington.edu/phylip/doc/sequence.html for the definition\n of the Phylip standard that allows this. By default, we keep all symbols except white space,\n because some multi-state models might use digits as symbols. However, for files that use\n this weird variant of the standard, this option can be activated to remove the digits.\n\nC++: genesis::sequence::PhylipReader::remove_digits(bool) --> class genesis::sequence::PhylipReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("remove_digits", (bool (genesis::sequence::PhylipReader::*)() const) &genesis::sequence::PhylipReader::remove_digits, "Return whether digits are removed from the Sequence.\n\nC++: genesis::sequence::PhylipReader::remove_digits() const --> bool");
		cl.def("valid_chars", (class genesis::sequence::PhylipReader & (genesis::sequence::PhylipReader::*)(const std::string &)) &genesis::sequence::PhylipReader::valid_chars, "Set the chars that are used for validating Sequence sites when reading them.\n\n When this function is called with a string of chars, those chars are used to validate the\n sites when reading them. That is, only sequences consisting of the given chars are valid.\n\n If set to an empty string, this check is deactivated. This is also the default, meaning that\n no checking is done.\n\n In case that site_casing() is set to a value other than `SiteCasing::kUnchanged`:\n The validation is done after changing the casing, so that only lower or capital letters have\n to be provided for validation. In case that site_casing() is set to `SiteCasing::kUnchanged`:\n All chars that are to be considered valid have to be provided for validation.\n\n See `nucleic_acid_codes...()` and `amino_acid_codes...()` functions for presettings of chars\n that can be used for validation here.\n\nC++: genesis::sequence::PhylipReader::valid_chars(const std::string &) --> class genesis::sequence::PhylipReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("chars"));
		cl.def("valid_chars", (std::string (genesis::sequence::PhylipReader::*)() const) &genesis::sequence::PhylipReader::valid_chars, "Return the currently set chars used for validating Sequence sites.\n\n An empty string means that no validation is done.\n\nC++: genesis::sequence::PhylipReader::valid_chars() const --> std::string");
		cl.def("valid_char_lookup", (class genesis::utils::CharLookup<bool> & (genesis::sequence::PhylipReader::*)()) &genesis::sequence::PhylipReader::valid_char_lookup, "Return the internal CharLookup that is used for validating the Sequence sites.\n\n This function is provided in case direct access to the lookup is needed. Usually, the\n valid_chars() function should suffice. See there for details.\n\nC++: genesis::sequence::PhylipReader::valid_char_lookup() --> class genesis::utils::CharLookup<bool> &", pybind11::return_value_policy::reference_internal);

		{ // genesis::sequence::PhylipReader::Header file:genesis/sequence/formats/phylip_reader.hpp line:97
			auto & enclosing_class = cl;
			pybind11::class_<genesis::sequence::PhylipReader::Header, std::shared_ptr<genesis::sequence::PhylipReader::Header>> cl(enclosing_class, "Header", "Helper that stores the header information of a Phylip file.");
			cl.def( pybind11::init( [](){ return new genesis::sequence::PhylipReader::Header(); } ) );
			cl.def( pybind11::init( [](genesis::sequence::PhylipReader::Header const &o){ return new genesis::sequence::PhylipReader::Header(o); } ) );
			cl.def_readwrite("num_sequences", &genesis::sequence::PhylipReader::Header::num_sequences);
			cl.def_readwrite("len_sequences", &genesis::sequence::PhylipReader::Header::len_sequences);
			cl.def_readwrite("options", &genesis::sequence::PhylipReader::Header::options);
			cl.def("assign", (struct genesis::sequence::PhylipReader::Header & (genesis::sequence::PhylipReader::Header::*)(const struct genesis::sequence::PhylipReader::Header &)) &genesis::sequence::PhylipReader::Header::operator=, "C++: genesis::sequence::PhylipReader::Header::operator=(const struct genesis::sequence::PhylipReader::Header &) --> struct genesis::sequence::PhylipReader::Header &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		}

	}
	// genesis::sequence::consensus_sequence_with_majorities(const class genesis::sequence::SiteCounts &, bool, char) file:genesis/sequence/functions/consensus.hpp line:84
	M("genesis::sequence").def("consensus_sequence_with_majorities", [](const class genesis::sequence::SiteCounts & a0) -> std::string { return genesis::sequence::consensus_sequence_with_majorities(a0); }, "", pybind11::arg("counts"));
	M("genesis::sequence").def("consensus_sequence_with_majorities", [](const class genesis::sequence::SiteCounts & a0, bool const & a1) -> std::string { return genesis::sequence::consensus_sequence_with_majorities(a0, a1); }, "", pybind11::arg("counts"), pybind11::arg("allow_gaps"));
	M("genesis::sequence").def("consensus_sequence_with_majorities", (std::string (*)(const class genesis::sequence::SiteCounts &, bool, char)) &genesis::sequence::consensus_sequence_with_majorities, "Calculate the majority rule consensus sequence by using the most frequent character at\n each site.\n\n The function creates a consensus sequence by using the character at each position that has the\n highest count (or frequency). It does not assume any character codes. Thus, it works for all\n kinds of sequence codes, e.g., nucleic acid or amino acid codes.\n\n The optional parameter `allow_gaps` (default is `true`) determines whether gaps in the consensus\n sequence are allowed. By default, if a site consists mostly of gaps, the consensus sequence also\n contains a gap at that site. If however this option is set to `false`, the consensus sequence\n will contain the most frequent non-gap character, even if there are more gaps at this site than\n the character itself. In other words, if the parameter is set to `false`, gaps are treated as\n missing characters instead of another type of character for computing the consensus.\n The only exception are gaps-only sites; in this case, the resulting sites contain a gap\n characters even if the parameter is set to `false`.\n\n The optional parameter `gap_char` (default value '-') is used for sites where no counts are\n available (i.e., are all zero), or, if `allow_gaps` is set to `true`, for sites that contain\n mostly gaps.\n\n Furthermore, if two or more characters have the same frequency, the first one is used. That is,\n the one that appears first in SiteCounts::characters().\n\n For an alternative version of this function that takes those ambiguities into account, see\n consensus_sequence_with_ambiguities(). Also, for a version of this function that takes a\n threshold for the character frequencies into account, see consensus_sequence_with_threshold().\n However, both of them currently only work for nucleic acid codes (`ACGT`).\n\nC++: genesis::sequence::consensus_sequence_with_majorities(const class genesis::sequence::SiteCounts &, bool, char) --> std::string", pybind11::arg("counts"), pybind11::arg("allow_gaps"), pybind11::arg("gap_char"));

}
