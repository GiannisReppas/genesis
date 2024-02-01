#include <functional>
#include <genesis/population/formats/variant_input_iterator.hpp>
#include <genesis/population/variant.hpp>
#include <genesis/utils/containers/lambda_iterator.hpp>
#include <genesis/utils/core/thread_pool.hpp>
#include <memory>
#include <sstream> // __str__

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

void bind_genesis_utils_containers_lambda_iterator(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // genesis::utils::EmptyLambdaIteratorData file:genesis/utils/containers/lambda_iterator.hpp line:52
		pybind11::class_<genesis::utils::EmptyLambdaIteratorData, std::shared_ptr<genesis::utils::EmptyLambdaIteratorData>> cl(M("genesis::utils"), "EmptyLambdaIteratorData", "Empty helper data struct to serve as a dummy for LambdaIterator.\n\n By default, the LambdaIterator::Data type does not do anything.\n This class here serves as the empty dummy class, so that the user does not have to\n provide one when using LambdaIterator without an extra data type.");
		cl.def( pybind11::init( [](){ return new genesis::utils::EmptyLambdaIteratorData(); } ) );
	}
	{ // genesis::utils::LambdaIterator file:genesis/utils/containers/lambda_iterator.hpp line:162
		pybind11::class_<genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>, std::shared_ptr<genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>>> cl(M("genesis::utils"), "LambdaIterator_genesis_population_Variant_genesis_population_VariantInputIteratorData_t", "");
		cl.def( pybind11::init( [](){ return new genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>(); } ) );
		cl.def( pybind11::init( [](genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData> const &o){ return new genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>(o); } ) );
		cl.def("assign", (class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> & (genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>::*)(const class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &)) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::operator=, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::operator=(const class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &) --> class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("begin", (class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator (genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>::*)()) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::begin, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::begin() --> class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator");
		cl.def("end", (class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator (genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>::*)()) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::end, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::end() --> class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator");
		cl.def("data", (struct genesis::population::VariantInputIteratorData & (genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>::*)()) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::data, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::data() --> struct genesis::population::VariantInputIteratorData &", pybind11::return_value_policy::reference_internal);
		cl.def("add_transform", (class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> & (genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>::*)(const class std::function<void (struct genesis::population::Variant &)> &)) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::add_transform, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::add_transform(const class std::function<void (struct genesis::population::Variant &)> &) --> class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &", pybind11::return_value_policy::reference_internal, pybind11::arg("transform"));
		cl.def("add_filter", (class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> & (genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>::*)(const class std::function<bool (const struct genesis::population::Variant &)> &)) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::add_filter, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::add_filter(const class std::function<bool (const struct genesis::population::Variant &)> &) --> class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &", pybind11::return_value_policy::reference_internal, pybind11::arg("filter"));
		cl.def("add_transform_filter", (class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> & (genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>::*)(const class std::function<bool (struct genesis::population::Variant &)> &)) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::add_transform_filter, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::add_transform_filter(const class std::function<bool (struct genesis::population::Variant &)> &) --> class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &", pybind11::return_value_policy::reference_internal, pybind11::arg("filter"));
		cl.def("clear_filters_and_transformations", (class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> & (genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>::*)()) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::clear_filters_and_transformations, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::clear_filters_and_transformations() --> class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &", pybind11::return_value_policy::reference_internal);
		cl.def("add_observer", (class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> & (genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>::*)(const class std::function<void (const struct genesis::population::Variant &)> &)) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::add_observer, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::add_observer(const class std::function<void (const struct genesis::population::Variant &)> &) --> class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &", pybind11::return_value_policy::reference_internal, pybind11::arg("observer"));
		cl.def("clear_observers", (class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> & (genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>::*)()) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::clear_observers, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::clear_observers() --> class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &", pybind11::return_value_policy::reference_internal);
		cl.def("add_begin_callback", (class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> & (genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>::*)(const class std::function<void (const class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &)> &)) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::add_begin_callback, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::add_begin_callback(const class std::function<void (const class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &)> &) --> class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &", pybind11::return_value_policy::reference_internal, pybind11::arg("callback"));
		cl.def("add_end_callback", (class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> & (genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>::*)(const class std::function<void (const class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &)> &)) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::add_end_callback, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::add_end_callback(const class std::function<void (const class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &)> &) --> class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &", pybind11::return_value_policy::reference_internal, pybind11::arg("callback"));
		cl.def("clear_callbacks", (class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> & (genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>::*)()) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::clear_callbacks, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::clear_callbacks() --> class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &", pybind11::return_value_policy::reference_internal);
		cl.def("block_size", (unsigned long (genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>::*)() const) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::block_size, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::block_size() const --> unsigned long");
		cl.def("block_size", (class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> & (genesis::utils::LambdaIterator<genesis::population::Variant,genesis::population::VariantInputIteratorData>::*)(unsigned long)) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::block_size, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::block_size(unsigned long) --> class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData> &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));

		{ // genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator file:genesis/utils/containers/lambda_iterator.hpp line:195
			auto & enclosing_class = cl;
			pybind11::class_<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, std::shared_ptr<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator>> cl(enclosing_class, "Iterator", "");
			cl.def( pybind11::init( [](){ return new genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator(); } ) );
			cl.def( pybind11::init( [](genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator const &o){ return new genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator(o); } ) );
			cl.def("assign", (class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator & (genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::*)(const class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator &)) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::operator=, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::operator=(const class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator &) --> class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
			cl.def("arrow", (struct genesis::population::Variant * (genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::*)()) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::operator->, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::operator->() --> struct genesis::population::Variant *", pybind11::return_value_policy::reference_internal);
			cl.def("dereference", (struct genesis::population::Variant & (genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::*)()) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::operator*, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::operator*() --> struct genesis::population::Variant &", pybind11::return_value_policy::reference_internal);
			cl.def("data", (const struct genesis::population::VariantInputIteratorData & (genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::*)() const) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::data, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::data() const --> const struct genesis::population::VariantInputIteratorData &", pybind11::return_value_policy::reference_internal);
			cl.def("pre_increment", (class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator & (genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::*)()) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::operator++, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::operator++() --> class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator &", pybind11::return_value_policy::reference_internal);
			cl.def("__eq__", (bool (genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::*)(const class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator &) const) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::operator==, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::operator==(const class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator &) const --> bool", pybind11::arg("other"));
			cl.def("__ne__", (bool (genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::*)(const class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator &) const) &genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::operator!=, "C++: genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator::operator!=(const class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator &) const --> bool", pybind11::arg("other"));
		}

	}
}