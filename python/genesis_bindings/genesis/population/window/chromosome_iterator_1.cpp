#include <genesis/population/base_counts.hpp>
#include <genesis/population/formats/variant_input_iterator.hpp>
#include <genesis/population/functions/functions.hpp>
#include <genesis/population/variant.hpp>
#include <genesis/population/window/chromosome_iterator.hpp>
#include <genesis/sequence/sequence_dict.hpp>
#include <genesis/utils/containers/lambda_iterator.hpp>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>

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

void bind_genesis_population_window_chromosome_iterator_1(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// genesis::population::make_chromosome_iterator(class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator) file:genesis/population/window/chromosome_iterator.hpp line:542
	M("genesis::population").def("make_chromosome_iterator", (class genesis::population::ChromosomeIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant> (*)(class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator)) &genesis::population::make_chromosome_iterator<genesis::utils::LambdaIterator<genesis::population::Variant, genesis::population::VariantInputIteratorData>::Iterator,genesis::population::Variant>, "C++: genesis::population::make_chromosome_iterator(class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator) --> class genesis::population::ChromosomeIterator<class genesis::utils::LambdaIterator<struct genesis::population::Variant, struct genesis::population::VariantInputIteratorData>::Iterator, struct genesis::population::Variant>", pybind11::arg("begin"), pybind11::arg("end"));

	// genesis::population::is_valid_base(char) file:genesis/population/functions/functions.hpp line:55
	M("genesis::population").def("is_valid_base", (bool (*)(char)) &genesis::population::is_valid_base, "Return whether a given base is in `ACGT`, case insensitive.\n\nC++: genesis::population::is_valid_base(char) --> bool", pybind11::arg("c"));

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

	// genesis::population::allele_count(const struct genesis::population::BaseCounts &) file:genesis/population/functions/functions.hpp line:140
	M("genesis::population").def("allele_count", (unsigned long (*)(const struct genesis::population::BaseCounts &)) &genesis::population::allele_count, "Return the number of alleles, that is, of non-zero nucleotide counts of the \n\n This looks at all four nucleotide counts (`ACGT`), and returns the number of them that are\n non zero. The result hence is between 0 and 4, with 0 = no allele had any counts and 4 = all\n alleles have a non-zero count.\n\nC++: genesis::population::allele_count(const struct genesis::population::BaseCounts &) --> unsigned long", pybind11::arg("sample"));

	// genesis::population::allele_count(const struct genesis::population::BaseCounts &, unsigned long) file:genesis/population/functions/functions.hpp line:150
	M("genesis::population").def("allele_count", (unsigned long (*)(const struct genesis::population::BaseCounts &, unsigned long)) &genesis::population::allele_count, "Return the number of alleles, taking a  into consideration, that is,\n we compute the number of nucleotide counts of the  that are at least the \n\n This looks at all four nucleotide counts (`ACGT`), and returns the number of them that are\n at least the  If `min_count == 0`, we instead call the allele_count(BaseCounts const&)\n overload of this function that does not consider minimum counts.\n\nC++: genesis::population::allele_count(const struct genesis::population::BaseCounts &, unsigned long) --> unsigned long", pybind11::arg("sample"), pybind11::arg("min_count"));

	// genesis::population::allele_count(const struct genesis::population::BaseCounts &, unsigned long, unsigned long) file:genesis/population/functions/functions.hpp line:161
	M("genesis::population").def("allele_count", (unsigned long (*)(const struct genesis::population::BaseCounts &, unsigned long, unsigned long)) &genesis::population::allele_count, "Return the number of alleles, taking a  and  into consideration,\n that is, we compute the number of nucleotide counts of the  that are at least\n  and at most \n\n This looks at all four nucleotide counts (`ACGT`), and returns the number of them that are\n at least the  and at most  If either of them is zero, they are not\n taken into account though.\n\nC++: genesis::population::allele_count(const struct genesis::population::BaseCounts &, unsigned long, unsigned long) --> unsigned long", pybind11::arg("sample"), pybind11::arg("min_count"), pybind11::arg("max_count"));

	// genesis::population::merge_inplace(struct genesis::population::BaseCounts &, const struct genesis::population::BaseCounts &) file:genesis/population/functions/functions.hpp line:167
	M("genesis::population").def("merge_inplace", (void (*)(struct genesis::population::BaseCounts &, const struct genesis::population::BaseCounts &)) &genesis::population::merge_inplace, "Merge the counts of two BaseCounts%s, by adding the counts of the second (\n to the first (\n \n\nC++: genesis::population::merge_inplace(struct genesis::population::BaseCounts &, const struct genesis::population::BaseCounts &) --> void", pybind11::arg("p1"), pybind11::arg("p2"));

	// genesis::population::merge(const struct genesis::population::BaseCounts &, const struct genesis::population::BaseCounts &) file:genesis/population/functions/functions.hpp line:172
	M("genesis::population").def("merge", (struct genesis::population::BaseCounts (*)(const struct genesis::population::BaseCounts &, const struct genesis::population::BaseCounts &)) &genesis::population::merge, "Merge the counts of two BaseCounts%s.\n\nC++: genesis::population::merge(const struct genesis::population::BaseCounts &, const struct genesis::population::BaseCounts &) --> struct genesis::population::BaseCounts", pybind11::arg("p1"), pybind11::arg("p2"));

	// genesis::population::merge(const class std::vector<struct genesis::population::BaseCounts, class std::allocator<struct genesis::population::BaseCounts> > &) file:genesis/population/functions/functions.hpp line:177
	M("genesis::population").def("merge", (struct genesis::population::BaseCounts (*)(const class std::vector<struct genesis::population::BaseCounts, class std::allocator<struct genesis::population::BaseCounts> > &)) &genesis::population::merge, "Merge the counts of a vector BaseCounts%s.\n\nC++: genesis::population::merge(const class std::vector<struct genesis::population::BaseCounts, class std::allocator<struct genesis::population::BaseCounts> > &) --> struct genesis::population::BaseCounts", pybind11::arg("p"));

	// genesis::population::merge_base_counts(const struct genesis::population::Variant &) file:genesis/population/functions/functions.hpp line:182
	M("genesis::population").def("merge_base_counts", (struct genesis::population::BaseCounts (*)(const struct genesis::population::Variant &)) &genesis::population::merge_base_counts, "Merge the counts of a vector BaseCounts%s.\n\nC++: genesis::population::merge_base_counts(const struct genesis::population::Variant &) --> struct genesis::population::BaseCounts", pybind11::arg("v"));

	// genesis::population::nucleotide_sum(const struct genesis::population::BaseCounts &) file:genesis/population/functions/functions.hpp line:196
	M("genesis::population").def("nucleotide_sum", (unsigned long (*)(const struct genesis::population::BaseCounts &)) &genesis::population::nucleotide_sum, "Count of the pure nucleotide bases at this position, that is,\n the sum of all `A`, `C`, `G`, and `T`.\n\n This is simply the sum of `a_count + c_count + g_count + t_count`, which we often use as the\n coverage at the given site.\n\n NB: In PoPoolation, this variable is called `eucov`.\n\nC++: genesis::population::nucleotide_sum(const struct genesis::population::BaseCounts &) --> unsigned long", pybind11::arg("sample"));

	// genesis::population::total_nucleotide_sum(const struct genesis::population::Variant &) file:genesis/population/functions/functions.hpp line:206
	M("genesis::population").def("total_nucleotide_sum", (unsigned long (*)(const struct genesis::population::Variant &)) &genesis::population::total_nucleotide_sum, "nucleotide_sum( BaseCounts const& )\n\n See nucleotide_sum() for details. This function gives the sum over all samples in the Variant.\n\nC++: genesis::population::total_nucleotide_sum(const struct genesis::population::Variant &) --> unsigned long", pybind11::arg("variant"));

	// genesis::population::consensus(const struct genesis::population::BaseCounts &) file:genesis/population/functions/functions.hpp line:224
	M("genesis::population").def("consensus", (struct std::pair<char, double> (*)(const struct genesis::population::BaseCounts &)) &genesis::population::consensus, "Consensus character for a BaseCounts, and its confidence.\n\n This is simply the character (out of `ACGT`) that appears most often (or, for ties,\n the lexicographically smallest character), unless all of (`A`, `C`, `G`, `T`) are zero,\n in which case the consensus character is `N`.\n The confidence is the count of the consensus character, divided by the total count\n of all four nucleotides.\n\nC++: genesis::population::consensus(const struct genesis::population::BaseCounts &) --> struct std::pair<char, double>", pybind11::arg("sample"));

	// genesis::population::consensus(const struct genesis::population::BaseCounts &, bool) file:genesis/population/functions/functions.hpp line:235
	M("genesis::population").def("consensus", (struct std::pair<char, double> (*)(const struct genesis::population::BaseCounts &, bool)) &genesis::population::consensus, "Consensus character for a BaseCounts, and its confidence.\n\n This is simply the character (out of `ACGT`) that appears most often (or, for ties,\n the lexicographically smallest character). If  is false (meaning, the position is\n not well covered by reads), the consensus character is `N`.\n The confidence is the count of the consensus character, divided by the total count\n of all four nucleotides.\n\nC++: genesis::population::consensus(const struct genesis::population::BaseCounts &, bool) --> struct std::pair<char, double>", pybind11::arg("sample"), pybind11::arg("is_covered"));

	// genesis::population::guess_reference_base(const struct genesis::population::Variant &, bool) file:genesis/population/functions/functions.hpp line:246
	M("genesis::population").def("guess_reference_base", [](const struct genesis::population::Variant & a0) -> char { return genesis::population::guess_reference_base(a0); }, "", pybind11::arg("variant"));
	M("genesis::population").def("guess_reference_base", (char (*)(const struct genesis::population::Variant &, bool)) &genesis::population::guess_reference_base, "Guess the reference base of a Variant.\n\n If the Variant already has a `reference_base` in `ACGT`, this base is returned (meaning that\n this function is idempotent; it does not change the reference base if there already is one).\n However, if the `reference_base` is `N` or any other value not in `ACGT`, or if  is `true`,\n the base with the highest count is returned instead,\n unless all counts are 0, in which case the returned reference base is `N`.\n\nC++: genesis::population::guess_reference_base(const struct genesis::population::Variant &, bool) --> char", pybind11::arg("variant"), pybind11::arg("force"));

	// genesis::population::guess_alternative_base(const struct genesis::population::Variant &, bool) file:genesis/population/functions/functions.hpp line:261
	M("genesis::population").def("guess_alternative_base", [](const struct genesis::population::Variant & a0) -> char { return genesis::population::guess_alternative_base(a0); }, "", pybind11::arg("variant"));
	M("genesis::population").def("guess_alternative_base", (char (*)(const struct genesis::population::Variant &, bool)) &genesis::population::guess_alternative_base, "Guess the alternative base of a Variant.\n\n If the Variant already has an `alternative_base` in `ACGT` and  is not `true`,\n this original base is returned (meaning that this function is idempotent; it does not change\n the alternative base if there already is one).\n However, if the `alternative_base` is `N` or any other char not in `ACGT`, or if  is `true`,\n the base with the highest count that is not the reference base is returned instead.\n This also means that the reference base has to be set to a value in `ACGT`,\n as otherwise the concept of an alternative base is meaningless anyway.\n If the reference base is not one of `ACGT`, the returned alternative base is `N`.\n Furthermore, if all three non-reference bases have count 0, the returned alternative base is `N`.\n\nC++: genesis::population::guess_alternative_base(const struct genesis::population::Variant &, bool) --> char", pybind11::arg("variant"), pybind11::arg("force"));

}
