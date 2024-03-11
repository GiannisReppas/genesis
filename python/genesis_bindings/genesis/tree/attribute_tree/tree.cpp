#include <genesis/placement/placement_tree.hpp>
#include <genesis/tree/attribute_tree/indexed_newick_reader.hpp>
#include <genesis/tree/attribute_tree/keyed_newick_reader.hpp>
#include <genesis/tree/attribute_tree/tree.hpp>
#include <genesis/tree/common_tree/tree.hpp>
#include <genesis/tree/formats/newick/broker.hpp>
#include <genesis/tree/formats/newick/element.hpp>
#include <genesis/tree/formats/newick/reader.hpp>
#include <genesis/tree/formats/newick/simple_tree.hpp>
#include <genesis/tree/tree.hpp>
#include <genesis/tree/tree/edge.hpp>
#include <genesis/tree/tree/edge_data.hpp>
#include <genesis/tree/tree/link.hpp>
#include <genesis/tree/tree/node.hpp>
#include <genesis/tree/tree/node_data.hpp>
#include <genesis/tree/tree_set.hpp>
#include <genesis/utils/containers/deref_iterator.hpp>
#include <genesis/utils/containers/range.hpp>
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

void bind_genesis_tree_attribute_tree_tree(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// genesis::tree::convert_common_tree_to_attribute_tree(const class genesis::tree::Tree &) file:genesis/tree/attribute_tree/tree.hpp line:211
	M("genesis::tree").def("convert_common_tree_to_attribute_tree", (class genesis::tree::Tree (*)(const class genesis::tree::Tree &)) &genesis::tree::convert_common_tree_to_attribute_tree, "Helper function that takes a CommonTree (or any Tree with Node and Edge data derived\n from it) and turns its data into an AttributeTree, that is, a Tree with\n \n\n\n\n\nC++: genesis::tree::convert_common_tree_to_attribute_tree(const class genesis::tree::Tree &) --> class genesis::tree::Tree", pybind11::arg("source"));

	{ // genesis::tree::IndexedAttributeTreeNewickReaderPlugin file:genesis/tree/attribute_tree/indexed_newick_reader.hpp line:95
		pybind11::class_<genesis::tree::IndexedAttributeTreeNewickReaderPlugin, std::shared_ptr<genesis::tree::IndexedAttributeTreeNewickReaderPlugin>> cl(M("genesis::tree"), "IndexedAttributeTreeNewickReaderPlugin", "Provide a set of plugin functions for NewickReader to read ordered attributes of the\n Nodes and Edges into an #AttributeTree.\n\n This class is a plugin that adds functionality to a NewickReader. The easiest way to use it is to\n instanciate a IndexedAttributeTreeNewickReader, which combines a NewickReader with this plugin.\n\n The class is useful for Newick trees that contain a fixed, ordered set of additional data stored\n for the nodes and edges of the tree, e.g.,\n\n     ((C,D)[0.1],(A,(B,X)[0.3])[0.2],E);\n\n This represents a Newick tree that contains bootstrap support values at the inner branches, where\n these data occur always as the first Newick comment for a given node.\n\n The plugin allows to process the following types of Newick data:\n\n   * Comments, of the form `[0.1]`, e.g., bootstrap values.\n   * Values, of the form `:3.14`, e.g., branch lengths.\n   * Tags, of the form `{42}`, e.g., edge numbers using in the `jplace` format.\n\n See NewickBrokerElement for more details on those Newick data types.\n\n The class offers two ways to process and store these data:\n\n   * add_attribute()\n   * add_catch_all()\n\n See there for details.\n\n Both ways use Source to select which Newick data to take (comments, values or tags), and use\n Target to select where to store it in the Tree (Nodes or Edges).\n\n Be aware that the latter is an important distinction, as the semantics of the data are not given\n by Newick. For example, storing bootstrap support values at Nodes insteda of Edges can lead to\n unexpected and wrong results. You are supposed to know what kind of data the Newick file you are\n processing contains. See also https://academic.oup.com/mbe/article-lookup/doi/10.1093/molbev/msx055\n\n This class is limited to the simple case where the Newick data is always stored in a certain\n order, i.e., the bootstrap values are always the first comment for a Newick node.\n Another common Newick data type are key-value-pairs, for example the New Hampshire eXtended (NHX)\n format. For such Newick trees, see KeyedAttributeTreeNewickReaderPlugin.\n If you have even more complex Newick data, you need to add your own NewickReader plugin functions.");
		cl.def( pybind11::init( [](){ return new genesis::tree::IndexedAttributeTreeNewickReaderPlugin(); } ) );
		cl.def( pybind11::init( [](genesis::tree::IndexedAttributeTreeNewickReaderPlugin const &o){ return new genesis::tree::IndexedAttributeTreeNewickReaderPlugin(o); } ) );

		pybind11::enum_<genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Source>(cl, "Source", "Select which kind of Newick data to take, i.e., either comments, values, or tags.\n\n See NewickBrokerElement for more details.")
			.value("kValue", genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Source::kValue)
			.value("kComment", genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Source::kComment)
			.value("kTag", genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Source::kTag);


		pybind11::enum_<genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Target>(cl, "Target", "Select where to store the data, i.e., at Nodes or Edges of the Tree.")
			.value("kNode", genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Target::kNode)
			.value("kEdge", genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Target::kEdge);

		cl.def("assign", (class genesis::tree::IndexedAttributeTreeNewickReaderPlugin & (genesis::tree::IndexedAttributeTreeNewickReaderPlugin::*)(const class genesis::tree::IndexedAttributeTreeNewickReaderPlugin &)) &genesis::tree::IndexedAttributeTreeNewickReaderPlugin::operator=, "C++: genesis::tree::IndexedAttributeTreeNewickReaderPlugin::operator=(const class genesis::tree::IndexedAttributeTreeNewickReaderPlugin &) --> class genesis::tree::IndexedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("add_attribute", (class genesis::tree::IndexedAttributeTreeNewickReaderPlugin & (genesis::tree::IndexedAttributeTreeNewickReaderPlugin::*)(enum genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Source, unsigned long, enum genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Target, const std::string &)) &genesis::tree::IndexedAttributeTreeNewickReaderPlugin::add_attribute, "Store the Newick data at a given  in an #AttributeTreeMap.\n\n Consider the exemplary Newick tree\n\n     ((C,D)[0.1],(A,(B,X)[0.3])[0.2],E);\n\n In this tree, Newick comments are used to store bootstrap support values. The values are\n always the first Newick comment of a node (if they occur), i.e. the comment with index `0`.\n\n To store these values in the \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nC++: genesis::tree::IndexedAttributeTreeNewickReaderPlugin::add_attribute(enum genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Source, unsigned long, enum genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Target, const std::string &) --> class genesis::tree::IndexedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal, pybind11::arg("source"), pybind11::arg("index"), pybind11::arg("target"), pybind11::arg("target_key"));
		cl.def("add_attribute", (class genesis::tree::IndexedAttributeTreeNewickReaderPlugin & (genesis::tree::IndexedAttributeTreeNewickReaderPlugin::*)(enum genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Source, unsigned long, enum genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Target, const std::string &, const std::string &)) &genesis::tree::IndexedAttributeTreeNewickReaderPlugin::add_attribute, "Store the Newick data at a given  in an #AttributeTreeMap, using a default\n value if there is no data at that index.\n\n The function behaves the same as\n add_attribute( Source, size_t, Target, std::string const& ) in cases where the given\n index is found at a Newick element.\n\n However, in cases where there is no corresponding index in the Newick element data, this\n function uses a default value in the attribute map, insted of ingoring it.\n\n For example, the Newick tree\n\n     ((C,D)[0.1],(A,(B,X)[0.3])[0.2],E);\n\n does not contain any bootstrap support values for the leaf nodes. That means, the\n \n\n\n\n\n\n\n\n\n\n\n\n\nC++: genesis::tree::IndexedAttributeTreeNewickReaderPlugin::add_attribute(enum genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Source, unsigned long, enum genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Target, const std::string &, const std::string &) --> class genesis::tree::IndexedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal, pybind11::arg("source"), pybind11::arg("index"), pybind11::arg("target"), pybind11::arg("target_key"), pybind11::arg("default_value"));
		cl.def("add_catch_all", (class genesis::tree::IndexedAttributeTreeNewickReaderPlugin & (genesis::tree::IndexedAttributeTreeNewickReaderPlugin::*)(enum genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Source, enum genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Target, const std::string &)) &genesis::tree::IndexedAttributeTreeNewickReaderPlugin::add_catch_all, "Store all Newick data of a given source in an #AttributeTreeMap.\n\n This function allows to capture all Newick data of a given type (comment, value or tag)\n and store it at a Tree element (Node or Edge), using a given prefix and a sequential number.\n\n For example, given the Newick tree\n\n     ((C,D)[inner_A],(A,(B,X)[inner_B])[inner_C],E);\n\n we can store all comments at the tree Nodes using\n\n ~~~{.cpp}\n IndexedAttributeTreeNewickReader reader;\n reader.add_catch_all(\n     IndexedAttributeTreeNewickReader::Source::kComment,\n     IndexedAttributeTreeNewickReader::Target::kNode,    \"comment_\"\n );\n auto tree = reader.read( from_file( \"path/to/tree.newick\" ));\n ~~~\n\n The resulting tree has attributes at the inner nodes, with the key `comment_0` and the values\n `inner_A`, `inner_B` and `inner_C`, respectively.\n\n Remark: This will store all data at either the Nodes or Edges of the Tree. This can lead\n to problems if some of the data actually belongs to the other element (Edges or Nodes).\n In these cases, better set the capturing explicitly, using add_attribute().\n\n \n            Input Newick element to take the data from. One of `kComment`,\n                          `kValue` or `kTag`.\n \n\n            Target Tree element to store the data at. Either `kNode` or `kEdge`.\n \n\n Prefix for the target key, to which a sequential number according\n                          to the index of the data is appended.\n\nC++: genesis::tree::IndexedAttributeTreeNewickReaderPlugin::add_catch_all(enum genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Source, enum genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Target, const std::string &) --> class genesis::tree::IndexedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal, pybind11::arg("source"), pybind11::arg("target"), pybind11::arg("target_key_prefix"));
		cl.def("add_catch_all", [](genesis::tree::IndexedAttributeTreeNewickReaderPlugin &o) -> genesis::tree::IndexedAttributeTreeNewickReaderPlugin & { return o.add_catch_all(); }, "", pybind11::return_value_policy::reference_internal);
		cl.def("add_catch_all", (class genesis::tree::IndexedAttributeTreeNewickReaderPlugin & (genesis::tree::IndexedAttributeTreeNewickReaderPlugin::*)(enum genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Target)) &genesis::tree::IndexedAttributeTreeNewickReaderPlugin::add_catch_all, "Store all Newick data in an #AttributeTreeMap.\n\n This is a simplification of add_catch_all(), which adds three catch-alls for\n the Newick comments, values and tags at once. It uses `comment_`, `value_` and `tag_` as\n key prefix, respectively. The function is meant for the most general use case, where we want\n to capture all Newick data and store it in an #AttributeTree.\n\n \n Optional parameter that can be used to specify where to store the data; default\n               is to store it at the Tree Nodes.\n\nC++: genesis::tree::IndexedAttributeTreeNewickReaderPlugin::add_catch_all(enum genesis::tree::IndexedAttributeTreeNewickReaderPlugin::Target) --> class genesis::tree::IndexedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal, pybind11::arg("target"));
		cl.def("clear", (void (genesis::tree::IndexedAttributeTreeNewickReaderPlugin::*)()) &genesis::tree::IndexedAttributeTreeNewickReaderPlugin::clear, "Reset all settings to the default, i.e., delete all attribute settings.\n\nC++: genesis::tree::IndexedAttributeTreeNewickReaderPlugin::clear() --> void");
		cl.def("element_to_node", (void (genesis::tree::IndexedAttributeTreeNewickReaderPlugin::*)(const struct genesis::tree::NewickBrokerElement &, class genesis::tree::TreeNode &) const) &genesis::tree::IndexedAttributeTreeNewickReaderPlugin::element_to_node, "C++: genesis::tree::IndexedAttributeTreeNewickReaderPlugin::element_to_node(const struct genesis::tree::NewickBrokerElement &, class genesis::tree::TreeNode &) const --> void", pybind11::arg("element"), pybind11::arg("node"));
		cl.def("element_to_edge", (void (genesis::tree::IndexedAttributeTreeNewickReaderPlugin::*)(const struct genesis::tree::NewickBrokerElement &, class genesis::tree::TreeEdge &) const) &genesis::tree::IndexedAttributeTreeNewickReaderPlugin::element_to_edge, "C++: genesis::tree::IndexedAttributeTreeNewickReaderPlugin::element_to_edge(const struct genesis::tree::NewickBrokerElement &, class genesis::tree::TreeEdge &) const --> void", pybind11::arg("element"), pybind11::arg("edge"));
		cl.def("register_with", (void (genesis::tree::IndexedAttributeTreeNewickReaderPlugin::*)(class genesis::tree::NewickReader &) const) &genesis::tree::IndexedAttributeTreeNewickReaderPlugin::register_with, "C++: genesis::tree::IndexedAttributeTreeNewickReaderPlugin::register_with(class genesis::tree::NewickReader &) const --> void", pybind11::arg("reader"));
	}
	{ // genesis::tree::IndexedAttributeTreeNewickReader file:genesis/tree/attribute_tree/indexed_newick_reader.hpp line:373
		pybind11::class_<genesis::tree::IndexedAttributeTreeNewickReader, std::shared_ptr<genesis::tree::IndexedAttributeTreeNewickReader>, genesis::tree::NewickReader, genesis::tree::CommonTreeNewickReaderPlugin, genesis::tree::IndexedAttributeTreeNewickReaderPlugin> cl(M("genesis::tree"), "IndexedAttributeTreeNewickReader", "Read Newick trees with ordered attributes for the Nodes and Edges.\n\n This class is a convenience wrapper that combines a NewickReader with an\n IndexedAttributeTreeNewickReaderPlugin. It is intended to be used for standard use cases, and\n produces a Tree with AttributeTreeNodeData and AttributeTreeEdgeData at its nodes and edges.\n\n It is also possible to register additional plugins on top of this class.");
		cl.def( pybind11::init( [](){ return new genesis::tree::IndexedAttributeTreeNewickReader(); } ) );
		cl.def( pybind11::init( [](genesis::tree::IndexedAttributeTreeNewickReader const &o){ return new genesis::tree::IndexedAttributeTreeNewickReader(o); } ) );
		cl.def("assign", (class genesis::tree::IndexedAttributeTreeNewickReader & (genesis::tree::IndexedAttributeTreeNewickReader::*)(const class genesis::tree::IndexedAttributeTreeNewickReader &)) &genesis::tree::IndexedAttributeTreeNewickReader::operator=, "C++: genesis::tree::IndexedAttributeTreeNewickReader::operator=(const class genesis::tree::IndexedAttributeTreeNewickReader &) --> class genesis::tree::IndexedAttributeTreeNewickReader &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
	}
	{ // genesis::tree::KeyedAttributeTreeNewickReaderPlugin file:genesis/tree/attribute_tree/keyed_newick_reader.hpp line:81
		pybind11::class_<genesis::tree::KeyedAttributeTreeNewickReaderPlugin, std::shared_ptr<genesis::tree::KeyedAttributeTreeNewickReaderPlugin>> cl(M("genesis::tree"), "KeyedAttributeTreeNewickReaderPlugin", "Provide a set of plugin functions for NewickReader to read key-value-pair data attributes\n into an #AttributeTree.\n\n This class is a plugin that adds functionality to a NewickReader. The easiest way to use it is to\n instanciate a KeyedAttributeTreeNewickReader, which combines a NewickReader with this plugin.\n\n The class can be used to read Newick trees that contain additional data in Newick comments, if\n this data is structured into key-value-pairs, e.g.,\n\n     ((C,D)[&!color=#009966],(A,(B,X)[&bs=82,!color=#137693])[&bs=70],E);\n\n This Newick tree contains a few values that represent branch colors (`color`) and bootstrap\n support values (`bs`).\n\n The class offers two ways to process and store these data:\n\n   * add_attribute()\n   * add_catch_all()\n\n Furthermore, it offers simple support for the New Hampshire eXtended (NHX) format, see\n set_nhx_delimiters() and add_nhx_attributes().\n\n By default, the classes uses `&` as the comment prefix, `,` as the separator between\n key-value-pairs, and `=` as the symbol between the key and the value. This is what the example\n above uses. In order to change those, use set_delimiters().\n\n Remark: This kind of key-value data is only useful in comments. Thus, different from the\n IndexedAttributeTreeNewickReaderPlugin, this plugin does not support Newick values or tags.");
		cl.def( pybind11::init( [](){ return new genesis::tree::KeyedAttributeTreeNewickReaderPlugin(); } ) );
		cl.def( pybind11::init( [](genesis::tree::KeyedAttributeTreeNewickReaderPlugin const &o){ return new genesis::tree::KeyedAttributeTreeNewickReaderPlugin(o); } ) );

		pybind11::enum_<genesis::tree::KeyedAttributeTreeNewickReaderPlugin::Target>(cl, "Target", "Select where to store the data, i.e., at Nodes or Edges of the Tree.")
			.value("kNode", genesis::tree::KeyedAttributeTreeNewickReaderPlugin::Target::kNode)
			.value("kEdge", genesis::tree::KeyedAttributeTreeNewickReaderPlugin::Target::kEdge);

		cl.def("assign", (class genesis::tree::KeyedAttributeTreeNewickReaderPlugin & (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)(const class genesis::tree::KeyedAttributeTreeNewickReaderPlugin &)) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::operator=, "C++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::operator=(const class genesis::tree::KeyedAttributeTreeNewickReaderPlugin &) --> class genesis::tree::KeyedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("add_attribute", (class genesis::tree::KeyedAttributeTreeNewickReaderPlugin & (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)(const std::string &, enum genesis::tree::KeyedAttributeTreeNewickReaderPlugin::Target)) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::add_attribute, "Store values of a  at a  (i.e., Node or Edge).\n\n For example, using the Newick tree\n\n     ((C,D)[&!color=#009966],(A,(B,X)[&bs=82,!color=#137693])[&bs=70],E);\n\n we can read the bootstrap support values (`bs`) and store them at the Edges like this:\n\n ~~~{.cpp}\n KeyedAttributeTreeNewickReader reader;\n reader.add_attribute( \"bs\", KeyedAttributeTreeNewickReader::Target::kEdge );\n auto tree = reader.read( from_file( \"path/to/tree.newick\" ));\n ~~~\n\n This is a simple form which uses the same key for the source (Newick comment) and target\n (Node or Edge), and does not use a default value, i.e., if the key is not found, no value\n is added to the target.\n\n See \n\n\n\n\n\n\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::add_attribute(const std::string &, enum genesis::tree::KeyedAttributeTreeNewickReaderPlugin::Target) --> class genesis::tree::KeyedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal, pybind11::arg("key"), pybind11::arg("target"));
		cl.def("add_attribute", (class genesis::tree::KeyedAttributeTreeNewickReaderPlugin & (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)(const std::string &, enum genesis::tree::KeyedAttributeTreeNewickReaderPlugin::Target, const std::string &)) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::add_attribute, "Store values of a  at a  (i.e., Node or Edge), using the\n \n\n Using this form, the source and target key can differ. For example, using the Newick tree\n\n     ((C,D)[&!color=#009966],(A,(B,X)[&bs=82,!color=#137693])[&bs=70],E);\n\n we can read the color values (`!color`) like this:\n\n ~~~{.cpp}\n KeyedAttributeTreeNewickReader reader;\n reader.add_attribute( \"!color\", KeyedAttributeTreeNewickReader::Target::kEdge, \"color\" );\n auto tree = reader.read( from_file( \"path/to/tree.newick\" ));\n ~~~\n\n which stores the values under the key `color` (without the leading exclamation mark).\n\n The function does not use default values. I.e., if the key is not found in the source comment,\n no value is added to the target.\n\n Also, see\n \n\n\n\n\n\n\n\n\n\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::add_attribute(const std::string &, enum genesis::tree::KeyedAttributeTreeNewickReaderPlugin::Target, const std::string &) --> class genesis::tree::KeyedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal, pybind11::arg("source_key"), pybind11::arg("target"), pybind11::arg("target_key"));
		cl.def("add_attribute", (class genesis::tree::KeyedAttributeTreeNewickReaderPlugin & (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)(const std::string &, enum genesis::tree::KeyedAttributeTreeNewickReaderPlugin::Target, const std::string &, const std::string &)) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::add_attribute, "Store values of a  at a  (i.e., Node or Edge), using the\n  and a  if the key is not found in the source.\n\n This is the most flexible form of this function. It is similar to\n \n\n\n\n\n\n\n\n\n\n\n\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::add_attribute(const std::string &, enum genesis::tree::KeyedAttributeTreeNewickReaderPlugin::Target, const std::string &, const std::string &) --> class genesis::tree::KeyedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal, pybind11::arg("source_key"), pybind11::arg("target"), pybind11::arg("target_key"), pybind11::arg("default_value"));
		cl.def("add_catch_all", [](genesis::tree::KeyedAttributeTreeNewickReaderPlugin &o) -> genesis::tree::KeyedAttributeTreeNewickReaderPlugin & { return o.add_catch_all(); }, "", pybind11::return_value_policy::reference_internal);
		cl.def("add_catch_all", (class genesis::tree::KeyedAttributeTreeNewickReaderPlugin & (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)(enum genesis::tree::KeyedAttributeTreeNewickReaderPlugin::Target)) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::add_catch_all, "Store all key-value-pairs of the Newick data in an #AttributeTree.\n\n This function allows to capture all Newick comment data in key-value-form and store it\n at a Tree element (Node or Edge).\n\n For example, given the Newick tree\n\n     ((C,D)[&!color=#009966],(A,(B,X)[&bs=82,!color=#137693])[&bs=70],E);\n\n we can store all data at the tree Edges using\n\n ~~~{.cpp}\n KeyedAttributeTreeNewickReader reader;\n reader.add_catch_all( KeyedAttributeTreeNewickReader::Target::kEdge );\n auto tree = reader.read( from_file( \"path/to/tree.newick\" ));\n ~~~\n\n Remark: This will store all data at either the Nodes or Edges of the Tree. This can lead\n to problems if some of the data actually belongs to the other element (Edges or Nodes).\n In these cases, better set the captureing explicitly, using add_attribute().\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::add_catch_all(enum genesis::tree::KeyedAttributeTreeNewickReaderPlugin::Target) --> class genesis::tree::KeyedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal, pybind11::arg("target"));
		cl.def("add_nhx_attributes", (class genesis::tree::KeyedAttributeTreeNewickReaderPlugin & (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)()) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::add_nhx_attributes, "Add typical attributes of the NHX format, and set the appropriate delimiters.\n\n The New Hampshire eXtended (NHX) format is an extension of the Newick format that uses\n specially formatted Newick comments to store additional data for the nodes and edges of a\n tree. See for example https://sites.google.com/site/cmzmasek/home/software/forester/nhx\n and https://home.cc.umanitoba.ca/~psgendb/doc/atv/NHX.pdf for details.\n\n This function adds capturing for the following keys:\n\n Key | Target | Description\n ----|--------|-------------------------------------------------------------------------------\n AC  | Node   | sequence accession\n B   | Edge   | confidence value for parent branch\n Co  | Node   | collapse this node when drawing the tree (default is not to collapse)\n D   | Node   | duplication event\n E   | Node   | EC number\n GN  | Node   | gene name\n L   | Edge   | log likelihood value on parent branch\n O   | Node   | orthologous to this external node\n S   | Node   | species name\n SO  | Node   | \"super orthologous\" (no duplications on paths)\n Sw  | Edge   | placing a subtree on the parent branch of this node makes the tree significantly worse according to Kishino/Hasegawa test (or similar)\n T   | Node   | taxonomy ID\n\n If you need other NHX keys, want to use different keys for the target, or want to use default\n values for keys that are not present in the Newick data, please use the normal\n add_attribute() functions or add_catch_all() instead.\n This is only meant to be a very basic simplification for supporting NHX.\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::add_nhx_attributes() --> class genesis::tree::KeyedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal);
		cl.def("set_nhx_delimiters", (class genesis::tree::KeyedAttributeTreeNewickReaderPlugin & (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)()) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::set_nhx_delimiters, "Set the delimiters to the format used by NHX.\n\n These are\n\n   * Prefix: `&&NHX`\n   * Separator: `:`\n   * Assigner: `=`\n\n See add_nhx_attributes() for details on the NHX format.\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::set_nhx_delimiters() --> class genesis::tree::KeyedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal);
		cl.def("set_delimiters", [](genesis::tree::KeyedAttributeTreeNewickReaderPlugin &o, const std::string & a0, const std::string & a1) -> genesis::tree::KeyedAttributeTreeNewickReaderPlugin & { return o.set_delimiters(a0, a1); }, "", pybind11::return_value_policy::reference_internal, pybind11::arg("prefix"), pybind11::arg("separator"));
		cl.def("set_delimiters", (class genesis::tree::KeyedAttributeTreeNewickReaderPlugin & (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)(const std::string &, const std::string &, const std::string &)) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::set_delimiters, "Set the delimiters for key-value-pairs.\n\n This function is a shortcut to set the prefix(), separator() and assigner() at once.\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::set_delimiters(const std::string &, const std::string &, const std::string &) --> class genesis::tree::KeyedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal, pybind11::arg("prefix"), pybind11::arg("separator"), pybind11::arg("assigner"));
		cl.def("prefix", (class genesis::tree::KeyedAttributeTreeNewickReaderPlugin & (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)(const std::string &)) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::prefix, "Set the prefix to look for in Newick comments.\n\n Default is `&`, as used in the examples of this class.\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::prefix(const std::string &) --> class genesis::tree::KeyedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("prefix", (std::string (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)() const) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::prefix, "Get the currently set prefix to look for in Newick comments.\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::prefix() const --> std::string");
		cl.def("separator", (class genesis::tree::KeyedAttributeTreeNewickReaderPlugin & (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)(const std::string &)) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::separator, "Set the separator between key-value-pairs.\n\n Default is `,`, as used in the examples of this class.\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::separator(const std::string &) --> class genesis::tree::KeyedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("separator", (std::string (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)() const) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::separator, "Get the currently set separator between key-value-pairs.\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::separator() const --> std::string");
		cl.def("assigner", (class genesis::tree::KeyedAttributeTreeNewickReaderPlugin & (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)(const std::string &)) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::assigner, "Set the assign symbol between a key and its value.\n\n Default is `=`, as used in the examples of this class.\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::assigner(const std::string &) --> class genesis::tree::KeyedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("assigner", (std::string (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)() const) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::assigner, "Get the currently set assign symbol between a key and its value.\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::assigner() const --> std::string");
		cl.def("trim", (class genesis::tree::KeyedAttributeTreeNewickReaderPlugin & (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)(bool)) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::trim, "Set whether to trim keys and values before storing them in the Tree.\n\n Default is `true`.\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::trim(bool) --> class genesis::tree::KeyedAttributeTreeNewickReaderPlugin &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("trim", (bool (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)() const) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::trim, "Get whether to trim keys and values before storing them in the Tree.\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::trim() const --> bool");
		cl.def("clear", (void (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)()) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::clear, "Reset all settings to the default and delete all attribute settings.\n\nC++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::clear() --> void");
		cl.def("element_to_node", (void (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)(const struct genesis::tree::NewickBrokerElement &, class genesis::tree::TreeNode &) const) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::element_to_node, "C++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::element_to_node(const struct genesis::tree::NewickBrokerElement &, class genesis::tree::TreeNode &) const --> void", pybind11::arg("element"), pybind11::arg("node"));
		cl.def("element_to_edge", (void (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)(const struct genesis::tree::NewickBrokerElement &, class genesis::tree::TreeEdge &) const) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::element_to_edge, "C++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::element_to_edge(const struct genesis::tree::NewickBrokerElement &, class genesis::tree::TreeEdge &) const --> void", pybind11::arg("element"), pybind11::arg("edge"));
		cl.def("register_with", (void (genesis::tree::KeyedAttributeTreeNewickReaderPlugin::*)(class genesis::tree::NewickReader &) const) &genesis::tree::KeyedAttributeTreeNewickReaderPlugin::register_with, "C++: genesis::tree::KeyedAttributeTreeNewickReaderPlugin::register_with(class genesis::tree::NewickReader &) const --> void", pybind11::arg("reader"));
	}
}
