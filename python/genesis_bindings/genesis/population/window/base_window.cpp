#include <functional>
#include <genesis/population/formats/variant_input_iterator.hpp>
#include <genesis/population/genome_region.hpp>
#include <genesis/population/variant.hpp>
#include <genesis/population/window/base_window.hpp>
#include <genesis/population/window/base_window_iterator.hpp>
#include <genesis/population/window/functions.hpp>
#include <genesis/population/window/window.hpp>
#include <genesis/population/window/window_view.hpp>
#include <genesis/utils/containers/lambda_iterator.hpp>
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

// genesis::population::BaseWindow file:genesis/population/window/base_window.hpp line:52
struct PyCallBack_genesis_population_BaseWindow_genesis_population_Variant_t : public genesis::population::BaseWindow<genesis::population::Variant> {
	using genesis::population::BaseWindow<genesis::population::Variant>::BaseWindow;

	void clear_() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const genesis::population::BaseWindow<genesis::population::Variant> *>(this), "clear_");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return BaseWindow::clear_();
	}
};

// genesis::population::BaseWindowIterator file:genesis/population/window/base_window_iterator.hpp line:111
struct PyCallBack_genesis_population_BaseWindowIterator_genesis_utils_LambdaIterator_genesis_population_Variant_genesis_population_VariantInputIteratorData_Iterator_genesis_population_Variant_genesis_population_WindowView_genesis_population_Variant_t : public genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>> {
	using genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>::BaseWindowIterator;

	using _binder_ret_0 = class std::unique_ptr<class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> >::BaseIterator, struct std::default_delete<class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> >::BaseIterator> >;
	_binder_ret_0 get_begin_iterator_() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>> *>(this), "get_begin_iterator_");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<_binder_ret_0>::value) {
				static pybind11::detail::override_caster_t<_binder_ret_0> caster;
				return pybind11::detail::cast_ref<_binder_ret_0>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<_binder_ret_0>(std::move(o));
		}
		pybind11::pybind11_fail("Tried to call pure virtual function \"BaseWindowIterator::get_begin_iterator_\"");
	}
	using _binder_ret_1 = class std::unique_ptr<class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> >::BaseIterator, struct std::default_delete<class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> >::BaseIterator> >;
	_binder_ret_1 get_end_iterator_() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>> *>(this), "get_end_iterator_");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<_binder_ret_1>::value) {
				static pybind11::detail::override_caster_t<_binder_ret_1> caster;
				return pybind11::detail::cast_ref<_binder_ret_1>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<_binder_ret_1>(std::move(o));
		}
		pybind11::pybind11_fail("Tried to call pure virtual function \"BaseWindowIterator::get_end_iterator_\"");
	}
};

