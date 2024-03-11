#include <genesis/population/functions/functions.hpp>
#include <genesis/population/variant.hpp>
#include <genesis/sequence/reference_genome.hpp>
#include <genesis/sequence/sequence.hpp>
#include <iterator>
#include <memory>
#include <string>
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
#include <genesis/population/genome_region_list.hpp>
#include <../python/custom_bindings/extensions/population/chromosome_iterator.hpp>
#include <pybind11/stl.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_genesis_population_functions_functions(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// genesis::population::guess_and_set_ref_and_alt_bases(struct genesis::population::Variant &, bool) file:genesis/population/functions/functions.hpp line:269
	M("genesis::population").def("guess_and_set_ref_and_alt_bases", [](struct genesis::population::Variant & a0) -> void { return genesis::population::guess_and_set_ref_and_alt_bases(a0); }, "", pybind11::arg("variant"));
	M("genesis::population").def("guess_and_set_ref_and_alt_bases", (void (*)(struct genesis::population::Variant &, bool)) &genesis::population::guess_and_set_ref_and_alt_bases, "Guess the reference and alternative bases for a Variant, and set them.\n\n This uses the same approach as guess_reference_base() and guess_alternative_base(),\n but is more efficient than calling both in sequence. See there for details.\n\nC++: genesis::population::guess_and_set_ref_and_alt_bases(struct genesis::population::Variant &, bool) --> void", pybind11::arg("variant"), pybind11::arg("force"));

	// genesis::population::guess_and_set_ref_and_alt_bases(struct genesis::population::Variant &, const class genesis::sequence::ReferenceGenome &, bool) file:genesis/population/functions/functions.hpp line:285
	M("genesis::population").def("guess_and_set_ref_and_alt_bases", [](struct genesis::population::Variant & a0, const class genesis::sequence::ReferenceGenome & a1) -> void { return genesis::population::guess_and_set_ref_and_alt_bases(a0, a1); }, "", pybind11::arg("variant"), pybind11::arg("ref_genome"));
	M("genesis::population").def("guess_and_set_ref_and_alt_bases", (void (*)(struct genesis::population::Variant &, const class genesis::sequence::ReferenceGenome &, bool)) &genesis::population::guess_and_set_ref_and_alt_bases, "Guess the reference and alternative bases for a Variant, and set them,\n using a ReferenceGenome to get the reference base where possible.\n\n This uses the same approach as guess_and_set_ref_and_alt_bases( Variant&, bool ), but\n additionally consideres the given  If the reference genome contains a value\n in `ACGT` (case insensitive) at the position of the  it is used as the reference.\n Note that the function throws an exception should the reference base already be set to a different\n value, in order to notify users that something is off.\n\n If the reference genome is `N` though, the function behaves the same as its reference-free\n alternative. For the alternative base, it always uses the most abundant base that is not the\n reference, same as its alternative function.\n\nC++: genesis::population::guess_and_set_ref_and_alt_bases(struct genesis::population::Variant &, const class genesis::sequence::ReferenceGenome &, bool) --> void", pybind11::arg("variant"), pybind11::arg("ref_genome"), pybind11::arg("force"));

}
