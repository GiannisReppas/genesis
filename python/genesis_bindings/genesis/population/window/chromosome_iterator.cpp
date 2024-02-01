#include <genesis/population/formats/variant_input_iterator.hpp>
#include <genesis/population/variant.hpp>
#include <genesis/population/window/chromosome_iterator.hpp>
#include <genesis/sequence/sequence_dict.hpp>
#include <genesis/utils/containers/lambda_iterator.hpp>
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

void bind_genesis_population_window_chromosome_iterator(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // genesis::population::ChromosomeIterator file:genesis/population/window/chromosome_iterator.hpp line:96
		pybind11::class_<genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant>, std::shared_ptr<genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant>>, genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>> cl(M("genesis::population"), "ChromosomeIterator_genesis_utils_LambdaIterator_genesis_population_Variant_genesis_population_VariantInputIteratorData_Iterator_genesis_population_Variant_t", "");
		cl.def( pybind11::init<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator>(), pybind11::arg("begin"), pybind11::arg("end") );

		cl.def( pybind11::init( [](genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant> const &o){ return new genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant>(o); } ) );
		cl.def("assign", (class genesis::population::ChromosomeIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant> & (genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant>::*)(const class genesis::population::ChromosomeIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant> &)) &genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::operator=, "C++: genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::operator=(const class genesis::population::ChromosomeIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant> &) --> class genesis::population::ChromosomeIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("whole_genome", (bool (genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant>::*)() const) &genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::whole_genome, "C++: genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::whole_genome() const --> bool");
		cl.def("whole_genome", (class genesis::population::ChromosomeIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant> & (genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant>::*)(bool)) &genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::whole_genome, "C++: genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::whole_genome(bool) --> class genesis::population::ChromosomeIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant> &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def("sequence_dict", (class std::shared_ptr<class genesis::sequence::SequenceDict> (genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant>::*)() const) &genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::sequence_dict, "C++: genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::sequence_dict() const --> class std::shared_ptr<class genesis::sequence::SequenceDict>");
		cl.def("sequence_dict", (class genesis::population::ChromosomeIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant> & (genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant>::*)(class std::shared_ptr<class genesis::sequence::SequenceDict>)) &genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::sequence_dict, "C++: genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::sequence_dict(class std::shared_ptr<class genesis::sequence::SequenceDict>) --> class genesis::population::ChromosomeIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant> &", pybind11::return_value_policy::reference_internal, pybind11::arg("value"));
		cl.def_readwrite("entry_input_function", &genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>::entry_input_function);
		cl.def_readwrite("chromosome_function", &genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>::chromosome_function);
		cl.def_readwrite("position_function", &genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>::position_function);
		cl.def("assign", (class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > & (genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>::*)(const class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > &)) &genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant, genesis::population::WindowView<genesis::population::Variant>>::operator=, "C++: genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant, genesis::population::WindowView<genesis::population::Variant>>::operator=(const class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > &) --> class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("add_visitor", (class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > & (genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>::*)(const class std::function<void (const class genesis::population::WindowView<struct genesis::population::Variant> &)> &)) &genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant, genesis::population::WindowView<genesis::population::Variant>>::add_visitor, "C++: genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant, genesis::population::WindowView<genesis::population::Variant>>::add_visitor(const class std::function<void (const class genesis::population::WindowView<struct genesis::population::Variant> &)> &) --> class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > &", pybind11::return_value_policy::reference_internal, pybind11::arg("visitor"));
		cl.def("clear_visitors", (class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > & (genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>::*)()) &genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant, genesis::population::WindowView<genesis::population::Variant>>::clear_visitors, "C++: genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant, genesis::population::WindowView<genesis::population::Variant>>::clear_visitors() --> class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > &", pybind11::return_value_policy::reference_internal);

		{ // genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::DerivedIterator file:genesis/population/window/chromosome_iterator.hpp line:129
			auto & enclosing_class = cl;
			pybind11::class_<genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::DerivedIterator, std::shared_ptr<genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::DerivedIterator>> cl(enclosing_class, "DerivedIterator", "");
			cl.def( pybind11::init( [](genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::DerivedIterator const &o){ return new genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::DerivedIterator(o); } ) );
			cl.def("assign", (class genesis::population::ChromosomeIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant>::DerivedIterator & (genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::DerivedIterator::*)(const class genesis::population::ChromosomeIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant>::DerivedIterator &)) &genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::DerivedIterator::operator=, "C++: genesis::population::ChromosomeIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant>::DerivedIterator::operator=(const class genesis::population::ChromosomeIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant>::DerivedIterator &) --> class genesis::population::ChromosomeIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant>::DerivedIterator &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		}

	}
}