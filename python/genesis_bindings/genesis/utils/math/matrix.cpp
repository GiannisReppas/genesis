#include <genesis/population/genome_region_list.hpp>
#include <genesis/utils/containers/interval_tree/interval.hpp>
#include <genesis/utils/containers/matrix.hpp>
#include <genesis/utils/math/matrix.hpp>
#include <genesis/utils/math/statistics.hpp>
#include <iterator>
#include <memory>
#include <sstream> // __str__
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

void bind_genesis_utils_math_matrix(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// genesis::utils::normalize_cols(class genesis::utils::Matrix<double> &) file:genesis/utils/math/matrix.hpp line:262
	M("genesis::utils").def("normalize_cols", (class std::vector<struct genesis::utils::MinMaxPair<double>, class std::allocator<struct genesis::utils::MinMaxPair<double> > > (*)(class genesis::utils::Matrix<double> &)) &genesis::utils::normalize_cols, "Normalize the columns of a Matrix so that all values are in the range `[ 0.0, 1.0 ]`.\n\n The Matrix is manipulated inline. For each column, the new values of the Matrix are calculated\n as \n\n.\n\n The function returns a vector containing the `min` and `max` values of the columns\n before normalization, see matrix_col_minmax().\n\n \n        Input data Matrix; normalization is done inline.\n \n\n            Vector containing the min and max values for each column before normalization.\n\nC++: genesis::utils::normalize_cols(class genesis::utils::Matrix<double> &) --> class std::vector<struct genesis::utils::MinMaxPair<double>, class std::allocator<struct genesis::utils::MinMaxPair<double> > >", pybind11::arg("data"));

	// genesis::utils::normalize_rows(class genesis::utils::Matrix<double> &) file:genesis/utils/math/matrix.hpp line:276
	M("genesis::utils").def("normalize_rows", (class std::vector<struct genesis::utils::MinMaxPair<double>, class std::allocator<struct genesis::utils::MinMaxPair<double> > > (*)(class genesis::utils::Matrix<double> &)) &genesis::utils::normalize_rows, "Normalize the rows of a Matrix so that all values are in the range `[ 0.0, 1.0 ]`.\n\n The Matrix is manipulated inline. For each row, the new values of the Matrix are calculated\n as \n\n.\n\n The function returns a vector containing the `min` and `max` values of the rows\n before normalization, see matrix_row_minmax().\n\n \n        Input data Matrix; normalization is done inline.\n \n\n            Vector containing the min and max values for each row before normalization.\n\nC++: genesis::utils::normalize_rows(class genesis::utils::Matrix<double> &) --> class std::vector<struct genesis::utils::MinMaxPair<double>, class std::allocator<struct genesis::utils::MinMaxPair<double> > >", pybind11::arg("data"));

	// genesis::utils::standardize_cols(class genesis::utils::Matrix<double> &, bool, bool) file:genesis/utils/math/matrix.hpp line:295
	M("genesis::utils").def("standardize_cols", [](class genesis::utils::Matrix<double> & a0) -> std::vector<struct genesis::utils::MeanStddevPair, class std::allocator<struct genesis::utils::MeanStddevPair> > { return genesis::utils::standardize_cols(a0); }, "", pybind11::arg("data"));
	M("genesis::utils").def("standardize_cols", [](class genesis::utils::Matrix<double> & a0, bool const & a1) -> std::vector<struct genesis::utils::MeanStddevPair, class std::allocator<struct genesis::utils::MeanStddevPair> > { return genesis::utils::standardize_cols(a0, a1); }, "", pybind11::arg("data"), pybind11::arg("scale_means"));
	M("genesis::utils").def("standardize_cols", (class std::vector<struct genesis::utils::MeanStddevPair, class std::allocator<struct genesis::utils::MeanStddevPair> > (*)(class genesis::utils::Matrix<double> &, bool, bool)) &genesis::utils::standardize_cols, "Standardize the columns of a Matrix by subtracting the mean and scaling to unit variance.\n\n The function performs a column-wise z-transformation on the given data.\n\n The function returns a vector containing the mean and standard deviation of the columns\n before standardization, see MeanStddevPair. If both `scale_means` and `scale_std` are\n set to `false`, the original data is not manipulated, while the returned vector still contains\n the means and standard deviations. See also matrix_col_mean_stddev().\n\n \n        Input data Matrix; standardizing is done inline.\n \n\n If `true` (default), center the data by subtracting the mean per column.\n \n\n   If `true` (default), scale the data to unit variance (or equivalently,\n                    unit standard deviation) per column.\n \n\n            Vector containing the mean and standard deviation for each column before\n                    standardization.\n\nC++: genesis::utils::standardize_cols(class genesis::utils::Matrix<double> &, bool, bool) --> class std::vector<struct genesis::utils::MeanStddevPair, class std::allocator<struct genesis::utils::MeanStddevPair> >", pybind11::arg("data"), pybind11::arg("scale_means"), pybind11::arg("scale_std"));

	// genesis::utils::standardize_rows(class genesis::utils::Matrix<double> &, bool, bool) file:genesis/utils/math/matrix.hpp line:318
	M("genesis::utils").def("standardize_rows", [](class genesis::utils::Matrix<double> & a0) -> std::vector<struct genesis::utils::MeanStddevPair, class std::allocator<struct genesis::utils::MeanStddevPair> > { return genesis::utils::standardize_rows(a0); }, "", pybind11::arg("data"));
	M("genesis::utils").def("standardize_rows", [](class genesis::utils::Matrix<double> & a0, bool const & a1) -> std::vector<struct genesis::utils::MeanStddevPair, class std::allocator<struct genesis::utils::MeanStddevPair> > { return genesis::utils::standardize_rows(a0, a1); }, "", pybind11::arg("data"), pybind11::arg("scale_means"));
	M("genesis::utils").def("standardize_rows", (class std::vector<struct genesis::utils::MeanStddevPair, class std::allocator<struct genesis::utils::MeanStddevPair> > (*)(class genesis::utils::Matrix<double> &, bool, bool)) &genesis::utils::standardize_rows, "Standardize the rows of a Matrix by subtracting the mean and scaling to unit variance.\n\n The function performs a row-wise z-transformation on the given data.\n\n The function returns a vector containing the mean and standard deviation of the rows\n before standardization, see MeanStddevPair. If both `scale_means` and `scale_std` are\n set to `false`, the original data is not manipulated, while the returned vector still contains\n the means and standard deviations. See also matrix_row_mean_stddev().\n\n \n        Input data Matrix; standardizing is done inline.\n \n\n If `true` (default), center the data by subtracting the mean per column.\n \n\n   If `true` (default), scale the data to unit variance (or equivalently,\n                    unit standard deviation) per column.\n \n\n            Vector containing the mean and standard deviation for each column before\n                    standardization.\n\nC++: genesis::utils::standardize_rows(class genesis::utils::Matrix<double> &, bool, bool) --> class std::vector<struct genesis::utils::MeanStddevPair, class std::allocator<struct genesis::utils::MeanStddevPair> >", pybind11::arg("data"), pybind11::arg("scale_means"), pybind11::arg("scale_std"));

	// genesis::utils::filter_constant_columns(class genesis::utils::Matrix<double> &, double) file:genesis/utils/math/matrix.hpp line:338
	M("genesis::utils").def("filter_constant_columns", [](class genesis::utils::Matrix<double> & a0) -> std::vector<unsigned long, class std::allocator<unsigned long> > { return genesis::utils::filter_constant_columns(a0); }, "", pybind11::arg("data"));
	M("genesis::utils").def("filter_constant_columns", (class std::vector<unsigned long, class std::allocator<unsigned long> > (*)(class genesis::utils::Matrix<double> &, double)) &genesis::utils::filter_constant_columns, "Filter out columns that have nearly constant values, measured using an \n\n The \n\n\n\n\n\n\n\n\n\n\n\nC++: genesis::utils::filter_constant_columns(class genesis::utils::Matrix<double> &, double) --> class std::vector<unsigned long, class std::allocator<unsigned long> >", pybind11::arg("data"), pybind11::arg("epsilon"));

	// genesis::utils::correlation_matrix(const class genesis::utils::Matrix<double> &) file:genesis/utils/math/matrix.hpp line:353
	M("genesis::utils").def("correlation_matrix", (class genesis::utils::Matrix<double> (*)(const class genesis::utils::Matrix<double> &)) &genesis::utils::correlation_matrix, "Calculate the correlation Matrix of a given `data` Matrix.\n\n This is done by standardizing the mean and variance of the given `data` and then calculating the\n sums_of_squares_and_cross_products_matrix().\n\nC++: genesis::utils::correlation_matrix(const class genesis::utils::Matrix<double> &) --> class genesis::utils::Matrix<double>", pybind11::arg("data"));

	// genesis::utils::covariance_matrix(const class genesis::utils::Matrix<double> &) file:genesis/utils/math/matrix.hpp line:361
	M("genesis::utils").def("covariance_matrix", (class genesis::utils::Matrix<double> (*)(const class genesis::utils::Matrix<double> &)) &genesis::utils::covariance_matrix, "Calculate the covariance Matrix of a given `data` Matrix.\n\n This is done by standardizing the mean of the given `data` and then calculating the\n sums_of_squares_and_cross_products_matrix().\n\nC++: genesis::utils::covariance_matrix(const class genesis::utils::Matrix<double> &) --> class genesis::utils::Matrix<double>", pybind11::arg("data"));

	// genesis::utils::sums_of_squares_and_cross_products_matrix(const class genesis::utils::Matrix<double> &) file:genesis/utils/math/matrix.hpp line:366
	M("genesis::utils").def("sums_of_squares_and_cross_products_matrix", (class genesis::utils::Matrix<double> (*)(const class genesis::utils::Matrix<double> &)) &genesis::utils::sums_of_squares_and_cross_products_matrix, "Calculate the Sums of Squares and Cross Products Matrix (SSCP Matrix).\n\nC++: genesis::utils::sums_of_squares_and_cross_products_matrix(const class genesis::utils::Matrix<double> &) --> class genesis::utils::Matrix<double>", pybind11::arg("data"));

	// genesis::utils::matrix_multiplication(const class genesis::utils::Matrix<signed char> &, const class std::vector<double, class std::allocator<double> > &) file:genesis/utils/math/matrix.hpp line:602
	M("genesis::utils").def("matrix_multiplication", (class std::vector<double, class std::allocator<double> > (*)(const class genesis::utils::Matrix<signed char> &, const class std::vector<double, class std::allocator<double> > &)) &genesis::utils::matrix_multiplication<double,signed char,double>, "C++: genesis::utils::matrix_multiplication(const class genesis::utils::Matrix<signed char> &, const class std::vector<double, class std::allocator<double> > &) --> class std::vector<double, class std::allocator<double> >", pybind11::arg("a"), pybind11::arg("b"));

	{ // genesis::utils::Interval file:genesis/utils/containers/interval_tree/interval.hpp line:271
		pybind11::class_<genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>, std::shared_ptr<genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>>> cl(M("genesis::utils"), "Interval_genesis_population_EmptyGenomeData_unsigned_long_genesis_utils_IntervalClosed_t", "");
		cl.def( pybind11::init<unsigned long, unsigned long>(), pybind11::arg("low"), pybind11::arg("high") );

		cl.def( pybind11::init<unsigned long, unsigned long, const struct genesis::population::EmptyGenomeData &>(), pybind11::arg("low"), pybind11::arg("high"), pybind11::arg("data") );

		cl.def( pybind11::init( [](genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed> const &o){ return new genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>(o); } ) );
		cl.def("assign", (struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> & (genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &)) &genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::operator=, "C++: genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::operator=(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) --> struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("overlaps", (bool (genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(unsigned long, unsigned long) const) &genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::overlaps, "C++: genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::overlaps(unsigned long, unsigned long) const --> bool", pybind11::arg("l"), pybind11::arg("h"));
		cl.def("overlaps_exclusive", (bool (genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(unsigned long, unsigned long) const) &genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::overlaps_exclusive, "C++: genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::overlaps_exclusive(unsigned long, unsigned long) const --> bool", pybind11::arg("l"), pybind11::arg("h"));
		cl.def("overlaps", (bool (genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) const) &genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::overlaps, "C++: genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::overlaps(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) const --> bool", pybind11::arg("other"));
		cl.def("overlaps_exclusive", (bool (genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) const) &genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::overlaps_exclusive, "C++: genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::overlaps_exclusive(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) const --> bool", pybind11::arg("other"));
		cl.def("within", (bool (genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(unsigned long) const) &genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::within, "C++: genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::within(unsigned long) const --> bool", pybind11::arg("value"));
		cl.def("within", (bool (genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) const) &genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::within, "C++: genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::within(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) const --> bool", pybind11::arg("other"));
		cl.def("__sub__", (unsigned long (genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) const) &genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::operator-, "C++: genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::operator-(const struct genesis::utils::Interval<struct genesis::population::EmptyGenomeData, unsigned long, struct genesis::utils::IntervalClosed> &) const --> unsigned long", pybind11::arg("other"));
		cl.def("low", (unsigned long (genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::low, "C++: genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::low() const --> unsigned long");
		cl.def("high", (unsigned long (genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::high, "C++: genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::high() const --> unsigned long");
		cl.def("size", (unsigned long (genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)() const) &genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::size, "C++: genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::size() const --> unsigned long");
		cl.def("to_string", [](genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed> const &o) -> std::string { return o.to_string(); }, "");
		cl.def("to_string", (std::string (genesis::utils::Interval<genesis::population::EmptyGenomeData,unsigned long,genesis::utils::IntervalClosed>::*)(bool) const) &genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::to_string, "C++: genesis::utils::Interval<genesis::population::EmptyGenomeData, unsigned long, genesis::utils::IntervalClosed>::to_string(bool) const --> std::string", pybind11::arg("narrow"));
	}
}
