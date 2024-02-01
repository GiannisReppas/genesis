#include <genesis/utils/math/statistics.hpp>
#include <iterator>
#include <memory>
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

void bind_genesis_utils_math_statistics(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// genesis::utils::closure(class std::vector<double, class std::allocator<double> > &) file:genesis/utils/math/statistics.hpp line:330
	M("genesis::utils").def("closure", (void (*)(class std::vector<double, class std::allocator<double> > &)) &genesis::utils::closure, "Calculate the closure of a `std::vector` of `double` elements.\n\n \n closure( ForwardIterator first, ForwardIterator last ) for details.\n\nC++: genesis::utils::closure(class std::vector<double, class std::allocator<double> > &) --> void", pybind11::arg("vec"));

	// genesis::utils::mean_stddev(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, double) file:genesis/utils/math/statistics.hpp line:358
	M("genesis::utils").def("mean_stddev", [](class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > > const & a0, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > > const & a1) -> genesis::utils::MeanStddevPair { return genesis::utils::mean_stddev(a0, a1); }, "", pybind11::arg("first"), pybind11::arg("last"));
	M("genesis::utils").def("mean_stddev", (struct genesis::utils::MeanStddevPair (*)(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, double)) &genesis::utils::mean_stddev<__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >>, "C++: genesis::utils::mean_stddev(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, double) --> struct genesis::utils::MeanStddevPair", pybind11::arg("first"), pybind11::arg("last"), pybind11::arg("epsilon"));

	// genesis::utils::mean_stddev(const class std::vector<double, class std::allocator<double> > &, double) file:genesis/utils/math/statistics.hpp line:413
	M("genesis::utils").def("mean_stddev", [](const class std::vector<double, class std::allocator<double> > & a0) -> genesis::utils::MeanStddevPair { return genesis::utils::mean_stddev(a0); }, "", pybind11::arg("vec"));
	M("genesis::utils").def("mean_stddev", (struct genesis::utils::MeanStddevPair (*)(const class std::vector<double, class std::allocator<double> > &, double)) &genesis::utils::mean_stddev, "Calculate the mean and standard deviation of a `std::vector` of `double` elements.\n\n \n mean_stddev( ForwardIterator first, ForwardIterator last, double epsilon ) for details.\n \n\n arithmetic_mean() for a function that only calculates the mean, and thus saves the effort\n of a second iteration over the range.\n\nC++: genesis::utils::mean_stddev(const class std::vector<double, class std::allocator<double> > &, double) --> struct genesis::utils::MeanStddevPair", pybind11::arg("vec"), pybind11::arg("epsilon"));

	// genesis::utils::arithmetic_mean(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) file:genesis/utils/math/statistics.hpp line:438
	M("genesis::utils").def("arithmetic_mean", (double (*)(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >)) &genesis::utils::arithmetic_mean<__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >>, "C++: genesis::utils::arithmetic_mean(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) --> double", pybind11::arg("first"), pybind11::arg("last"));

	// genesis::utils::arithmetic_mean(const class std::vector<double, class std::allocator<double> > &) file:genesis/utils/math/statistics.hpp line:473
	M("genesis::utils").def("arithmetic_mean", (double (*)(const class std::vector<double, class std::allocator<double> > &)) &genesis::utils::arithmetic_mean, "Calculate the arithmetic mean of a `std::vector` of `double` elements.\n\n \n arithmetic_mean( ForwardIterator first, ForwardIterator last ) for details.\n \n\n mean_stddev() for a function that simultaneously calculates the standard deviation.\n \n\n geometric_mean() for a function that calculates the geometric mean, and\n \n\n harmonic_mean() for a function that calculates the harmonic mean.\n\nC++: genesis::utils::arithmetic_mean(const class std::vector<double, class std::allocator<double> > &) --> double", pybind11::arg("vec"));

	// genesis::utils::weighted_arithmetic_mean(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) file:genesis/utils/math/statistics.hpp line:496
	M("genesis::utils").def("weighted_arithmetic_mean", (double (*)(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >)) &genesis::utils::weighted_arithmetic_mean<__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >>, "C++: genesis::utils::weighted_arithmetic_mean(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) --> double", pybind11::arg("first_value"), pybind11::arg("last_value"), pybind11::arg("first_weight"), pybind11::arg("last_weight"));

	// genesis::utils::weighted_arithmetic_mean(const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &) file:genesis/utils/math/statistics.hpp line:547
	M("genesis::utils").def("weighted_arithmetic_mean", (double (*)(const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &)) &genesis::utils::weighted_arithmetic_mean, "Calculate the weighted arithmetic mean of a `std::vector` of `double` elements.\n\n \n weighted_arithmetic_mean( ForwardIterator first, ForwardIterator last ) for details.\n \n\n arithmetic_mean() for the unweighted version.\n \n\n geometric_mean() for a function that calculates the geometric mean, and\n \n\n harmonic_mean() for a function that calculates the harmonic mean.\n \n\n weighted_geometric_mean() for a function that calculates the weighted geometric mean, and\n \n\n weighted_harmonic_mean() for a function that calculates the weighted harmonic mean.\n\nC++: genesis::utils::weighted_arithmetic_mean(const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &) --> double", pybind11::arg("values"), pybind11::arg("weights"));

	// genesis::utils::geometric_mean(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) file:genesis/utils/math/statistics.hpp line:574
	M("genesis::utils").def("geometric_mean", (double (*)(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >)) &genesis::utils::geometric_mean<__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >>, "C++: genesis::utils::geometric_mean(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) --> double", pybind11::arg("first"), pybind11::arg("last"));

	// genesis::utils::geometric_mean(const class std::vector<double, class std::allocator<double> > &) file:genesis/utils/math/statistics.hpp line:613
	M("genesis::utils").def("geometric_mean", (double (*)(const class std::vector<double, class std::allocator<double> > &)) &genesis::utils::geometric_mean, "Calculate the geometric mean of a `std::vector` of `double` elements.\n\n \n geometric_mean( ForwardIterator first, ForwardIterator last ) for details.\n \n\n arithmetic_mean() for a function that calculates the arithmetic mean, and\n \n\n harmonic_mean() for a function that calculates the harmonic mean.\n\nC++: genesis::utils::geometric_mean(const class std::vector<double, class std::allocator<double> > &) --> double", pybind11::arg("vec"));

	// genesis::utils::weighted_geometric_mean(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) file:genesis/utils/math/statistics.hpp line:649
	M("genesis::utils").def("weighted_geometric_mean", (double (*)(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >)) &genesis::utils::weighted_geometric_mean<__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >>, "C++: genesis::utils::weighted_geometric_mean(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) --> double", pybind11::arg("first_value"), pybind11::arg("last_value"), pybind11::arg("first_weight"), pybind11::arg("last_weight"));

	// genesis::utils::weighted_geometric_mean(const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &) file:genesis/utils/math/statistics.hpp line:706
	M("genesis::utils").def("weighted_geometric_mean", (double (*)(const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &)) &genesis::utils::weighted_geometric_mean, "Calculate the weighted geometric mean of a `std::vector` of `double` elements.\n\n \n weighted_geometric_mean( ForwardIterator first, ForwardIterator last ) for details.\n \n\n geometric_mean() for the unweighted version.\n \n\n arithmetic_mean() for a function that calculates the arithmetic mean, and\n \n\n harmonic_mean() for a function that calculates the harmonic mean.\n \n\n weighted_arithmetic_mean() for a function that calculates the weighted arithmetic mean, and\n \n\n weighted_harmonic_mean() for a function that calculates the weighted harmonic mean.\n\nC++: genesis::utils::weighted_geometric_mean(const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &) --> double", pybind11::arg("values"), pybind11::arg("weights"));

	// genesis::utils::HarmonicMeanZeroPolicy file:genesis/utils/math/statistics.hpp line:721
	pybind11::enum_<genesis::utils::HarmonicMeanZeroPolicy>(M("genesis::utils"), "HarmonicMeanZeroPolicy", "Select a policy on how to treat zeroes in the computation of harmonic_mean()\n and weighted_harmonic_mean().")
		.value("kThrow", genesis::utils::HarmonicMeanZeroPolicy::kThrow)
		.value("kIgnore", genesis::utils::HarmonicMeanZeroPolicy::kIgnore)
		.value("kReturnZero", genesis::utils::HarmonicMeanZeroPolicy::kReturnZero)
		.value("kCorrection", genesis::utils::HarmonicMeanZeroPolicy::kCorrection);

;

	// genesis::utils::harmonic_mean(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, enum genesis::utils::HarmonicMeanZeroPolicy) file:genesis/utils/math/statistics.hpp line:775
	M("genesis::utils").def("harmonic_mean", [](class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > > const & a0, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > > const & a1) -> double { return genesis::utils::harmonic_mean(a0, a1); }, "", pybind11::arg("first"), pybind11::arg("last"));
	M("genesis::utils").def("harmonic_mean", (double (*)(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, enum genesis::utils::HarmonicMeanZeroPolicy)) &genesis::utils::harmonic_mean<__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >>, "C++: genesis::utils::harmonic_mean(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, enum genesis::utils::HarmonicMeanZeroPolicy) --> double", pybind11::arg("first"), pybind11::arg("last"), pybind11::arg("zero_policy"));

	// genesis::utils::harmonic_mean(const class std::vector<double, class std::allocator<double> > &, enum genesis::utils::HarmonicMeanZeroPolicy) file:genesis/utils/math/statistics.hpp line:849
	M("genesis::utils").def("harmonic_mean", [](const class std::vector<double, class std::allocator<double> > & a0) -> double { return genesis::utils::harmonic_mean(a0); }, "", pybind11::arg("vec"));
	M("genesis::utils").def("harmonic_mean", (double (*)(const class std::vector<double, class std::allocator<double> > &, enum genesis::utils::HarmonicMeanZeroPolicy)) &genesis::utils::harmonic_mean, "Calculate the harmonic mean of a `std::vector` of `double` elements.\n\n \n harmonic_mean( ForwardIterator first, ForwardIterator last ) for details.\n \n\n arithmetic_mean() for a function that calculates the arithmetic mean, and\n \n\n geometric_mean() for a function that calculates the geometric mean.\n\nC++: genesis::utils::harmonic_mean(const class std::vector<double, class std::allocator<double> > &, enum genesis::utils::HarmonicMeanZeroPolicy) --> double", pybind11::arg("vec"), pybind11::arg("zero_policy"));

	// genesis::utils::weighted_harmonic_mean(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, enum genesis::utils::HarmonicMeanZeroPolicy) file:genesis/utils/math/statistics.hpp line:884
	M("genesis::utils").def("weighted_harmonic_mean", [](class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > > const & a0, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > > const & a1, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > > const & a2, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > > const & a3) -> double { return genesis::utils::weighted_harmonic_mean(a0, a1, a2, a3); }, "", pybind11::arg("first_value"), pybind11::arg("last_value"), pybind11::arg("first_weight"), pybind11::arg("last_weight"));
	M("genesis::utils").def("weighted_harmonic_mean", (double (*)(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, enum genesis::utils::HarmonicMeanZeroPolicy)) &genesis::utils::weighted_harmonic_mean<__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >>, "C++: genesis::utils::weighted_harmonic_mean(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, enum genesis::utils::HarmonicMeanZeroPolicy) --> double", pybind11::arg("first_value"), pybind11::arg("last_value"), pybind11::arg("first_weight"), pybind11::arg("last_weight"), pybind11::arg("zero_policy"));

}
