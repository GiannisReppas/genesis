#include <genesis/utils/math/bitvector.hpp>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <vector>

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

void bind_std_genesis_utils_math_bitvector(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // std::hash file:genesis/utils/math/bitvector.hpp line:470
		pybind11::class_<std::hash<genesis::utils::Bitvector>, std::shared_ptr<std::hash<genesis::utils::Bitvector>>> cl(M("std"), "hash_genesis_utils_Bitvector_t", "Specialization of std::hash for the Bitvector class.\n\n It uses Bitvector::hash() for the hashing. See also BitvectorHash for an alternative class\n that does the same, but resides in the same namespace as Bitvector, and see BitvectorXhash\n for a variant that uses Bitvector::x_hash() instead as the hashing function.");
		cl.def( pybind11::init( [](){ return new std::hash<genesis::utils::Bitvector>(); } ) );
		cl.def("__call__", (unsigned long (std::hash<genesis::utils::Bitvector>::*)(const class genesis::utils::Bitvector &) const) &std::hash<genesis::utils::Bitvector>::operator(), "C++: std::hash<genesis::utils::Bitvector>::operator()(const class genesis::utils::Bitvector &) const --> unsigned long", pybind11::arg("value"));
	}
}
