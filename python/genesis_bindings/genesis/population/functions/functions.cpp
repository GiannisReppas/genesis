#include <genesis/population/base_counts.hpp>
#include <genesis/population/functions/functions.hpp>
#include <genesis/population/variant.hpp>
#include <genesis/sequence/reference_genome.hpp>
#include <genesis/sequence/sequence.hpp>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>

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

void bind_genesis_population_functions_functions(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// genesis::population::is_valid_base_or_n(char) file:genesis/population/functions/functions.hpp line:70
	M("genesis::population").def("is_valid_base_or_n", (bool (*)(char)) &genesis::population::is_valid_base_or_n, "Return whether a given base is in `ACGTN`, case insensitive.\n\nC++: genesis::population::is_valid_base_or_n(char) --> bool", pybind11::arg("c"));

	// genesis::population::get_base_count(const struct genesis::population::BaseCounts &, char) file:genesis/population/functions/functions.hpp line:88
	M("genesis::population").def("get_base_count", (unsigned long (*)(const struct genesis::population::BaseCounts &, char)) &genesis::population::get_base_count, "Get the count for a  given as a char.\n\n The given  has to be one of `ACGTDN` (case insensitive), or `*#.` for deletions as well.\n\nC++: genesis::population::get_base_count(const struct genesis::population::BaseCounts &, char) --> unsigned long", pybind11::arg("sample"), pybind11::arg("base"));

	// genesis::population::set_base_count(struct genesis::population::BaseCounts &, char, unsigned long) file:genesis/population/functions/functions.hpp line:95
	M("genesis::population").def("set_base_count", (void (*)(struct genesis::population::BaseCounts &, char, unsigned long)) &genesis::population::set_base_count, "Set the count for a  given as a char.\n\n The given  has to be one of `ACGTDN` (case insensitive), or `*#.` for deletions as well.\n\nC++: genesis::population::set_base_count(struct genesis::population::BaseCounts &, char, unsigned long) --> void", pybind11::arg("sample"), pybind11::arg("base"), pybind11::arg("value"));

	// genesis::population::sorted_base_counts(const struct genesis::population::BaseCounts &) file:genesis/population/functions/functions.hpp line:104
	M("genesis::population").def("sorted_base_counts", (struct genesis::population::SortedBaseCounts (*)(const struct genesis::population::BaseCounts &)) &genesis::population::sorted_base_counts, "Return the order of base counts (nucleotides), largest one first.\n\nC++: genesis::population::sorted_base_counts(const struct genesis::population::BaseCounts &) --> struct genesis::population::SortedBaseCounts", pybind11::arg("sample"));

	// genesis::population::sorted_average_base_counts(const struct genesis::population::BaseCounts &, const struct genesis::population::BaseCounts &) file:genesis/population/functions/functions.hpp line:113
	M("genesis::population").def("sorted_average_base_counts", (struct std::pair<struct genesis::population::SortedBaseCounts, struct genesis::population::SortedBaseCounts> (*)(const struct genesis::population::BaseCounts &, const struct genesis::population::BaseCounts &)) &genesis::population::sorted_average_base_counts, "Return the sorted base counts of both input samples, orderd by the average\n frequencies of the nucleotide counts in the two samples.\n\n Both returned counts will be in the same order, with the nucleotide first that has the highest\n average count in the two samples, etc.\n\nC++: genesis::population::sorted_average_base_counts(const struct genesis::population::BaseCounts &, const struct genesis::population::BaseCounts &) --> struct std::pair<struct genesis::population::SortedBaseCounts, struct genesis::population::SortedBaseCounts>", pybind11::arg("sample_a"), pybind11::arg("sample_b"));

	// genesis::population::sorted_base_counts(const struct genesis::population::Variant &, bool) file:genesis/population/functions/functions.hpp line:125
	M("genesis::population").def("sorted_base_counts", (struct genesis::population::SortedBaseCounts (*)(const struct genesis::population::Variant &, bool)) &genesis::population::sorted_base_counts, "Get a list of bases sorted by their counts.\n\n If  is set to `true`, the first entry in the resulting array is always\n the reference base of the Variant, while the other three bases are sorted by counts.\n If  is set to `false`, all four bases are sorted by their counts.\n\nC++: genesis::population::sorted_base_counts(const struct genesis::population::Variant &, bool) --> struct genesis::population::SortedBaseCounts", pybind11::arg("variant"), pybind11::arg("reference_first"));

	// genesis::population::allele_count(const struct genesis::population::BaseCounts &) file:genesis/population/functions/functions.hpp line:139
	M("genesis::population").def("allele_count", (unsigned long (*)(const struct genesis::population::BaseCounts &)) &genesis::population::allele_count, "Return the number of alleles, that is, of non-zero nucleotide counts of the \n\n This looks at all four nucleotide counts (`ACGT`), and returns the number of them that are\n non zero, which hence is between 0 and 4.\n\nC++: genesis::population::allele_count(const struct genesis::population::BaseCounts &) --> unsigned long", pybind11::arg("sample"));

	// genesis::population::merge_inplace(struct genesis::population::BaseCounts &, const struct genesis::population::BaseCounts &) file:genesis/population/functions/functions.hpp line:145
	M("genesis::population").def("merge_inplace", (void (*)(struct genesis::population::BaseCounts &, const struct genesis::population::BaseCounts &)) &genesis::population::merge_inplace, "Merge the counts of two BaseCounts%s, by adding the counts of the second (\n to the first (\n \n\nC++: genesis::population::merge_inplace(struct genesis::population::BaseCounts &, const struct genesis::population::BaseCounts &) --> void", pybind11::arg("p1"), pybind11::arg("p2"));

	// genesis::population::merge(const struct genesis::population::BaseCounts &, const struct genesis::population::BaseCounts &) file:genesis/population/functions/functions.hpp line:150
	M("genesis::population").def("merge", (struct genesis::population::BaseCounts (*)(const struct genesis::population::BaseCounts &, const struct genesis::population::BaseCounts &)) &genesis::population::merge, "Merge the counts of two BaseCounts%s.\n\nC++: genesis::population::merge(const struct genesis::population::BaseCounts &, const struct genesis::population::BaseCounts &) --> struct genesis::population::BaseCounts", pybind11::arg("p1"), pybind11::arg("p2"));

	// genesis::population::merge(const class std::vector<struct genesis::population::BaseCounts, class std::allocator<struct genesis::population::BaseCounts> > &) file:genesis/population/functions/functions.hpp line:155
	M("genesis::population").def("merge", (struct genesis::population::BaseCounts (*)(const class std::vector<struct genesis::population::BaseCounts, class std::allocator<struct genesis::population::BaseCounts> > &)) &genesis::population::merge, "Merge the counts of a vector BaseCounts%s.\n\nC++: genesis::population::merge(const class std::vector<struct genesis::population::BaseCounts, class std::allocator<struct genesis::population::BaseCounts> > &) --> struct genesis::population::BaseCounts", pybind11::arg("p"));

	// genesis::population::merge_base_counts(const struct genesis::population::Variant &) file:genesis/population/functions/functions.hpp line:160
	M("genesis::population").def("merge_base_counts", (struct genesis::population::BaseCounts (*)(const struct genesis::population::Variant &)) &genesis::population::merge_base_counts, "Merge the counts of a vector BaseCounts%s.\n\nC++: genesis::population::merge_base_counts(const struct genesis::population::Variant &) --> struct genesis::population::BaseCounts", pybind11::arg("v"));

	// genesis::population::nucleotide_sum(const struct genesis::population::BaseCounts &) file:genesis/population/functions/functions.hpp line:174
	M("genesis::population").def("nucleotide_sum", (unsigned long (*)(const struct genesis::population::BaseCounts &)) &genesis::population::nucleotide_sum, "Count of the pure nucleotide bases at this position, that is,\n the sum of all `A`, `C`, `G`, and `T`.\n\n This is simply the sum of `a_count + c_count + g_count + t_count`, which we often use as the\n coverage at the given site.\n\n NB: In PoPoolation, this variable is called `eucov`.\n\nC++: genesis::population::nucleotide_sum(const struct genesis::population::BaseCounts &) --> unsigned long", pybind11::arg("sample"));

	// genesis::population::total_nucleotide_sum(const struct genesis::population::Variant &) file:genesis/population/functions/functions.hpp line:184
	M("genesis::population").def("total_nucleotide_sum", (unsigned long (*)(const struct genesis::population::Variant &)) &genesis::population::total_nucleotide_sum, "nucleotide_sum( BaseCounts const& )\n\n See nucleotide_sum() for details. This function gives the sum over all samples in the Variant.\n\nC++: genesis::population::total_nucleotide_sum(const struct genesis::population::Variant &) --> unsigned long", pybind11::arg("variant"));

	// genesis::population::consensus(const struct genesis::population::BaseCounts &) file:genesis/population/functions/functions.hpp line:202
	M("genesis::population").def("consensus", (struct std::pair<char, double> (*)(const struct genesis::population::BaseCounts &)) &genesis::population::consensus, "Consensus character for a BaseCounts, and its confidence.\n\n This is simply the character (out of `ACGT`) that appears most often (or, for ties,\n the lexicographically smallest character), unless all of (`A`, `C`, `G`, `T`) are zero,\n in which case the consensus character is `N`.\n The confidence is the count of the consensus character, divided by the total count\n of all four nucleotides.\n\nC++: genesis::population::consensus(const struct genesis::population::BaseCounts &) --> struct std::pair<char, double>", pybind11::arg("sample"));

	// genesis::population::consensus(const struct genesis::population::BaseCounts &, bool) file:genesis/population/functions/functions.hpp line:213
	M("genesis::population").def("consensus", (struct std::pair<char, double> (*)(const struct genesis::population::BaseCounts &, bool)) &genesis::population::consensus, "Consensus character for a BaseCounts, and its confidence.\n\n This is simply the character (out of `ACGT`) that appears most often (or, for ties,\n the lexicographically smallest character). If  is false (meaning, the position is\n not well covered by reads), the consensus character is `N`.\n The confidence is the count of the consensus character, divided by the total count\n of all four nucleotides.\n\nC++: genesis::population::consensus(const struct genesis::population::BaseCounts &, bool) --> struct std::pair<char, double>", pybind11::arg("sample"), pybind11::arg("is_covered"));

	// genesis::population::guess_reference_base(const struct genesis::population::Variant &, bool) file:genesis/population/functions/functions.hpp line:224
	M("genesis::population").def("guess_reference_base", [](const struct genesis::population::Variant & a0) -> char { return genesis::population::guess_reference_base(a0); }, "", pybind11::arg("variant"));
	M("genesis::population").def("guess_reference_base", (char (*)(const struct genesis::population::Variant &, bool)) &genesis::population::guess_reference_base, "Guess the reference base of a Variant.\n\n If the Variant already has a `reference_base` in `ACGT`, this base is returned (meaning that\n this function is idempotent; it does not change the reference base if there already is one).\n However, if the `reference_base` is `N` or any other value not in `ACGT`, or if  is `true`,\n the base with the highest count is returned instead,\n unless all counts are 0, in which case the returned reference base is `N`.\n\nC++: genesis::population::guess_reference_base(const struct genesis::population::Variant &, bool) --> char", pybind11::arg("variant"), pybind11::arg("force"));

	// genesis::population::guess_alternative_base(const struct genesis::population::Variant &, bool) file:genesis/population/functions/functions.hpp line:239
	M("genesis::population").def("guess_alternative_base", [](const struct genesis::population::Variant & a0) -> char { return genesis::population::guess_alternative_base(a0); }, "", pybind11::arg("variant"));
	M("genesis::population").def("guess_alternative_base", (char (*)(const struct genesis::population::Variant &, bool)) &genesis::population::guess_alternative_base, "Guess the alternative base of a Variant.\n\n If the Variant already has an `alternative_base` in `ACGT` and  is not `true`,\n this original base is returned (meaning that this function is idempotent; it does not change\n the alternative base if there already is one).\n However, if the `alternative_base` is `N` or any other char not in `ACGT`, or if  is `true`,\n the base with the highest count that is not the reference base is returned instead.\n This also means that the reference base has to be set to a value in `ACGT`,\n as otherwise the concept of an alternative base is meaningless anyway.\n If the reference base is not one of `ACGT`, the returned alternative base is `N`.\n Furthermore, if all three non-reference bases have count 0, the returned alternative base is `N`.\n\nC++: genesis::population::guess_alternative_base(const struct genesis::population::Variant &, bool) --> char", pybind11::arg("variant"), pybind11::arg("force"));

	// genesis::population::guess_and_set_ref_and_alt_bases(struct genesis::population::Variant &, bool) file:genesis/population/functions/functions.hpp line:247
	M("genesis::population").def("guess_and_set_ref_and_alt_bases", [](struct genesis::population::Variant & a0) -> void { return genesis::population::guess_and_set_ref_and_alt_bases(a0); }, "", pybind11::arg("variant"));
	M("genesis::population").def("guess_and_set_ref_and_alt_bases", (void (*)(struct genesis::population::Variant &, bool)) &genesis::population::guess_and_set_ref_and_alt_bases, "Guess the reference and alternative bases for a Variant, and set them.\n\n This uses the same approach as guess_reference_base() and guess_alternative_base(),\n but is more efficient than calling both in sequence. See there for details.\n\nC++: genesis::population::guess_and_set_ref_and_alt_bases(struct genesis::population::Variant &, bool) --> void", pybind11::arg("variant"), pybind11::arg("force"));

	// genesis::population::guess_and_set_ref_and_alt_bases(struct genesis::population::Variant &, const class genesis::sequence::ReferenceGenome &, bool) file:genesis/population/functions/functions.hpp line:263
	M("genesis::population").def("guess_and_set_ref_and_alt_bases", [](struct genesis::population::Variant & a0, const class genesis::sequence::ReferenceGenome & a1) -> void { return genesis::population::guess_and_set_ref_and_alt_bases(a0, a1); }, "", pybind11::arg("variant"), pybind11::arg("ref_genome"));
	M("genesis::population").def("guess_and_set_ref_and_alt_bases", (void (*)(struct genesis::population::Variant &, const class genesis::sequence::ReferenceGenome &, bool)) &genesis::population::guess_and_set_ref_and_alt_bases, "Guess the reference and alternative bases for a Variant, and set them,\n using a ReferenceGenome to get the reference base where possible.\n\n This uses the same approach as guess_and_set_ref_and_alt_bases( Variant&, bool ), but\n additionally consideres the given  If the reference genome contains a value\n in `ACGT` (case insensitive) at the position of the  it is used as the reference.\n Note that the function throws an exception should the reference base already be set to a different\n value, in order to notify users that something is off.\n\n If the reference genome is `N` though, the function behaves the same as its reference-free\n alternative. For the alternative base, it always uses the most abundant base that is not the\n reference, same as its alternative function.\n\nC++: genesis::population::guess_and_set_ref_and_alt_bases(struct genesis::population::Variant &, const class genesis::sequence::ReferenceGenome &, bool) --> void", pybind11::arg("variant"), pybind11::arg("ref_genome"), pybind11::arg("force"));

}
