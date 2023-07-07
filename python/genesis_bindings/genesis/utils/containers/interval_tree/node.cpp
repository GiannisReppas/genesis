#include <genesis/utils/containers/interval_tree/interval.hpp>
#include <genesis/utils/containers/interval_tree/iterator.hpp>
#include <genesis/utils/containers/interval_tree/node.hpp>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>

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
#include <../python/custom_bindings/extensions/common_node_data.hpp>
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

void bind_genesis_utils_containers_interval_tree_node(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // genesis::utils::IntervalTreeNode file:genesis/utils/containers/interval_tree/node.hpp line:91
		pybind11::class_<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>, std::shared_ptr<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>>> cl(M("genesis::utils"), "IntervalTreeNode_genesis_population_EmptyGenomeData_unsigned_long_genesis_utils_IntervalClosed_t", "");
		cl.def( pybind11::init<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> *, const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &>(), pybind11::arg("parent"), pybind11::arg("interval") );

		cl.def( pybind11::init( [](genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed> const &o){ return new genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>(o); } ) );
		cl.def("assign", (class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> & (genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(const class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &)) &genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::operator=, "C++: genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::operator=(const class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) --> class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("interval", (const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> & (genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::interval, "C++: genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::interval() const --> const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &", pybind11::return_value_policy::reference_internal);
		cl.def("max", (unsigned long (genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::max, "C++: genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::max() const --> unsigned long");
		cl.def("is_left", (bool (genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::is_left, "C++: genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::is_left() const --> bool");
		cl.def("is_right", (bool (genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::is_right, "C++: genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::is_right() const --> bool");
		cl.def("is_root", (bool (genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::is_root, "C++: genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::is_root() const --> bool");
		cl.def("color", (enum genesis::utils::RedBackColor (genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::color, "C++: genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::color() const --> enum genesis::utils::RedBackColor");
		cl.def("parent", (const class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> * (genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::parent, "C++: genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::parent() const --> const class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> *", pybind11::return_value_policy::reference_internal);
		cl.def("left", (const class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> * (genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::left, "C++: genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::left() const --> const class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> *", pybind11::return_value_policy::reference_internal);
		cl.def("right", (const class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> * (genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::right, "C++: genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::right() const --> const class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> *", pybind11::return_value_policy::reference_internal);
		cl.def("height", (unsigned long (genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::height, "C++: genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::height() const --> unsigned long");
		cl.def("low", (unsigned long (genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::low, "C++: genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::low() const --> unsigned long");
		cl.def("high", (unsigned long (genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::high, "C++: genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::high() const --> unsigned long");
	}
	{ // genesis::utils::IntervalTreeIterator file:genesis/utils/containers/interval_tree/iterator.hpp line:71
		pybind11::class_<genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>, std::shared_ptr<genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>>, std::forward_iterator_tag> cl(M("genesis::utils"), "IntervalTreeIterator_genesis_utils_IntervalTreeNode_genesis_population_EmptyGenomeData_unsigned_long_genesis_utils_IntervalClosed_false_t", "");
		cl.def( pybind11::init( [](genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false> const &o){ return new genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>(o); } ) );
		cl.def("assign", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> & (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>::*)(const class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> &)) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::operator=, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::operator=(const class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> &) --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("__ne__", (bool (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>::*)(const class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> &) const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::operator!=, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::operator!=(const class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> &) const --> bool", pybind11::arg("other"));
		cl.def("__eq__", (bool (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>::*)(const class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> &) const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::operator==, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::operator==(const class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> &) const --> bool", pybind11::arg("other"));
		cl.def("pre_increment", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> & (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>::*)()) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::operator++, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::operator++() --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> &", pybind11::return_value_policy::reference_internal);
		cl.def("post_increment", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>::*)(int)) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::operator++, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::operator++(int) --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>", pybind11::arg(""));
		cl.def("dereference", (const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> & (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::operator*, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::operator*() const --> const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &", pybind11::return_value_policy::reference_internal);
		cl.def("arrow", (const class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> * (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::operator->, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::operator->() const --> const class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> *", pybind11::return_value_policy::reference_internal);
		cl.def("parent", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::parent, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::parent() const --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>");
		cl.def("left", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::left, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::left() const --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>");
		cl.def("right", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::right, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::right() const --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>");
		cl.def("max", (unsigned long (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::max, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::max() const --> unsigned long");
		cl.def("color", (enum genesis::utils::RedBackColor (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::color, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::color() const --> enum genesis::utils::RedBackColor");
		cl.def("interval", (const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> & (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,false>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::interval, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, false>::interval() const --> const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &", pybind11::return_value_policy::reference_internal);
		cl.def("assign", (struct std::forward_iterator_tag & (std::forward_iterator_tag::*)(const struct std::forward_iterator_tag &)) &std::forward_iterator_tag::operator=, "C++: std::forward_iterator_tag::operator=(const struct std::forward_iterator_tag &) --> struct std::forward_iterator_tag &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
	}
}
