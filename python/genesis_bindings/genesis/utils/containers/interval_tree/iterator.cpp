#include <genesis/population/genome_region_list.hpp>
#include <genesis/utils/containers/interval_tree/functions.hpp>
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
#include <genesis/population/genome_region_list.hpp>
#include <../python/custom_bindings/extensions/population/chromosome_iterator.hpp>
#include <pybind11/stl.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_genesis_utils_containers_interval_tree_iterator(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // genesis::utils::IntervalTreeIterator file:genesis/utils/containers/interval_tree/iterator.hpp line:71
		pybind11::class_<genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>, std::shared_ptr<genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>>, std::forward_iterator_tag> cl(M("genesis::utils"), "IntervalTreeIterator_genesis_utils_IntervalTreeNode_genesis_population_EmptyGenomeData_unsigned_long_genesis_utils_IntervalClosed_true_t", "");
		cl.def( pybind11::init( [](genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true> const &o){ return new genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>(o); } ) );
		cl.def("assign", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> & (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>::*)(const class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> &)) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::operator=, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::operator=(const class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> &) --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("__ne__", (bool (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>::*)(const class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> &) const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::operator!=, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::operator!=(const class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> &) const --> bool", pybind11::arg("other"));
		cl.def("__eq__", (bool (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>::*)(const class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> &) const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::operator==, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::operator==(const class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> &) const --> bool", pybind11::arg("other"));
		cl.def("pre_increment", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> & (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>::*)()) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::operator++, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::operator++() --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> &", pybind11::return_value_policy::reference_internal);
		cl.def("post_increment", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>::*)(int)) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::operator++, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::operator++(int) --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true>", pybind11::arg(""));
		cl.def("dereference", (const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> & (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::operator*, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::operator*() const --> const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &", pybind11::return_value_policy::reference_internal);
		cl.def("arrow", (const class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> * (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::operator->, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::operator->() const --> const class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> *", pybind11::return_value_policy::reference_internal);
		cl.def("parent", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::parent, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::parent() const --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true>");
		cl.def("left", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::left, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::left() const --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true>");
		cl.def("right", (class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true> (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::right, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::right() const --> class genesis::utils::IntervalTreeIterator<class genesis::utils::IntervalTreeNode<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>, true>");
		cl.def("max", (unsigned long (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::max, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::max() const --> unsigned long");
		cl.def("color", (enum genesis::utils::RedBackColor (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::color, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::color() const --> enum genesis::utils::RedBackColor");
		cl.def("interval", (const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> & (genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>,true>::*)() const) &genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::interval, "C++: genesis::utils::IntervalTreeIterator<genesis::utils::IntervalTreeNode<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>, true>::interval() const --> const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &", pybind11::return_value_policy::reference_internal);
		cl.def("assign", (struct std::forward_iterator_tag & (std::forward_iterator_tag::*)(const struct std::forward_iterator_tag &)) &std::forward_iterator_tag::operator=, "C++: std::forward_iterator_tag::operator=(const struct std::forward_iterator_tag &) --> struct std::forward_iterator_tag &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
	}
	{ // genesis::utils::EmptyIntervalData file:genesis/utils/containers/interval_tree/interval.hpp line:70
		pybind11::class_<genesis::utils::EmptyIntervalData, std::shared_ptr<genesis::utils::EmptyIntervalData>> cl(M("genesis::utils"), "EmptyIntervalData", "Empty class used as default for Interval data.\n\n An Interval offers to store some data with with it, which is for example useful when working\n with annotated genome regions. By default however, we do not want to store any data,\n and use this class as a dummy,");
		cl.def( pybind11::init( [](){ return new genesis::utils::EmptyIntervalData(); } ) );
	}
	{ // genesis::utils::IntervalLeftOpen file:genesis/utils/containers/interval_tree/interval.hpp line:84
		pybind11::class_<genesis::utils::IntervalLeftOpen, std::shared_ptr<genesis::utils::IntervalLeftOpen>> cl(M("genesis::utils"), "IntervalLeftOpen", "Helper type to define a left open `(]` Interval.");
		cl.def( pybind11::init( [](){ return new genesis::utils::IntervalLeftOpen(); } ) );
	}
	{ // genesis::utils::IntervalRightOpen file:genesis/utils/containers/interval_tree/interval.hpp line:118
		pybind11::class_<genesis::utils::IntervalRightOpen, std::shared_ptr<genesis::utils::IntervalRightOpen>> cl(M("genesis::utils"), "IntervalRightOpen", "Helper type to define a right open `[)` Interval.");
		cl.def( pybind11::init( [](){ return new genesis::utils::IntervalRightOpen(); } ) );
	}
	{ // genesis::utils::IntervalOpen file:genesis/utils/containers/interval_tree/interval.hpp line:152
		pybind11::class_<genesis::utils::IntervalOpen, std::shared_ptr<genesis::utils::IntervalOpen>> cl(M("genesis::utils"), "IntervalOpen", "Helper type to define an open `()` Interval.");
		cl.def( pybind11::init( [](){ return new genesis::utils::IntervalOpen(); } ) );
	}
	{ // genesis::utils::IntervalClosed file:genesis/utils/containers/interval_tree/interval.hpp line:208
		pybind11::class_<genesis::utils::IntervalClosed, std::shared_ptr<genesis::utils::IntervalClosed>> cl(M("genesis::utils"), "IntervalClosed", "Helper type to define a closed `[]` Interval.");
		cl.def( pybind11::init( [](){ return new genesis::utils::IntervalClosed(); } ) );
	}
	// genesis::utils::join(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &, const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &, const struct genesis::population::EmptyGenomeData &) file:genesis/utils/containers/interval_tree/functions.hpp line:144
	M("genesis::utils").def("join", (struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> (*)(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &, const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &, const struct genesis::population::EmptyGenomeData &)) &genesis::utils::join<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>, "C++: genesis::utils::join(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &, const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &, const struct genesis::population::EmptyGenomeData &) --> struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed>", pybind11::arg("a"), pybind11::arg("b"), pybind11::arg("data"));

}
