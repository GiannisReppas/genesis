#include <genesis/population/genome_region_list.hpp>
#include <genesis/utils/containers/interval_tree.hpp>
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

void bind_genesis_utils_containers_interval_tree(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // genesis::utils::IntervalTree file:genesis/utils/containers/interval_tree.hpp line:78
		pybind11::class_<genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>, std::shared_ptr<genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>>> cl(M("genesis::utils"), "IntervalTree_genesis_population_EmptyGenomeData_unsigned_long_genesis_utils_IntervalClosed_t", "");
		cl.def( pybind11::init( [](){ return new genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>(); } ) );
		cl.def( pybind11::init( [](genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed> const &o){ return new genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>(o); } ) );
		cl.def("assign", (class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> & (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(const class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &)) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::operator=, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::operator=(const class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) --> class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &", pybind11::return_value_policy::reference_internal, pybind11::arg("other"));
		cl.def("size", (unsigned long (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::size, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::size() const --> unsigned long");
		cl.def("empty", (bool (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::empty, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::empty() const --> bool");
		cl.def("root", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)()) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::root, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::root() --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>");
		cl.def("lowest", (unsigned long (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::lowest, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::lowest() const --> unsigned long");
		cl.def("highest", (unsigned long (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::highest, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::highest() const --> unsigned long");
		cl.def("begin", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)()) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::begin, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::begin() --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>");
		cl.def("end", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)()) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::end, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::end() --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>");
		cl.def("cbegin", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::cbegin, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::cbegin() const --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true>");
		cl.def("cend", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::cend, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::cend() const --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true>");
		cl.def("find", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &)) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::find, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::find(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>", pybind11::arg("ival"));
		cl.def("find_next_in_subtree", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>, const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &)) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::find_next_in_subtree, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::find_next_in_subtree(class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>, const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>", pybind11::arg("from"), pybind11::arg("ival"));
		cl.def("overlap_find", [](genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed> &o, const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> & a0) -> genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> { return o.overlap_find(a0); }, "", pybind11::arg("ival"));
		cl.def("overlap_find", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &, bool)) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::overlap_find, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::overlap_find(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &, bool) --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>", pybind11::arg("ival"), pybind11::arg("exclusive"));
		cl.def("overlap_find", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(unsigned long)) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::overlap_find, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::overlap_find(unsigned long) --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>", pybind11::arg("position"));
		cl.def("clear", (void (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)()) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::clear, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::clear() --> void");
		cl.def("insert", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &)) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::insert, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::insert(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>", pybind11::arg("ival"));
		cl.def("insert_overlap", [](genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed> &o, const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> & a0) -> genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> { return o.insert_overlap(a0); }, "", pybind11::arg("ival"));
		cl.def("insert_overlap", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &, bool)) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::insert_overlap, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::insert_overlap(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &, bool) --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>", pybind11::arg("ival"), pybind11::arg("exclusive"));
		cl.def("insert_overlap", [](genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed> &o, const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> & a0, const struct genesis::population::EmptyGenomeData & a1) -> genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> { return o.insert_overlap(a0, a1); }, "", pybind11::arg("ival"), pybind11::arg("data"));
		cl.def("insert_overlap", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &, const struct genesis::population::EmptyGenomeData &, bool)) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::insert_overlap, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::insert_overlap(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &, const struct genesis::population::EmptyGenomeData &, bool) --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>", pybind11::arg("ival"), pybind11::arg("data"), pybind11::arg("exclusive"));
		cl.def("erase", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>)) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::erase, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::erase(class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>) --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, false>", pybind11::arg("iter"));
		cl.def("flatten", (class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> & (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)()) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::flatten, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::flatten() --> class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &", pybind11::return_value_policy::reference_internal);
		cl.def("flatten_copy", (class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)()) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::flatten_copy, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::flatten_copy() --> class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>");
		cl.def("punch", (class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::punch, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::punch() const --> class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>");
		cl.def("punch", (class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> (genesis::utils::IntervalTree<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) const) &genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::punch, "C++: genesis::utils::IntervalTree<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::punch(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) const --> class genesis::utils::IntervalTree<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>", pybind11::arg("ival"));
	}
}
