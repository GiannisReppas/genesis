#include <functional>
#include <genesis/taxonomy/formats/taxonomy_reader.hpp>
#include <genesis/taxonomy/formats/taxopath_parser.hpp>
#include <genesis/taxonomy/taxon.hpp>
#include <genesis/taxonomy/taxon_data.hpp>
#include <genesis/taxonomy/taxonomy.hpp>
#include <genesis/taxonomy/taxopath.hpp>
#include <genesis/utils/formats/csv/reader.hpp>
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

void bind_genesis_taxonomy_formats_taxopath_parser(std::function< pybind11::module &(std::string const &namespace_) > &M)
{

	extend_iterator(M("genesis::taxonomy"));
	{ // genesis::taxonomy::TaxopathParser file:genesis/taxonomy/formats/taxopath_parser.hpp line:81
		pybind11::class_<genesis::taxonomy::TaxopathParser, std::shared_ptr<genesis::taxonomy::TaxopathParser>> cl(M("genesis::taxonomy"), "TaxopathParser", "Helper class to parse a string containing a taxonomic path string into a Taxopath object.\n\n This class bundles the parameters used for parsing a taxonomic path strings and offers functions\n for the actual parsing. This is needed in order to allow customization of the parsing process,\n for example in TaxonomyReader. Furthermore, this prevents code duplication in places where the\n input is a taxonomic path string.\n The result of the parsing process is a Taxopath object. See there for details.\n\n The elements are expected to be char separated, using the value of\n \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		cl.def( pybind11::init( [](){ return new genesis::taxonomy::TaxopathParser(); } ) );
		cl.def( pybind11::init( [](genesis::taxonomy::TaxopathParser const &o){ return new genesis::taxonomy::TaxopathParser(o); } ) );
		cl.def("assign", (class genesis::taxonomy::TaxopathParser & (genesis::taxonomy::TaxopathParser::*)(const class genesis::taxonomy::TaxopathParser &)) &genesis::taxonomy::TaxopathParser::operator=, "C++: genesis::taxonomy::TaxopathParser::operator=(const class genesis::taxonomy::TaxopathParser &) --> class genesis::taxonomy::TaxopathParser &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("parse", (class genesis::taxonomy::Taxopath (genesis::taxonomy::TaxopathParser::*)(const std::string &) const) &genesis::taxonomy::TaxopathParser::parse, "Parse a taxonomic path string into a Taxopath object and return it.\n\n See \n\n\nC++: genesis::taxonomy::TaxopathParser::parse(const std::string &) const --> class genesis::taxonomy::Taxopath", pybind11::arg("taxopath"));
		cl.def("parse", (class genesis::taxonomy::Taxopath (genesis::taxonomy::TaxopathParser::*)(const class genesis::taxonomy::Taxon &) const) &genesis::taxonomy::TaxopathParser::parse, "Helper function to turn a Taxon into a Taxopath.\n\n This function is probably not need often, as the Taxopath is a helper object from\n a taxonomic path string towards a Taxon object, but not the other way round.\n In order to get the string from a Taxon, see the TaxopathGenerator class instead.\n\n However, this function might still be useful in some cases. You never know.\n\nC++: genesis::taxonomy::TaxopathParser::parse(const class genesis::taxonomy::Taxon &) const --> class genesis::taxonomy::Taxopath", pybind11::arg("taxon"));
		cl.def("delimiters", (class genesis::taxonomy::TaxopathParser & (genesis::taxonomy::TaxopathParser::*)(const std::string &)) &genesis::taxonomy::TaxopathParser::delimiters, "Set the chars used to split the taxonomic path string.\n\n Those chars are used to split the taxon name into its hierarchical parts.\n Default is ';', as this is the usual value in many databases. See Taxopath for details.\n\n If this value is set to multiple chars (string longer than 1), any of them is used for splitting.\n\n Example: The taxonomic path string\n\n     Archaea;Euryarchaeota;Halobacteria;\n\n is split into \"Archaea\", \"Euryarchaeota\" and \"Halobacteria\".\n\nC++: genesis::taxonomy::TaxopathParser::delimiters(const std::string &) --> class genesis::taxonomy::TaxopathParser &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("delimiters", (std::string (genesis::taxonomy::TaxopathParser::*)() const) &genesis::taxonomy::TaxopathParser::delimiters, "Return the currelty set delimiter chars used to split the taxonomic path string.\n\n See \n\n\nC++: genesis::taxonomy::TaxopathParser::delimiters() const --> std::string");
		cl.def("trim_whitespaces", (class genesis::taxonomy::TaxopathParser & (genesis::taxonomy::TaxopathParser::*)(bool)) &genesis::taxonomy::TaxopathParser::trim_whitespaces, "Set whether to trim whitespaces around the taxonomic elements after splitting them.\n\n Default is `true`. If set to true, the taxa given are trimmed off white spaces after splitting\n them. This is helpful if the input string is copied from some spreadsheet application or\n CSV file, where spaces between cells might be added.\n\n If set to `false`, all elements are left as they are.\n\n Example: The line\n\n     Archaea; Aigarchaeota; Aigarchaeota Incertae Sedis;	11091	class	123\n\n contains spaces both between the taxa names (separated by `;`), as well as within the names.\n Only the former ones will be trimmed, while latter ones are left as they are.\n\nC++: genesis::taxonomy::TaxopathParser::trim_whitespaces(bool) --> class genesis::taxonomy::TaxopathParser &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("trim_whitespaces", (bool (genesis::taxonomy::TaxopathParser::*)() const) &genesis::taxonomy::TaxopathParser::trim_whitespaces, "Return the currently set value whether whitespaces are trimmed off the taxonomic elements.\n\n See \n\n\nC++: genesis::taxonomy::TaxopathParser::trim_whitespaces() const --> bool");
		cl.def("remove_trailing_delimiter", (class genesis::taxonomy::TaxopathParser & (genesis::taxonomy::TaxopathParser::*)(bool)) &genesis::taxonomy::TaxopathParser::remove_trailing_delimiter, "Set whether to remove an empty taxonomic element at the end, if it occurs.\n\n In many taxonomic databases, the taxonomic string representation end with a ';' by default.\n When splitting such a string, this results in an empty last element. If this option is set to\n `true` (default), this element is removed from the Taxopath.\n\n If set to `false`, the element is not removed, but instead treated as a normal \"empty\" element,\n which means, it is replaced by the value of the preceeding element. See\n \n\n\n\nC++: genesis::taxonomy::TaxopathParser::remove_trailing_delimiter(bool) --> class genesis::taxonomy::TaxopathParser &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("remove_trailing_delimiter", (bool (genesis::taxonomy::TaxopathParser::*)() const) &genesis::taxonomy::TaxopathParser::remove_trailing_delimiter, "Return whether currently trailing delimiters are removed from the taxonomic path\n string.\n\n See \n\n\nC++: genesis::taxonomy::TaxopathParser::remove_trailing_delimiter() const --> bool");
	}
	{ // genesis::taxonomy::TaxonomyReader file:genesis/taxonomy/formats/taxonomy_reader.hpp line:108
		pybind11::class_<genesis::taxonomy::TaxonomyReader, std::shared_ptr<genesis::taxonomy::TaxonomyReader>> cl(M("genesis::taxonomy"), "TaxonomyReader", "Read Taxonomy file formats.\n\n This reader populates a Taxonomy.\n\n Exemplary usage:\n\n     std::string infile = \"path/to/taxonomy.txt\";\n     Taxonomy tax;\n\n     TaxonomyReader()\n         .rank_field_position( 2 )\n         .expect_strict_order( true )\n         .read( utils::from_file( infile ), tax );\n\n It expects one taxon per input line. This line can also contain other information, for example\n\n     Archaea;Crenarchaeota;Thermoprotei;Desulfurococcales;	14	order	119\n\n In order to separate the fields of the input, a \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		cl.def( pybind11::init( [](){ return new genesis::taxonomy::TaxonomyReader(); } ) );
		cl.def( pybind11::init( [](genesis::taxonomy::TaxonomyReader const &o){ return new genesis::taxonomy::TaxonomyReader(o); } ) );
		cl.def("assign", (class genesis::taxonomy::TaxonomyReader & (genesis::taxonomy::TaxonomyReader::*)(const class genesis::taxonomy::TaxonomyReader &)) &genesis::taxonomy::TaxonomyReader::operator=, "C++: genesis::taxonomy::TaxonomyReader::operator=(const class genesis::taxonomy::TaxonomyReader &) --> class genesis::taxonomy::TaxonomyReader &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("read", (void (genesis::taxonomy::TaxonomyReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>, class genesis::taxonomy::Taxonomy &) const) &genesis::taxonomy::TaxonomyReader::read, "Read taxonomy data from an input source, and add the contents to a Taxonomy.\n\n Use functions such as utils::from_file() and utils::from_string() to conveniently\n get an input source that can be used here.\n\nC++: genesis::taxonomy::TaxonomyReader::read(class std::shared_ptr<class genesis::utils::BaseInputSource>, class genesis::taxonomy::Taxonomy &) const --> void", pybind11::arg("source"), pybind11::arg("target"));
		cl.def("read", (class genesis::taxonomy::Taxonomy (genesis::taxonomy::TaxonomyReader::*)(class std::shared_ptr<class genesis::utils::BaseInputSource>) const) &genesis::taxonomy::TaxonomyReader::read, "Read a taxonomy from an input source and return the Taxonomy.\n\n Use functions such as utils::from_file() and utils::from_string() to conveniently\n get an input source that can be used here.\n\nC++: genesis::taxonomy::TaxonomyReader::read(class std::shared_ptr<class genesis::utils::BaseInputSource>) const --> class genesis::taxonomy::Taxonomy", pybind11::arg("source"));
		cl.def("parse_document", (void (genesis::taxonomy::TaxonomyReader::*)(class genesis::utils::InputStream &, class genesis::taxonomy::Taxonomy &) const) &genesis::taxonomy::TaxonomyReader::parse_document, "Parse all data from an InputStream into a Taxonomy object.\n\nC++: genesis::taxonomy::TaxonomyReader::parse_document(class genesis::utils::InputStream &, class genesis::taxonomy::Taxonomy &) const --> void", pybind11::arg("it"), pybind11::arg("tax"));
		cl.def("parse_line", (struct genesis::taxonomy::TaxonomyReader::Line (genesis::taxonomy::TaxonomyReader::*)(class genesis::utils::InputStream &) const) &genesis::taxonomy::TaxonomyReader::parse_line, "Read a single line of a taxonomy file and return the contained name and rank.\n\n The name is expected to be a taxonomic path string. See Taxopath for details on that format.\n\nC++: genesis::taxonomy::TaxonomyReader::parse_line(class genesis::utils::InputStream &) const --> struct genesis::taxonomy::TaxonomyReader::Line", pybind11::arg("it"));
		cl.def("csv_reader", (class genesis::utils::CsvReader & (genesis::taxonomy::TaxonomyReader::*)()) &genesis::taxonomy::TaxonomyReader::csv_reader, "Get the \n\n\n\n\n\n\n\n\n\n\n\nC++: genesis::taxonomy::TaxonomyReader::csv_reader() --> class genesis::utils::CsvReader &", pybind11::return_value_policy::reference_internal);
		cl.def("taxopath_parser", (class genesis::taxonomy::TaxopathParser & (genesis::taxonomy::TaxonomyReader::*)()) &genesis::taxonomy::TaxonomyReader::taxopath_parser, "Get the TaxopathParser used for parsing taxonomic path strings.\n\n The name field is expected to be a taxonomic path string. It is turned into a Taxon\n using the settings of the TaxopathParser. See there for details. See Taxopath for\n a path of the expected string format.\n\nC++: genesis::taxonomy::TaxonomyReader::taxopath_parser() --> class genesis::taxonomy::TaxopathParser &", pybind11::return_value_policy::reference_internal);
		cl.def("name_field_position", (class genesis::taxonomy::TaxonomyReader & (genesis::taxonomy::TaxonomyReader::*)(int)) &genesis::taxonomy::TaxonomyReader::name_field_position, "Set the position of the field in each line where the taxon name (Taxopath) is located.\n\n This value determines at with position (zero based) the field for the taxon name is located.\n\n For example, in a taxonomy file with entries like\n\n     Archaea;Crenarchaeota;Thermoprotei;	7	class	119\n\n this value would have to be set to `0`, as this is where the taxon name is found. This reader\n expects the taxon name to be a Taxopath. This is what we call a string of taxonomic hierarchy\n elements, usually separated by semicola. See Taxopath for details.\n\n By default, this value is set to `0`, that is, the first field. As it does not make sense to\n skip this value, it cannot be set to values below zero - which is different from\n \n\n\n\n\nC++: genesis::taxonomy::TaxonomyReader::name_field_position(int) --> class genesis::taxonomy::TaxonomyReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("name_field_position", (int (genesis::taxonomy::TaxonomyReader::*)() const) &genesis::taxonomy::TaxonomyReader::name_field_position, "Get the currently set position of the field in each line where the taxon name is located.\n\n See \n\n\nC++: genesis::taxonomy::TaxonomyReader::name_field_position() const --> int");
		cl.def("rank_field_position", (class genesis::taxonomy::TaxonomyReader & (genesis::taxonomy::TaxonomyReader::*)(int)) &genesis::taxonomy::TaxonomyReader::rank_field_position, "Set the position of the field in each line where the rank name is located.\n\n This value determines at with position (zero based) the field for the rank name is located.\n\n For example, in a taxonomy file with entries like\n\n     Archaea;Crenarchaeota;Thermoprotei;	7	class	119\n\n this value would have to be set to `2`, as this is where the rank name \"class\" is found.\n\n If the file does not contain any rank names, or if this field should be skipped, set it to\n a value of `-1`. This is also the default.\n\nC++: genesis::taxonomy::TaxonomyReader::rank_field_position(int) --> class genesis::taxonomy::TaxonomyReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("rank_field_position", (int (genesis::taxonomy::TaxonomyReader::*)() const) &genesis::taxonomy::TaxonomyReader::rank_field_position, "Get the currently set position of the field in each line where the rank name is located.\n\n See \n\n\nC++: genesis::taxonomy::TaxonomyReader::rank_field_position() const --> int");
		cl.def("id_field_position", (class genesis::taxonomy::TaxonomyReader & (genesis::taxonomy::TaxonomyReader::*)(int)) &genesis::taxonomy::TaxonomyReader::id_field_position, "Set the position of the field in each line where the ID is located.\n\n This value determines at with position (zero based) the field for the ID is located.\n\n For example, in a taxonomy file with entries like\n\n     Archaea;Crenarchaeota;Thermoprotei;	7	class	119\n\n this value could have to be set to `1`, as this is where the ID \"7\" is found.\n\n If the file does not contain any IDs, or if this field should be skipped, set it to\n a value of `-1`. This is also the default.\n\nC++: genesis::taxonomy::TaxonomyReader::id_field_position(int) --> class genesis::taxonomy::TaxonomyReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("id_field_position", (int (genesis::taxonomy::TaxonomyReader::*)() const) &genesis::taxonomy::TaxonomyReader::id_field_position, "Get the currently set position of the field in each line where the ID is located.\n\n See \n\n\nC++: genesis::taxonomy::TaxonomyReader::id_field_position() const --> int");
		cl.def("expect_strict_order", (class genesis::taxonomy::TaxonomyReader & (genesis::taxonomy::TaxonomyReader::*)(bool)) &genesis::taxonomy::TaxonomyReader::expect_strict_order, "Set whether the reader expects a strict order of taxa.\n\n In a strictly ordered taxonomy file, the super-groups have to be listed before any sub-groups.\n\n For example, the list\n\n     Archaea;\n     Archaea;Aenigmarchaeota;\n     Archaea;Crenarchaeota;\n     Archaea;Crenarchaeota;Thermoprotei;\n\n is in strict order.\n\n If this property is set to `true`, the reader expects this ordering and throws an exception\n if there is a violation, that is, if there is a sub-group in the list without a previous\n entry of its super-group (recursively). This is useful to check a file for consistency, e.g.,\n it might happen that some super-group is misspelled by accident.\n\n If set to `false` (default), the order is ignored and all super-groups are created if necessary.\n\nC++: genesis::taxonomy::TaxonomyReader::expect_strict_order(bool) --> class genesis::taxonomy::TaxonomyReader &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("expect_strict_order", (bool (genesis::taxonomy::TaxonomyReader::*)() const) &genesis::taxonomy::TaxonomyReader::expect_strict_order, "Return whether currently the reader expects a strict order of taxa.\n\n See \n\n\nC++: genesis::taxonomy::TaxonomyReader::expect_strict_order() const --> bool");

		{ // genesis::taxonomy::TaxonomyReader::Line file:genesis/taxonomy/formats/taxonomy_reader.hpp line:119
			auto & enclosing_class = cl;
			pybind11::class_<genesis::taxonomy::TaxonomyReader::Line, std::shared_ptr<genesis::taxonomy::TaxonomyReader::Line>> cl(enclosing_class, "Line", "Internal helper structure that stores the relevant data of one line while reading.");
			cl.def( pybind11::init( [](){ return new genesis::taxonomy::TaxonomyReader::Line(); } ) );
			cl.def( pybind11::init( [](genesis::taxonomy::TaxonomyReader::Line const &o){ return new genesis::taxonomy::TaxonomyReader::Line(o); } ) );
			cl.def_readwrite("name", &genesis::taxonomy::TaxonomyReader::Line::name);
			cl.def_readwrite("rank", &genesis::taxonomy::TaxonomyReader::Line::rank);
			cl.def_readwrite("id", &genesis::taxonomy::TaxonomyReader::Line::id);
			cl.def("assign", (struct genesis::taxonomy::TaxonomyReader::Line & (genesis::taxonomy::TaxonomyReader::Line::*)(const struct genesis::taxonomy::TaxonomyReader::Line &)) &genesis::taxonomy::TaxonomyReader::Line::operator=, "C++: genesis::taxonomy::TaxonomyReader::Line::operator=(const struct genesis::taxonomy::TaxonomyReader::Line &) --> struct genesis::taxonomy::TaxonomyReader::Line &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		}

	}
}