void bind_genesis_population_window_base_window(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // genesis::population::BaseWindow file:genesis/population/window/base_window.hpp line:52
		pybind11::class_<genesis::population::BaseWindow<genesis::population::Variant>, std::shared_ptr<genesis::population::BaseWindow<genesis::population::Variant>>, PyCallBack_genesis_population_BaseWindow_genesis_population_Variant_t> cl(M("genesis::population"), "BaseWindow_genesis_population_Variant_t", "");
		cl.def( pybind11::init( [](){ return new genesis::population::BaseWindow<genesis::population::Variant>(); }, [](){ return new PyCallBack_genesis_population_BaseWindow_genesis_population_Variant_t(); } ) );
		cl.def( pybind11::init( [](PyCallBack_genesis_population_BaseWindow_genesis_population_Variant_t const &o){ return new PyCallBack_genesis_population_BaseWindow_genesis_population_Variant_t(o); } ) );
		cl.def( pybind11::init( [](genesis::population::BaseWindow<genesis::population::Variant> const &o){ return new genesis::population::BaseWindow<genesis::population::Variant>(o); } ) );
		cl.def("assign", (class genesis::population::BaseWindow<struct genesis::population::Variant> & (genesis::population::BaseWindow<genesis::population::Variant>::*)(const class genesis::population::BaseWindow<struct genesis::population::Variant> &)) &genesis::population::BaseWindow<genesis::population::Variant>::operator=, "C++: genesis::population::BaseWindow<genesis::population::Variant>::operator=(const class genesis::population::BaseWindow<struct genesis::population::Variant> &) --> class genesis::population::BaseWindow<struct genesis::population::Variant> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("chromosome", (const std::string & (genesis::population::BaseWindow<genesis::population::Variant>::*)() const) &genesis::population::BaseWindow<genesis::population::Variant>::chromosome, "C++: genesis::population::BaseWindow<genesis::population::Variant>::chromosome() const --> const std::string &", pybind11::return_value_policy::reference_internal);
		cl.def("chromosome", (void (genesis::population::BaseWindow<genesis::population::Variant>::*)(const std::string &)) &genesis::population::BaseWindow<genesis::population::Variant>::chromosome, "C++: genesis::population::BaseWindow<genesis::population::Variant>::chromosome(const std::string &) --> void", pybind11::arg("value"));
		cl.def("first_position", (unsigned long (genesis::population::BaseWindow<genesis::population::Variant>::*)() const) &genesis::population::BaseWindow<genesis::population::Variant>::first_position, "C++: genesis::population::BaseWindow<genesis::population::Variant>::first_position() const --> unsigned long");
		cl.def("first_position", (void (genesis::population::BaseWindow<genesis::population::Variant>::*)(unsigned long)) &genesis::population::BaseWindow<genesis::population::Variant>::first_position, "C++: genesis::population::BaseWindow<genesis::population::Variant>::first_position(unsigned long) --> void", pybind11::arg("value"));
		cl.def("last_position", (unsigned long (genesis::population::BaseWindow<genesis::population::Variant>::*)() const) &genesis::population::BaseWindow<genesis::population::Variant>::last_position, "C++: genesis::population::BaseWindow<genesis::population::Variant>::last_position() const --> unsigned long");
		cl.def("last_position", (void (genesis::population::BaseWindow<genesis::population::Variant>::*)(unsigned long)) &genesis::population::BaseWindow<genesis::population::Variant>::last_position, "C++: genesis::population::BaseWindow<genesis::population::Variant>::last_position(unsigned long) --> void", pybind11::arg("value"));
		cl.def("genome_region", (struct genesis::population::GenomeRegion (genesis::population::BaseWindow<genesis::population::Variant>::*)() const) &genesis::population::BaseWindow<genesis::population::Variant>::genome_region, "C++: genesis::population::BaseWindow<genesis::population::Variant>::genome_region() const --> struct genesis::population::GenomeRegion");
		cl.def("width", (unsigned long (genesis::population::BaseWindow<genesis::population::Variant>::*)() const) &genesis::population::BaseWindow<genesis::population::Variant>::width, "C++: genesis::population::BaseWindow<genesis::population::Variant>::width() const --> unsigned long");
		cl.def("clear", (void (genesis::population::BaseWindow<genesis::population::Variant>::*)()) &genesis::population::BaseWindow<genesis::population::Variant>::clear, "C++: genesis::population::BaseWindow<genesis::population::Variant>::clear() --> void");
	}
	{ // genesis::population::EmptyAccumulator file:genesis/population/window/window.hpp line:57
		pybind11::class_<genesis::population::EmptyAccumulator, std::shared_ptr<genesis::population::EmptyAccumulator>> cl(M("genesis::population"), "EmptyAccumulator", "Empty helper data struct to serve as a dummy for Window.\n\n By default, the Window::Accumulator type does not do anything, because most of the time, we\n do not need it. This class here serves as that empty class, so that the user does not have to\n provide one when using Window without an accumulator.");
		cl.def( pybind11::init( [](){ return new genesis::population::EmptyAccumulator(); } ) );
	}
	{ // genesis::population::WindowView file:genesis/population/window/window_view.hpp line:76
		pybind11::class_<genesis::population::WindowView<genesis::population::Variant>, std::shared_ptr<genesis::population::WindowView<genesis::population::Variant>>, genesis::population::BaseWindow<genesis::population::Variant>> cl(M("genesis::population"), "WindowView_genesis_population_Variant_t", "");
		cl.def( pybind11::init( [](){ return new genesis::population::WindowView<genesis::population::Variant>(); } ) );
		cl.def( pybind11::init( [](genesis::population::WindowView<genesis::population::Variant> const &o){ return new genesis::population::WindowView<genesis::population::Variant>(o); } ) );
		cl.def_readwrite("get_element", &genesis::population::WindowView<genesis::population::Variant>::get_element);
		cl.def("assign", (class genesis::population::WindowView<struct genesis::population::Variant> & (genesis::population::WindowView<genesis::population::Variant>::*)(const class genesis::population::WindowView<struct genesis::population::Variant> &)) &genesis::population::WindowView<genesis::population::Variant>::operator=, "C++: genesis::population::WindowView<genesis::population::Variant>::operator=(const class genesis::population::WindowView<struct genesis::population::Variant> &) --> class genesis::population::WindowView<struct genesis::population::Variant> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("assign", (class genesis::population::BaseWindow<struct genesis::population::Variant> & (genesis::population::BaseWindow<genesis::population::Variant>::*)(const class genesis::population::BaseWindow<struct genesis::population::Variant> &)) &genesis::population::BaseWindow<genesis::population::Variant>::operator=, "C++: genesis::population::BaseWindow<genesis::population::Variant>::operator=(const class genesis::population::BaseWindow<struct genesis::population::Variant> &) --> class genesis::population::BaseWindow<struct genesis::population::Variant> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("chromosome", (const std::string & (genesis::population::BaseWindow<genesis::population::Variant>::*)() const) &genesis::population::BaseWindow<genesis::population::Variant>::chromosome, "C++: genesis::population::BaseWindow<genesis::population::Variant>::chromosome() const --> const std::string &", pybind11::return_value_policy::reference_internal);
		cl.def("chromosome", (void (genesis::population::BaseWindow<genesis::population::Variant>::*)(const std::string &)) &genesis::population::BaseWindow<genesis::population::Variant>::chromosome, "C++: genesis::population::BaseWindow<genesis::population::Variant>::chromosome(const std::string &) --> void", pybind11::arg("value"));
		cl.def("first_position", (unsigned long (genesis::population::BaseWindow<genesis::population::Variant>::*)() const) &genesis::population::BaseWindow<genesis::population::Variant>::first_position, "C++: genesis::population::BaseWindow<genesis::population::Variant>::first_position() const --> unsigned long");
		cl.def("first_position", (void (genesis::population::BaseWindow<genesis::population::Variant>::*)(unsigned long)) &genesis::population::BaseWindow<genesis::population::Variant>::first_position, "C++: genesis::population::BaseWindow<genesis::population::Variant>::first_position(unsigned long) --> void", pybind11::arg("value"));
		cl.def("last_position", (unsigned long (genesis::population::BaseWindow<genesis::population::Variant>::*)() const) &genesis::population::BaseWindow<genesis::population::Variant>::last_position, "C++: genesis::population::BaseWindow<genesis::population::Variant>::last_position() const --> unsigned long");
		cl.def("last_position", (void (genesis::population::BaseWindow<genesis::population::Variant>::*)(unsigned long)) &genesis::population::BaseWindow<genesis::population::Variant>::last_position, "C++: genesis::population::BaseWindow<genesis::population::Variant>::last_position(unsigned long) --> void", pybind11::arg("value"));
		cl.def("genome_region", (struct genesis::population::GenomeRegion (genesis::population::BaseWindow<genesis::population::Variant>::*)() const) &genesis::population::BaseWindow<genesis::population::Variant>::genome_region, "C++: genesis::population::BaseWindow<genesis::population::Variant>::genome_region() const --> struct genesis::population::GenomeRegion");
		cl.def("width", (unsigned long (genesis::population::BaseWindow<genesis::population::Variant>::*)() const) &genesis::population::BaseWindow<genesis::population::Variant>::width, "C++: genesis::population::BaseWindow<genesis::population::Variant>::width() const --> unsigned long");
		cl.def("clear", (void (genesis::population::BaseWindow<genesis::population::Variant>::*)()) &genesis::population::BaseWindow<genesis::population::Variant>::clear, "C++: genesis::population::BaseWindow<genesis::population::Variant>::clear() --> void");
	}
	// genesis::population::WindowAnchorType file:genesis/population/window/functions.hpp line:57
	pybind11::enum_<genesis::population::WindowAnchorType>(M("genesis::population"), "WindowAnchorType", "Position in the genome that is used for reporting when emitting or using a window.\n\n See anchor_position() for details. The interval-based types are available for any BaseWindow\n type, that is, for Window and for WindowView for instance. The variant-based types however\n require random access to the data in the window, and hence are not applicable to WindowView.")
		.value("kIntervalBegin", genesis::population::WindowAnchorType::kIntervalBegin)
		.value("kIntervalEnd", genesis::population::WindowAnchorType::kIntervalEnd)
		.value("kIntervalMidpoint", genesis::population::WindowAnchorType::kIntervalMidpoint)
		.value("kVariantFirst", genesis::population::WindowAnchorType::kVariantFirst)
		.value("kVariantLast", genesis::population::WindowAnchorType::kVariantLast)
		.value("kVariantMedian", genesis::population::WindowAnchorType::kVariantMedian)
		.value("kVariantMean", genesis::population::WindowAnchorType::kVariantMean)
		.value("kVariantMidpoint", genesis::population::WindowAnchorType::kVariantMidpoint);

;

	{ // genesis::population::BaseWindowIterator file:genesis/population/window/base_window_iterator.hpp line:111
		pybind11::class_<genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>, std::shared_ptr<genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>>, PyCallBack_genesis_population_BaseWindowIterator_genesis_utils_LambdaIterator_genesis_population_Variant_genesis_population_VariantInputIteratorData_Iterator_genesis_population_Variant_genesis_population_WindowView_genesis_population_Variant_t> cl(M("genesis::population"), "BaseWindowIterator_genesis_utils_LambdaIterator_genesis_population_Variant_genesis_population_VariantInputIteratorData_Iterator_genesis_population_Variant_genesis_population_WindowView_genesis_population_Variant_t", "");
		cl.def( pybind11::init<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator>(), pybind11::arg("begin"), pybind11::arg("end") );

		cl.def(pybind11::init<PyCallBack_genesis_population_BaseWindowIterator_genesis_utils_LambdaIterator_genesis_population_Variant_genesis_population_VariantInputIteratorData_Iterator_genesis_population_Variant_genesis_population_WindowView_genesis_population_Variant_t const &>());
		cl.def_readwrite("entry_input_function", &genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>::entry_input_function);
		cl.def_readwrite("chromosome_function", &genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>::chromosome_function);
		cl.def_readwrite("position_function", &genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>::position_function);
		cl.def("assign", (class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > & (genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>::*)(const class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > &)) &genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant, genesis::population::WindowView<genesis::population::Variant>>::operator=, "C++: genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant, genesis::population::WindowView<genesis::population::Variant>>::operator=(const class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > &) --> class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("add_visitor", (class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > & (genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>::*)(const class std::function<void (const class genesis::population::WindowView<struct genesis::population::Variant> &)> &)) &genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant, genesis::population::WindowView<genesis::population::Variant>>::add_visitor, "C++: genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant, genesis::population::WindowView<genesis::population::Variant>>::add_visitor(const class std::function<void (const class genesis::population::WindowView<struct genesis::population::Variant> &)> &) --> class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > &", pybind11::return_value_policy::reference_internal, pybind11::arg("visitor"));
		cl.def("clear_visitors", (class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > & (genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant,genesis::population::WindowView<genesis::population::Variant>>::*)()) &genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant, genesis::population::WindowView<genesis::population::Variant>>::clear_visitors, "C++: genesis::population::BaseWindowIterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator, genesis::population::Variant, genesis::population::WindowView<genesis::population::Variant>>::clear_visitors() --> class genesis::population::BaseWindowIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant, class genesis::population::WindowView<struct genesis::population::Variant> > &", pybind11::return_value_policy::reference_internal);
	}
}
