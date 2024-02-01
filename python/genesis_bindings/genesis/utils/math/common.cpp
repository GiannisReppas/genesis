#include <functional>
#include <genesis/utils/formats/csv/reader.hpp>
#include <genesis/utils/io/base_input_source.hpp>
#include <genesis/utils/io/input_stream.hpp>
#include <genesis/utils/math/common.hpp>
#include <genesis/utils/tools/hash/functions.hpp>
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
#include <../python/custom_bindings/extensions/taxonomy/functions_taxonomy.hpp>
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

void bind_genesis_utils_math_common(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// genesis::utils::for_each_finite_pair(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class std::function<void (double, double)>) file:genesis/utils/math/common.hpp line:286
	M("genesis::utils").def("for_each_finite_pair", (void (*)(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class std::function<void (double, double)>)) &genesis::utils::for_each_finite_pair<__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >,__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >>, "C++: genesis::utils::for_each_finite_pair(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class std::function<void (double, double)>) --> void", pybind11::arg("first_a"), pybind11::arg("last_a"), pybind11::arg("first_b"), pybind11::arg("last_b"), pybind11::arg("execute"));

	// genesis::utils::HashingFunctions file:genesis/utils/tools/hash/functions.hpp line:53
	pybind11::enum_<genesis::utils::HashingFunctions>(M("genesis::utils"), "HashingFunctions", "List of the currently implemented hashing functions.\n\n This is useful in order to select the used hashing function at runtime for some algorithms.\n\n \n hash_hex()")
		.value("kMD5", genesis::utils::HashingFunctions::kMD5)
		.value("kSHA1", genesis::utils::HashingFunctions::kSHA1)
		.value("kSHA256", genesis::utils::HashingFunctions::kSHA256);

;

	// genesis::utils::hash_hex(class std::shared_ptr<class genesis::utils::BaseInputSource>, enum genesis::utils::HashingFunctions) file:genesis/utils/tools/hash/functions.hpp line:81
	M("genesis::utils").def("hash_hex", (std::string (*)(class std::shared_ptr<class genesis::utils::BaseInputSource>, enum genesis::utils::HashingFunctions)) &genesis::utils::hash_hex, "Calculate the hash of an input source, using a given hashing function, and return its hex\n representation as a string.\n\n See ::HashingFunctions for the list of available hashing functions.\n\nC++: genesis::utils::hash_hex(class std::shared_ptr<class genesis::utils::BaseInputSource>, enum genesis::utils::HashingFunctions) --> std::string", pybind11::arg("source"), pybind11::arg("hash_fct"));

	{ // genesis::utils::CsvReader file:genesis/utils/formats/csv/reader.hpp line:70
		pybind11::class_<genesis::utils::CsvReader, std::shared_ptr<genesis::utils::CsvReader>> cl(M("genesis::utils"), "CsvReader", "Read Comma/Character Separated Values (CSV) data and other delimiter-separated formats.\n\n This class provides simple facilities for reading data in a format that uses delimiter chars\n to separate tabulated data into fields, where one line represents one row of the table.\n\n The read() function returns the table as a vector, with one entry per line (i.e., row). Each such\n entry is itself a vector of strings, representing the fields (values of the columns) of that row.\n\n There are several properties that can be changed in order to customize the behaviour. By default,\n the reader uses the comma char to separate fields and uses double quotation marks. See the\n property functions for more information.\n\n If the data is too big to be read at once into memory, or if you want to parse the data line by\n line, you can also use the parser functions parse_line() and parse_field() directly.");
		cl.def( pybind11::init( [](){ return new genesis::utils::CsvReader(); } ) );
		cl.def( pybind11::init( [](genesis::utils::CsvReader const &o){ return new genesis::utils::CsvReader(o); } ) );
		cl.def("assign", (class genesis::utils::CsvReader & (genesis::utils::CsvReader::*)(const class genesis::utils::CsvReader &)) &genesis::utils::CsvReader::operator=, "C++: genesis::utils::CsvReader::operator=(const class genesis::utils::CsvReader &) --> class genesis::utils::CsvReader &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("read", (class std::vector<class std::vector<std::string, class std::allocator<std::string > >, class std::allocator<class std::vector<std::string, class std::allocator<std::string > > > > (genesis::utils::CsvReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>) const) &genesis::utils::CsvReader::read, "Read CSV data from a source and return it as a table, using a vector per line,\n containing a vector of fields found on that line.\n\n Use functions such as utils::from_file() and utils::from_string() to conveniently\n get an input source that can be used here.\n\nC++: genesis::utils::CsvReader::read(class std::shared_ptr<class genesis::utils::BaseInputSource>) const --> class std::vector<class std::vector<std::string, class std::allocator<std::string > >, class std::allocator<class std::vector<std::string, class std::allocator<std::string > > > >", pybind11::arg("source"));
		cl.def("parse_document", (class std::vector<class std::vector<std::string, class std::allocator<std::string > >, class std::allocator<class std::vector<std::string, class std::allocator<std::string > > > > (genesis::utils::CsvReader::*)(class genesis::utils::InputStream &) const) &genesis::utils::CsvReader::parse_document, "Parse a whole CSV document and return its contents.\n\nC++: genesis::utils::CsvReader::parse_document(class genesis::utils::InputStream &) const --> class std::vector<class std::vector<std::string, class std::allocator<std::string > >, class std::allocator<class std::vector<std::string, class std::allocator<std::string > > > >", pybind11::arg("input_stream"));
		cl.def("parse_field", (std::string (genesis::utils::CsvReader::*)(class genesis::utils::InputStream &) const) &genesis::utils::CsvReader::parse_field, "Parse one field (i.e., one cell) of the CSV data and return it.\n\n This function reads from a given input stream until the column separator or the end of the line\n or the end of the stream is found. It furthermore trims the necessary chars from the beginning\n and end of the field, and handles quoted strings according to the settings of the CsvReader.\n\n The stream is left at either the separator char, the new line char, or the end of the file,\n depending on which occurs first.\n\n See\n \n\n\n\n\n\n\n\n\nC++: genesis::utils::CsvReader::parse_field(class genesis::utils::InputStream &) const --> std::string", pybind11::arg("input_stream"));
		cl.def("parse_line", (class std::vector<std::string, class std::allocator<std::string > > (genesis::utils::CsvReader::*)(class genesis::utils::InputStream &) const) &genesis::utils::CsvReader::parse_line, "Parse one line of the CSV data and return it.\n\n This function parses a whole line using parse_field() until the new line char (or the end of the\n stream) is found. The fields are returned in a vector. The stream is left at either the next char\n after the new line char or the end of the file, if there is no new line.\n\n See \n\n\n\nC++: genesis::utils::CsvReader::parse_line(class genesis::utils::InputStream &) const --> class std::vector<std::string, class std::allocator<std::string > >", pybind11::arg("input_stream"));
		cl.def("comment_chars", (class genesis::utils::CsvReader & (genesis::utils::CsvReader::*)(const std::string &)) &genesis::utils::CsvReader::comment_chars, "Set chars that are used to mark comment lines.\n\n By default, no chars are used, that is, no line is interpreted as comment. Use this function\n to change that behaviour, e.g., use `#` as marker for comment lines.\n All lines starting with any of the set chars are then skipped while reading. The char has to\n be the first on the line, that is, no leading blanks are allowed.\n\n The function returns a reference to the CsvReader object in order to allow a fluent interface.\n\nC++: genesis::utils::CsvReader::comment_chars(const std::string &) --> class genesis::utils::CsvReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("chars"));
		cl.def("comment_chars", (const std::string & (genesis::utils::CsvReader::*)() const) &genesis::utils::CsvReader::comment_chars, "Return the currently set chars that are used to mark comment lines.\n\n See the \n\n\n\nC++: genesis::utils::CsvReader::comment_chars() const --> const std::string &", pybind11::return_value_policy::reference_internal);
		cl.def("trim_chars", (class genesis::utils::CsvReader & (genesis::utils::CsvReader::*)(const std::string &)) &genesis::utils::CsvReader::trim_chars, "Set chars that are trimmed from the start and end of each field.\n\n By default, no chars are trimmed. Use this function to change that behaviour, e.g., to trim\n spaces and tabs. Be aware that according to some CSV definitions, blanks are considered\n to be part of the field and should not be trimmed.\n\n The function returns a reference to the CsvReader object in order to allow a fluent interface.\n\nC++: genesis::utils::CsvReader::trim_chars(const std::string &) --> class genesis::utils::CsvReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("chars"));
		cl.def("trim_chars", (const std::string & (genesis::utils::CsvReader::*)() const) &genesis::utils::CsvReader::trim_chars, "Return the currently set chars that are trimmed from the start and end of each field.\n\n See the \n\n\n\nC++: genesis::utils::CsvReader::trim_chars() const --> const std::string &", pybind11::return_value_policy::reference_internal);
		cl.def("quotation_chars", (class genesis::utils::CsvReader & (genesis::utils::CsvReader::*)(const std::string &)) &genesis::utils::CsvReader::quotation_chars, "Set the chars that are used for quoting strings in fields.\n\n By default, the double quotation mark char \" is used as quotation mark. Any other set of chars\n can be used instead, for example a combination of single and double quotation marks by providing\n `'\"` to this function.\n\n Within a quoted part, any char can appear, even new lines. However, in order to use the quotation\n mark itself, it has to be escaped.\n See \n\n\n\n\n\n\n\nC++: genesis::utils::CsvReader::quotation_chars(const std::string &) --> class genesis::utils::CsvReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("chars"));
		cl.def("quotation_chars", (const std::string & (genesis::utils::CsvReader::*)() const) &genesis::utils::CsvReader::quotation_chars, "Return the currently set chars for quoting strings in fields.\n\n See the \n\n\n\nC++: genesis::utils::CsvReader::quotation_chars() const --> const std::string &", pybind11::return_value_policy::reference_internal);
		cl.def("separator_chars", (class genesis::utils::CsvReader & (genesis::utils::CsvReader::*)(const std::string &)) &genesis::utils::CsvReader::separator_chars, "Set the chars used to separate fields of the CSV data.\n\n By default, the comma char `,` is used. Any other set of chars can be used instead, for example\n a combination of tabs and bars by providing `|` to this function.\n\n Caveat: If more than one char is used as separater, any of them separates fields. That is,\n the string provided to this function is not taken as a whole to separate fields, but its single\n chars are used.\n\n See \n\n\n\n\n\nC++: genesis::utils::CsvReader::separator_chars(const std::string &) --> class genesis::utils::CsvReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("chars"));
		cl.def("separator_chars", (const std::string & (genesis::utils::CsvReader::*)() const) &genesis::utils::CsvReader::separator_chars, "Return the currently set chars used to separate fields of the CSV data.\n\n See the \n\n\n\nC++: genesis::utils::CsvReader::separator_chars() const --> const std::string &", pybind11::return_value_policy::reference_internal);
		cl.def("skip_empty_lines", (class genesis::utils::CsvReader & (genesis::utils::CsvReader::*)(bool)) &genesis::utils::CsvReader::skip_empty_lines, "Set whether to skip empty lines.\n\n Default is `false`. If set to `true`, all lines that are empty (that is, no content, or just\n consisting of spaces and tabs) are skipped while reading.\n\n The function returns a reference to the CsvReader object in order to allow a fluent interface.\n\nC++: genesis::utils::CsvReader::skip_empty_lines(bool) --> class genesis::utils::CsvReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("skip_empty_lines", (bool (genesis::utils::CsvReader::*)() const) &genesis::utils::CsvReader::skip_empty_lines, "Return whether currently empty lines are skipped.\n\n See the \n\n\nC++: genesis::utils::CsvReader::skip_empty_lines() const --> bool");
		cl.def("merge_separators", (class genesis::utils::CsvReader & (genesis::utils::CsvReader::*)(bool)) &genesis::utils::CsvReader::merge_separators, "Set whether consecutive separater chars are merged or whether each of them creates a\n new field.\n\n Default is `false`. Usually, CSV data has the same number of columns for the whole dataset.\n Thus, empty fields will result in consecutive separator chars. When this value is set to `false`,\n those fields are correctly parsed into empty fields.\n\n It might however be useful to not create separate empty fields when consecutive separator chars\n are encountered. This is particularly the case if spaces or tabs are used as separators.\n In this case it makes sense to have more than one of them consecutively in order to align\n the columns of the data. For such datasets, this value can be set to `true`.\n\n To put it in other words, this value determines whether empty strings resulting from adjacent\n separator chars are excluded from the output.\n\n The function returns a reference to the CsvReader object in order to allow a fluent interface.\n\nC++: genesis::utils::CsvReader::merge_separators(bool) --> class genesis::utils::CsvReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("merge_separators", (bool (genesis::utils::CsvReader::*)() const) &genesis::utils::CsvReader::merge_separators, "Return the current setting whether consecutive separators are merged or not.\n\n See the \n\n\nC++: genesis::utils::CsvReader::merge_separators() const --> bool");
		cl.def("use_escapes", (class genesis::utils::CsvReader & (genesis::utils::CsvReader::*)(bool)) &genesis::utils::CsvReader::use_escapes, "Set whether to use backslash escape sequences.\n\n Default is `false`. If set to `true`, character sequences of `` (backslash and some other char)\n are turned into the respective string form, according to the rules of deescape().\n Also, see parse_quoted_string() for more information on escaping.\n\n This works inside and outside of quoted strings. In order to create new lines within a field,\n either the sequence `` (backslash n) can be used, or a backslash at the end of the line.\n\n The function returns a reference to the CsvReader object in order to allow a fluent interface.\n\nC++: genesis::utils::CsvReader::use_escapes(bool) --> class genesis::utils::CsvReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("use_escapes", (bool (genesis::utils::CsvReader::*)() const) &genesis::utils::CsvReader::use_escapes, "Return whether backslash escape sequences are used.\n\n See the \n\n\nC++: genesis::utils::CsvReader::use_escapes() const --> bool");
		cl.def("use_twin_quotes", (class genesis::utils::CsvReader & (genesis::utils::CsvReader::*)(bool)) &genesis::utils::CsvReader::use_twin_quotes, "Set whether to interpret two consequtive quotation marks as a single (\"escaped\") one.\n\n Default is `true`. Use this setting in order to be able to escape quotation marks by doubling\n them. This is a common variant in CSV data. It means, whenever two consecutive quotation marks\n are encountered, they are turned into one (thus, the first one \"escapes\" the second). This\n works both inside and outside of regularly quoted parts. That is, the following two fields\n are interpreted the same:\n\n     \"My \"\"old\"\" friend\"\n     My \"\"old\"\" friend\n\n This also works in addition to normal backslash escape sequences, see\n \n\n\n\n\n\n\n\n\nC++: genesis::utils::CsvReader::use_twin_quotes(bool) --> class genesis::utils::CsvReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("use_twin_quotes", (bool (genesis::utils::CsvReader::*)() const) &genesis::utils::CsvReader::use_twin_quotes, "Return whether to interpret two consequtive quotation marks as a single (\"escaped\") one.\n\n See the \n\n\nC++: genesis::utils::CsvReader::use_twin_quotes() const --> bool");
	}
}