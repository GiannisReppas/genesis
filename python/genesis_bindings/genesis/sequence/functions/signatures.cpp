#include <genesis/sequence/functions/signature_specifications.hpp>
#include <genesis/sequence/functions/signatures.hpp>
#include <genesis/sequence/sequence.hpp>
#include <ios>
#include <iterator>
#include <locale>
#include <memory>
#include <ostream>
#include <streambuf>
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

void bind_genesis_sequence_functions_signatures(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// genesis::sequence::signature_counts(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) file:genesis/sequence/functions/signatures.hpp line:59
	M("genesis::sequence").def("signature_counts", (class std::vector<unsigned long, class std::allocator<unsigned long> > (*)(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &)) &genesis::sequence::signature_counts, "Count the occurences of k-mers in the  according to the \n\n The function returns a vector that contains the count for each k-mer that can be build from\n the characters in the alphabet, in the order given by SignatureSpecifications::kmer_list().\n\nC++: genesis::sequence::signature_counts(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) --> class std::vector<unsigned long, class std::allocator<unsigned long> >", pybind11::arg("sequence"), pybind11::arg("settings"));

	// genesis::sequence::signature_frequencies(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) file:genesis/sequence/functions/signatures.hpp line:70
	M("genesis::sequence").def("signature_frequencies", (class std::vector<double, class std::allocator<double> > (*)(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &)) &genesis::sequence::signature_frequencies, "Calculate the frequencies of occurences of k-mers in the  according to the\n \n\n The function simply calculates the frequencies as the normalized values of signature_counts().\n\nC++: genesis::sequence::signature_frequencies(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) --> class std::vector<double, class std::allocator<double> >", pybind11::arg("sequence"), pybind11::arg("settings"));

	// genesis::sequence::signature_symmetrized_counts(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) file:genesis/sequence/functions/signatures.hpp line:85
	M("genesis::sequence").def("signature_symmetrized_counts", (class std::vector<unsigned long, class std::allocator<unsigned long> > (*)(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &)) &genesis::sequence::signature_symmetrized_counts, "Calcuate the symmetrized counts of the  according to the \n\n The function uses signature_counts(), and sums up the counts of k-mers that are reverse\n complements of each other.\n\nC++: genesis::sequence::signature_symmetrized_counts(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) --> class std::vector<unsigned long, class std::allocator<unsigned long> >", pybind11::arg("sequence"), pybind11::arg("settings"));

	// genesis::sequence::signature_symmetrized_frequencies(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) file:genesis/sequence/functions/signatures.hpp line:96
	M("genesis::sequence").def("signature_symmetrized_frequencies", (class std::vector<double, class std::allocator<double> > (*)(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &)) &genesis::sequence::signature_symmetrized_frequencies, "Calcuate the symmetrized counts of the  according to the \n\n The function uses signature_frequencies(), and sums up the counts of k-mers that are reverse\n complements of each other.\n\nC++: genesis::sequence::signature_symmetrized_frequencies(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) --> class std::vector<double, class std::allocator<double> >", pybind11::arg("sequence"), pybind11::arg("settings"));

	// genesis::sequence::signature_ranks(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) file:genesis/sequence/functions/signatures.hpp line:111
	M("genesis::sequence").def("signature_ranks", (class std::vector<unsigned long, class std::allocator<unsigned long> > (*)(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &)) &genesis::sequence::signature_ranks, "Calcuate the rank signature of a  according to the \n\n That is, \n\n\n\nC++: genesis::sequence::signature_ranks(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) --> class std::vector<unsigned long, class std::allocator<unsigned long> >", pybind11::arg("sequence"), pybind11::arg("settings"));

	// genesis::sequence::signature_symmetrized_ranks(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) file:genesis/sequence/functions/signatures.hpp line:122
	M("genesis::sequence").def("signature_symmetrized_ranks", (class std::vector<unsigned long, class std::allocator<unsigned long> > (*)(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &)) &genesis::sequence::signature_symmetrized_ranks, "Calcuate the symmetrized rank signature of a  according to the \n\n That is, \n\n\n\nC++: genesis::sequence::signature_symmetrized_ranks(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) --> class std::vector<unsigned long, class std::allocator<unsigned long> >", pybind11::arg("sequence"), pybind11::arg("settings"));

	// genesis::sequence::signature_minimal_complementarity_frequencies(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) file:genesis/sequence/functions/signatures.hpp line:144
	M("genesis::sequence").def("signature_minimal_complementarity_frequencies", (class std::vector<double, class std::allocator<double> > (*)(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &)) &genesis::sequence::signature_minimal_complementarity_frequencies, "Calculate the signature of a  that uses the minimum frequency of reverse\n complement k-mers.\n\n The function is calculated according to\n\n > F. Gori, D. Mavroedis, M. S. M. Jetten, and E. Marchiori,\n > “Genomic signatures for metagenomic data analysis:\n > Exploiting the reverse complementarity of tetranucleotides,”\n > 2011 IEEE Int. Conf. Syst. Biol. ISB 2011, pp. 149–154, 2011.\n\n It excludes palindromic k-mers where the reverse complement is the k-mer itself.\n\nC++: genesis::sequence::signature_minimal_complementarity_frequencies(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) --> class std::vector<double, class std::allocator<double> >", pybind11::arg("sequence"), pybind11::arg("settings"));

	// genesis::sequence::signature_maximal_complementarity_frequencies(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) file:genesis/sequence/functions/signatures.hpp line:162
	M("genesis::sequence").def("signature_maximal_complementarity_frequencies", (class std::vector<double, class std::allocator<double> > (*)(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &)) &genesis::sequence::signature_maximal_complementarity_frequencies, "Calculate the signature of a  that uses the maximum frequency of reverse\n complement k-mers.\n\n The function is calculated according to\n\n > F. Gori, D. Mavroedis, M. S. M. Jetten, and E. Marchiori,\n > “Genomic signatures for metagenomic data analysis:\n > Exploiting the reverse complementarity of tetranucleotides,”\n > 2011 IEEE Int. Conf. Syst. Biol. ISB 2011, pp. 149–154, 2011.\n\n It excludes palindromic k-mers where the reverse complement is the k-mer itself.\n\nC++: genesis::sequence::signature_maximal_complementarity_frequencies(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) --> class std::vector<double, class std::allocator<double> >", pybind11::arg("sequence"), pybind11::arg("settings"));

	// genesis::sequence::signature_reverse_identity_frequencies(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) file:genesis/sequence/functions/signatures.hpp line:180
	M("genesis::sequence").def("signature_reverse_identity_frequencies", (class std::vector<double, class std::allocator<double> > (*)(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &)) &genesis::sequence::signature_reverse_identity_frequencies, "Calculate the signature of a  that uses only the frequencies of k-mers\n whose reverse complement is the k-mer itself.\n\n The function is calculated according to\n\n > F. Gori, D. Mavroedis, M. S. M. Jetten, and E. Marchiori,\n > “Genomic signatures for metagenomic data analysis:\n > Exploiting the reverse complementarity of tetranucleotides,”\n > 2011 IEEE Int. Conf. Syst. Biol. ISB 2011, pp. 149–154, 2011.\n\n It excludes k-mers where the reverse complement is a different k-mer.\n\nC++: genesis::sequence::signature_reverse_identity_frequencies(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) --> class std::vector<double, class std::allocator<double> >", pybind11::arg("sequence"), pybind11::arg("settings"));

	// genesis::sequence::signature_frequency_ratios_1(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) file:genesis/sequence/functions/signatures.hpp line:201
	M("genesis::sequence").def("signature_frequency_ratios_1", (class std::vector<double, class std::allocator<double> > (*)(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &)) &genesis::sequence::signature_frequency_ratios_1, "Calculate the ratio 1 signature of a \n\n The function is calculated according to\n\n > F. Gori, D. Mavroedis, M. S. M. Jetten, and E. Marchiori,\n > “Genomic signatures for metagenomic data analysis:\n > Exploiting the reverse complementarity of tetranucleotides,”\n > 2011 IEEE Int. Conf. Syst. Biol. ISB 2011, pp. 149–154, 2011.\n\n It excludes palindromic k-mers where the reverse complement is the k-mer itself.\n\nC++: genesis::sequence::signature_frequency_ratios_1(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) --> class std::vector<double, class std::allocator<double> >", pybind11::arg("sequence"), pybind11::arg("settings"));

	// genesis::sequence::signature_frequency_ratios_2(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) file:genesis/sequence/functions/signatures.hpp line:218
	M("genesis::sequence").def("signature_frequency_ratios_2", (class std::vector<double, class std::allocator<double> > (*)(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &)) &genesis::sequence::signature_frequency_ratios_2, "Calculate the ratio 2 signature of a \n\n The function is calculated according to\n\n > F. Gori, D. Mavroedis, M. S. M. Jetten, and E. Marchiori,\n > “Genomic signatures for metagenomic data analysis:\n > Exploiting the reverse complementarity of tetranucleotides,”\n > 2011 IEEE Int. Conf. Syst. Biol. ISB 2011, pp. 149–154, 2011.\n\n It excludes palindromic k-mers where the reverse complement is the k-mer itself.\n\nC++: genesis::sequence::signature_frequency_ratios_2(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) --> class std::vector<double, class std::allocator<double> >", pybind11::arg("sequence"), pybind11::arg("settings"));

	// genesis::sequence::signature_jensen_shannon(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) file:genesis/sequence/functions/signatures.hpp line:240
	M("genesis::sequence").def("signature_jensen_shannon", (class std::vector<double, class std::allocator<double> > (*)(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &)) &genesis::sequence::signature_jensen_shannon, "Calculate the Jensen-Shannon (JS) signature of a \n\n The function is calculated according to\n\n > F. Gori, D. Mavroedis, M. S. M. Jetten, and E. Marchiori,\n > “Genomic signatures for metagenomic data analysis:\n > Exploiting the reverse complementarity of tetranucleotides,”\n > 2011 IEEE Int. Conf. Syst. Biol. ISB 2011, pp. 149–154, 2011.\n\n using details of\n\n > J. Lin, “Divergence Measures Based on the Shannon Entropy,”\n > IEEE Trans. Inf. Theory, vol. 37, no. 1, pp. 145–151, 1991.\n\n It excludes palindromic k-mers where the reverse complement is the k-mer itself.\n\nC++: genesis::sequence::signature_jensen_shannon(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) --> class std::vector<double, class std::allocator<double> >", pybind11::arg("sequence"), pybind11::arg("settings"));

	// genesis::sequence::kmer_string_overlapping(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) file:genesis/sequence/functions/signatures.hpp line:266
	M("genesis::sequence").def("kmer_string_overlapping", (std::string (*)(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &)) &genesis::sequence::kmer_string_overlapping, "Return the  spitted into overlapping k-mers.\n\n The function takes the  and splits it into k-mers according to \n using a space char as delimiter between k-mers, with overlap.\n\n For example, the sequence `ACGTACGT` with `k == 3` becomes\n\n     ACG CGT GTA TAC ACG CGT\n\n The naming of the function follows\n\n > D. Kimothi, A. Soni, P. Biyani, and J. M. Hogan,\n > “Distributed Representations for Biological Sequence Analysis,” CoRR, vol. abs/1608.0, 2016.\n\n See there for details.\n\nC++: genesis::sequence::kmer_string_overlapping(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) --> std::string", pybind11::arg("sequence"), pybind11::arg("settings"));

	// genesis::sequence::kmer_string_overlapping(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &, std::ostream &) file:genesis/sequence/functions/signatures.hpp line:278
	M("genesis::sequence").def("kmer_string_overlapping", (void (*)(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &, std::ostream &)) &genesis::sequence::kmer_string_overlapping, "Print the  spitted into overlapping k-mers.\n\n This is identical to kmer_string_overlapping( Sequence const&, SignatureSpecifications const& ),\n but prints directly to a stream, which is better for processing large files.\n After the k-mer sequence, a new line character is printed.\n\nC++: genesis::sequence::kmer_string_overlapping(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &, std::ostream &) --> void", pybind11::arg("sequence"), pybind11::arg("settings"), pybind11::arg("out"));

	// genesis::sequence::kmer_strings_non_overlapping(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) file:genesis/sequence/functions/signatures.hpp line:303
	M("genesis::sequence").def("kmer_strings_non_overlapping", (class std::vector<std::string, class std::allocator<std::string > > (*)(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &)) &genesis::sequence::kmer_strings_non_overlapping, "Return the  spitted into a set of non-overlapping k-mers.\n\n The function takes the  and splits it into k-mers according to \n using a space char as delimiter between k-mers, without overlap.\n\n For example, the sequence `ACGTACGTACGT` with `k == 3` becomes\n\n     ACG TAC GTA CGT\n     CGT ACG TAC\n     GTA CGT ACG\n\n The naming of the function follows\n\n > D. Kimothi, A. Soni, P. Biyani, and J. M. Hogan,\n > “Distributed Representations for Biological Sequence Analysis,” CoRR, vol. abs/1608.0, 2016.\n\n See there for details.\n\nC++: genesis::sequence::kmer_strings_non_overlapping(const class genesis::sequence::Sequence &, const class genesis::sequence::SignatureSpecifications &) --> class std::vector<std::string, class std::allocator<std::string > >", pybind11::arg("sequence"), pybind11::arg("settings"));

}
