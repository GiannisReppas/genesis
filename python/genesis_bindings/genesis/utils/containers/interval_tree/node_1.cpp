#include <genesis/utils/containers/interval_tree/node.hpp>

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

void bind_genesis_utils_containers_interval_tree_node_1(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// genesis::utils::RedBackColor file:genesis/utils/containers/interval_tree/node.hpp line:65
	pybind11::enum_<genesis::utils::RedBackColor>(M("genesis::utils"), "RedBackColor", "Definition for Red-Black Tree coloring.\n\n Used in IntervalTree and IntervalTreeNode.")
		.value("kInvalid", genesis::utils::RedBackColor::kInvalid)
		.value("kRed", genesis::utils::RedBackColor::kRed)
		.value("kBlack", genesis::utils::RedBackColor::kBlack)
		.value("kKDoubleBlack", genesis::utils::RedBackColor::kKDoubleBlack);

;

}
