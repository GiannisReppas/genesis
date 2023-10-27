#include <../python/custom_bindings/template_instances/chromosome_iterator.hpp>
#include <../python/custom_bindings/template_instances/lambda_iterator.hpp>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>
#include <pybind11/functional.h>
#include <../python/custom_bindings/extensions/matrix.hpp>
#include <genesis/utils/color/functions.hpp>
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
#include <../python/custom_bindings/extensions/chromosome_iterator.hpp>
#include <pybind11/stl.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind____python_custom_bindings_template_instances_lambda_iterator(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// template_lambda_iterator_variant_variant_input_data() file:../python/custom_bindings/template_instances/lambda_iterator.hpp line:8
	M("").def("template_lambda_iterator_variant_variant_input_data", (void (*)()) &template_lambda_iterator_variant_variant_input_data, "C++: template_lambda_iterator_variant_variant_input_data() --> void");

	// template_chromosome_iterator_lambda_iterator_variant_variant_input_data() file:../python/custom_bindings/template_instances/chromosome_iterator.hpp line:10
	M("").def("template_chromosome_iterator_lambda_iterator_variant_variant_input_data", (void (*)()) &template_chromosome_iterator_lambda_iterator_variant_variant_input_data, "C++: template_chromosome_iterator_lambda_iterator_variant_variant_input_data() --> void");

}
