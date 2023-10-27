#include <genesis/utils/math/statistics.hpp>
#include <iterator>
#include <memory>
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

void bind_genesis_utils_math_statistics_1(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// genesis::utils::weighted_harmonic_mean(const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &, enum genesis::utils::HarmonicMeanZeroPolicy) file:genesis/utils/math/statistics.hpp line:988
	M("genesis::utils").def("weighted_harmonic_mean", [](const class std::vector<double, class std::allocator<double> > & a0, const class std::vector<double, class std::allocator<double> > & a1) -> double { return genesis::utils::weighted_harmonic_mean(a0, a1); }, "", pybind11::arg("values"), pybind11::arg("weights"));
	M("genesis::utils").def("weighted_harmonic_mean", (double (*)(const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &, enum genesis::utils::HarmonicMeanZeroPolicy)) &genesis::utils::weighted_harmonic_mean, "Calculate the weighted harmonic mean of a `std::vector` of `double` elements.\n\n \n weighted_harmonic_mean( ForwardIterator first, ForwardIterator last ) for details.\n \n\n harmonic_mean() for the unweighted version.\n \n\n arithmetic_mean() for a function that calculates the arithmetic mean, and\n \n\n geometric_mean() for a function that calculates the geometric mean.\n \n\n weighted_arithmetic_mean() for a function that calculates the weighted arithmetic mean, and\n \n\n weighted_geometric_mean() for a function that calculates the weighted geometric mean.\n\nC++: genesis::utils::weighted_harmonic_mean(const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &, enum genesis::utils::HarmonicMeanZeroPolicy) --> double", pybind11::arg("values"), pybind11::arg("weights"), pybind11::arg("zero_policy"));

	// genesis::utils::median(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) file:genesis/utils/math/statistics.hpp line:1014
	M("genesis::utils").def("median", (double (*)(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >)) &genesis::utils::median<__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >>, "C++: genesis::utils::median(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) --> double", pybind11::arg("first"), pybind11::arg("last"));

	// genesis::utils::median(const class std::vector<double, class std::allocator<double> > &) file:genesis/utils/math/statistics.hpp line:1050
	M("genesis::utils").def("median", (double (*)(const class std::vector<double, class std::allocator<double> > &)) &genesis::utils::median, "Calculate the median value of a `vector` of `double`.\n\n The vector has to be sorted.\n\nC++: genesis::utils::median(const class std::vector<double, class std::allocator<double> > &) --> double", pybind11::arg("vec"));

	// genesis::utils::quartiles(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) file:genesis/utils/math/statistics.hpp line:1066
	M("genesis::utils").def("quartiles", (struct genesis::utils::Quartiles (*)(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >)) &genesis::utils::quartiles<__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >>, "C++: genesis::utils::quartiles(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) --> struct genesis::utils::Quartiles", pybind11::arg("first"), pybind11::arg("last"));

	// genesis::utils::quartiles(const class std::vector<double, class std::allocator<double> > &) file:genesis/utils/math/statistics.hpp line:1108
	M("genesis::utils").def("quartiles", (struct genesis::utils::Quartiles (*)(const class std::vector<double, class std::allocator<double> > &)) &genesis::utils::quartiles, "Calculate the Quartiles of a `vector` of `double`.\n\n The vector has to be sorted.\n\nC++: genesis::utils::quartiles(const class std::vector<double, class std::allocator<double> > &) --> struct genesis::utils::Quartiles", pybind11::arg("vec"));

	// genesis::utils::coefficient_of_variation(const struct genesis::utils::MeanStddevPair &) file:genesis/utils/math/statistics.hpp line:1125
	M("genesis::utils").def("coefficient_of_variation", (double (*)(const struct genesis::utils::MeanStddevPair &)) &genesis::utils::coefficient_of_variation, "Calculate the index of dispersion.\n\n The coefficient of variation (CV), also known as the relative standard deviation (RSD),\n is defined as the ratio of the standard deviation to the mean.\n See mean_stddev() to calculate those values.\n See https://en.wikipedia.org/wiki/Coefficient_of_variation for details.\n\nC++: genesis::utils::coefficient_of_variation(const struct genesis::utils::MeanStddevPair &) --> double", pybind11::arg("ms"));

	// genesis::utils::coefficient_of_variation(const class std::vector<struct genesis::utils::MeanStddevPair, class std::allocator<struct genesis::utils::MeanStddevPair> > &) file:genesis/utils/math/statistics.hpp line:1133
	M("genesis::utils").def("coefficient_of_variation", (class std::vector<double, class std::allocator<double> > (*)(const class std::vector<struct genesis::utils::MeanStddevPair, class std::allocator<struct genesis::utils::MeanStddevPair> > &)) &genesis::utils::coefficient_of_variation, "coefficient_of_variation( MeanStddevPair const& ms )\n\nC++: genesis::utils::coefficient_of_variation(const class std::vector<struct genesis::utils::MeanStddevPair, class std::allocator<struct genesis::utils::MeanStddevPair> > &) --> class std::vector<double, class std::allocator<double> >", pybind11::arg("ms"));

	// genesis::utils::index_of_dispersion(const struct genesis::utils::MeanStddevPair &) file:genesis/utils/math/statistics.hpp line:1151
	M("genesis::utils").def("index_of_dispersion", (double (*)(const struct genesis::utils::MeanStddevPair &)) &genesis::utils::index_of_dispersion, "Calculate the index of dispersion.\n\n The index of dispersion, also known as the dispersion index, coefficient of dispersion,\n relative variance, variance-to-mean ratio (VMR) or Fano factor, is defined as the ratio of the\n variance to the mean. Variance is the square of the standard deviation.\n See mean_stddev() to calculate those values.\n See https://en.wikipedia.org/wiki/Index_of_dispersion for details.\n\nC++: genesis::utils::index_of_dispersion(const struct genesis::utils::MeanStddevPair &) --> double", pybind11::arg("ms"));

	// genesis::utils::index_of_dispersion(const class std::vector<struct genesis::utils::MeanStddevPair, class std::allocator<struct genesis::utils::MeanStddevPair> > &) file:genesis/utils/math/statistics.hpp line:1159
	M("genesis::utils").def("index_of_dispersion", (class std::vector<double, class std::allocator<double> > (*)(const class std::vector<struct genesis::utils::MeanStddevPair, class std::allocator<struct genesis::utils::MeanStddevPair> > &)) &genesis::utils::index_of_dispersion, "index_of_dispersion( MeanStddevPair const& ms )\n\nC++: genesis::utils::index_of_dispersion(const class std::vector<struct genesis::utils::MeanStddevPair, class std::allocator<struct genesis::utils::MeanStddevPair> > &) --> class std::vector<double, class std::allocator<double> >", pybind11::arg("ms"));

	// genesis::utils::quartile_coefficient_of_dispersion(const struct genesis::utils::Quartiles &) file:genesis/utils/math/statistics.hpp line:1175
	M("genesis::utils").def("quartile_coefficient_of_dispersion", (double (*)(const struct genesis::utils::Quartiles &)) &genesis::utils::quartile_coefficient_of_dispersion, "Calculate the quartile_coefficient_of_dispersion.\n\n The quartile coefficient of dispersion is defined as `( Q3 - Q1 ) / ( Q3 + Q1 )`.\n See quartiles() to caculate those values.\n See https://en.wikipedia.org/wiki/Quartile_coefficient_of_dispersion for details.\n\nC++: genesis::utils::quartile_coefficient_of_dispersion(const struct genesis::utils::Quartiles &) --> double", pybind11::arg("q"));

	// genesis::utils::quartile_coefficient_of_dispersion(const class std::vector<struct genesis::utils::Quartiles, class std::allocator<struct genesis::utils::Quartiles> > &) file:genesis/utils/math/statistics.hpp line:1183
	M("genesis::utils").def("quartile_coefficient_of_dispersion", (class std::vector<double, class std::allocator<double> > (*)(const class std::vector<struct genesis::utils::Quartiles, class std::allocator<struct genesis::utils::Quartiles> > &)) &genesis::utils::quartile_coefficient_of_dispersion, "quartile_coefficient_of_dispersion( Quartiles const& ms )\n\nC++: genesis::utils::quartile_coefficient_of_dispersion(const class std::vector<struct genesis::utils::Quartiles, class std::allocator<struct genesis::utils::Quartiles> > &) --> class std::vector<double, class std::allocator<double> >", pybind11::arg("q"));

	// genesis::utils::pearson_correlation_coefficient(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) file:genesis/utils/math/statistics.hpp line:1209
	M("genesis::utils").def("pearson_correlation_coefficient", (double (*)(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >)) &genesis::utils::pearson_correlation_coefficient<__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >,__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >>, "C++: genesis::utils::pearson_correlation_coefficient(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) --> double", pybind11::arg("first_a"), pybind11::arg("last_a"), pybind11::arg("first_b"), pybind11::arg("last_b"));

	// genesis::utils::pearson_correlation_coefficient(const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &) file:genesis/utils/math/statistics.hpp line:1261
	M("genesis::utils").def("pearson_correlation_coefficient", (double (*)(const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &)) &genesis::utils::pearson_correlation_coefficient, "Calculate the Pearson Correlation Coefficient between the entries of two vectors.\n\n  pearson_correlation_coefficient( ForwardIteratorA first_a, ForwardIteratorA last_a, ForwardIteratorB first_b, ForwardIteratorB last_b ).\n\nC++: genesis::utils::pearson_correlation_coefficient(const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &) --> double", pybind11::arg("vec_a"), pybind11::arg("vec_b"));

	// genesis::utils::spearmans_rank_correlation_coefficient(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) file:genesis/utils/math/statistics.hpp line:1279
	M("genesis::utils").def("spearmans_rank_correlation_coefficient", (double (*)(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >)) &genesis::utils::spearmans_rank_correlation_coefficient<__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >,__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >>, "C++: genesis::utils::spearmans_rank_correlation_coefficient(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) --> double", pybind11::arg("first_a"), pybind11::arg("last_a"), pybind11::arg("first_b"), pybind11::arg("last_b"));

	// genesis::utils::spearmans_rank_correlation_coefficient(const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &) file:genesis/utils/math/statistics.hpp line:1300
	M("genesis::utils").def("spearmans_rank_correlation_coefficient", (double (*)(const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &)) &genesis::utils::spearmans_rank_correlation_coefficient, "Calculate Spearman's Rank Correlation Coefficient between the entries of two vectors.\n\n  spearmans_rank_correlation_coefficient( RandomAccessIteratorA first_a, RandomAccessIteratorA last_a, RandomAccessIteratorB first_b, RandomAccessIteratorB last_b )\n\nC++: genesis::utils::spearmans_rank_correlation_coefficient(const class std::vector<double, class std::allocator<double> > &, const class std::vector<double, class std::allocator<double> > &) --> double", pybind11::arg("vec_a"), pybind11::arg("vec_b"));

	// genesis::utils::fisher_transformation(double) file:genesis/utils/math/statistics.hpp line:1317
	M("genesis::utils").def("fisher_transformation", (double (*)(double)) &genesis::utils::fisher_transformation, "Apply Fisher z-transformation to a correlation coefficient.\n\n The coefficient can be calculated with pearson_correlation_coefficient() or\n spearmans_rank_correlation_coefficient() and has to be in range `[ -1.0, 1.0 ]`.\n\n There is also a version of this function for a vector of coefficients.\n\nC++: genesis::utils::fisher_transformation(double) --> double", pybind11::arg("correlation_coefficient"));

	// genesis::utils::fisher_transformation(const class std::vector<double, class std::allocator<double> > &) file:genesis/utils/math/statistics.hpp line:1337
	M("genesis::utils").def("fisher_transformation", (class std::vector<double, class std::allocator<double> > (*)(const class std::vector<double, class std::allocator<double> > &)) &genesis::utils::fisher_transformation, "Apply Fisher z-transformation to a vector of correlation coefficients.\n\n See fisher_transformation( double ) for details.\n\nC++: genesis::utils::fisher_transformation(const class std::vector<double, class std::allocator<double> > &) --> class std::vector<double, class std::allocator<double> >", pybind11::arg("correlation_coefficients"));

}
