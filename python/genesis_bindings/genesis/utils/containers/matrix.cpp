#include <genesis/utils/color/color.hpp>
#include <genesis/utils/containers/matrix.hpp>
#include <genesis/utils/containers/matrix/row.hpp>
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

void bind_genesis_utils_containers_matrix(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// genesis::utils::transpose_inplace(class genesis::utils::Matrix<class genesis::utils::Color> &) file:genesis/utils/containers/matrix.hpp line:170
	M("genesis::utils").def("transpose_inplace", (void (*)(class genesis::utils::Matrix<class genesis::utils::Color> &)) &genesis::utils::transpose_inplace<genesis::utils::Color>, "C++: genesis::utils::transpose_inplace(class genesis::utils::Matrix<class genesis::utils::Color> &) --> void", pybind11::arg(""));

	{ // genesis::utils::Matrix file:genesis/utils/containers/matrix.hpp line:60
		pybind11::class_<genesis::utils::Matrix<double>, std::shared_ptr<genesis::utils::Matrix<double>>> cl(M("genesis::utils"), "Matrix_double_t", "");
		cl.def( pybind11::init( [](){ return new genesis::utils::Matrix<double>(); } ) );
		cl.def( pybind11::init<unsigned long, unsigned long>(), pybind11::arg("rows"), pybind11::arg("cols") );

		cl.def( pybind11::init<unsigned long, unsigned long, double>(), pybind11::arg("rows"), pybind11::arg("cols"), pybind11::arg("init") );

		cl.def( pybind11::init<unsigned long, unsigned long, const class std::vector<double, class std::allocator<double> > &>(), pybind11::arg("rows"), pybind11::arg("cols"), pybind11::arg("data") );

		cl.def( pybind11::init( [](genesis::utils::Matrix<double> const &o){ return new genesis::utils::Matrix<double>(o); } ) );
		cl.def("assign", (class genesis::utils::Matrix<double> & (genesis::utils::Matrix<double>::*)(const class genesis::utils::Matrix<double> &)) &genesis::utils::Matrix<double>::operator=, "C++: genesis::utils::Matrix<double>::operator=(const class genesis::utils::Matrix<double> &) --> class genesis::utils::Matrix<double> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("swap", (void (genesis::utils::Matrix<double>::*)(class genesis::utils::Matrix<double> &)) &genesis::utils::Matrix<double>::swap, "C++: genesis::utils::Matrix<double>::swap(class genesis::utils::Matrix<double> &) --> void", pybind11::arg("other"));
		cl.def("rows", (unsigned long (genesis::utils::Matrix<double>::*)() const) &genesis::utils::Matrix<double>::rows, "C++: genesis::utils::Matrix<double>::rows() const --> unsigned long");
		cl.def("cols", (unsigned long (genesis::utils::Matrix<double>::*)() const) &genesis::utils::Matrix<double>::cols, "C++: genesis::utils::Matrix<double>::cols() const --> unsigned long");
		cl.def("size", (unsigned long (genesis::utils::Matrix<double>::*)() const) &genesis::utils::Matrix<double>::size, "C++: genesis::utils::Matrix<double>::size() const --> unsigned long");
		cl.def("empty", (bool (genesis::utils::Matrix<double>::*)() const) &genesis::utils::Matrix<double>::empty, "C++: genesis::utils::Matrix<double>::empty() const --> bool");
		cl.def("data", (const class std::vector<double, class std::allocator<double> > & (genesis::utils::Matrix<double>::*)() const) &genesis::utils::Matrix<double>::data, "C++: genesis::utils::Matrix<double>::data() const --> const class std::vector<double, class std::allocator<double> > &", pybind11::return_value_policy::reference_internal);
		cl.def("at", (double & (genesis::utils::Matrix<double>::*)(const unsigned long, const unsigned long)) &genesis::utils::Matrix<double>::at, "C++: genesis::utils::Matrix<double>::at(const unsigned long, const unsigned long) --> double &", pybind11::return_value_policy::reference_internal, pybind11::arg("row"), pybind11::arg("col"));
		cl.def("__call__", (double & (genesis::utils::Matrix<double>::*)(const unsigned long, const unsigned long)) &genesis::utils::Matrix<double>::operator(), "C++: genesis::utils::Matrix<double>::operator()(const unsigned long, const unsigned long) --> double &", pybind11::return_value_policy::reference_internal, pybind11::arg("row"), pybind11::arg("col"));
		cl.def("begin", (class __gnu_cxx::__normal_iterator<double *, class std::vector<double, class std::allocator<double> > > (genesis::utils::Matrix<double>::*)()) &genesis::utils::Matrix<double>::begin, "C++: genesis::utils::Matrix<double>::begin() --> class __gnu_cxx::__normal_iterator<double *, class std::vector<double, class std::allocator<double> > >");
		cl.def("end", (class __gnu_cxx::__normal_iterator<double *, class std::vector<double, class std::allocator<double> > > (genesis::utils::Matrix<double>::*)()) &genesis::utils::Matrix<double>::end, "C++: genesis::utils::Matrix<double>::end() --> class __gnu_cxx::__normal_iterator<double *, class std::vector<double, class std::allocator<double> > >");
		cl.def("cbegin", (class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > > (genesis::utils::Matrix<double>::*)() const) &genesis::utils::Matrix<double>::cbegin, "C++: genesis::utils::Matrix<double>::cbegin() const --> class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >");
		cl.def("cend", (class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > > (genesis::utils::Matrix<double>::*)() const) &genesis::utils::Matrix<double>::cend, "C++: genesis::utils::Matrix<double>::cend() const --> class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >");
		cl.def("__eq__", (bool (genesis::utils::Matrix<double>::*)(const class genesis::utils::Matrix<double> &) const) &genesis::utils::Matrix<double>::operator==, "C++: genesis::utils::Matrix<double>::operator==(const class genesis::utils::Matrix<double> &) const --> bool", pybind11::arg("other"));
		cl.def("__ne__", (bool (genesis::utils::Matrix<double>::*)(const class genesis::utils::Matrix<double> &) const) &genesis::utils::Matrix<double>::operator!=, "C++: genesis::utils::Matrix<double>::operator!=(const class genesis::utils::Matrix<double> &) const --> bool", pybind11::arg("other"));

		extend_matrix(cl);
	}
	// genesis::utils::transpose_inplace(class genesis::utils::Matrix<double> &) file:genesis/utils/containers/matrix.hpp line:170
	M("genesis::utils").def("transpose_inplace", (void (*)(class genesis::utils::Matrix<double> &)) &genesis::utils::transpose_inplace<double>, "C++: genesis::utils::transpose_inplace(class genesis::utils::Matrix<double> &) --> void", pybind11::arg(""));

	{ // genesis::utils::Matrix file:genesis/utils/containers/matrix.hpp line:60
		pybind11::class_<genesis::utils::Matrix<unsigned int>, std::shared_ptr<genesis::utils::Matrix<unsigned int>>> cl(M("genesis::utils"), "Matrix_unsigned_int_t", "");
		cl.def( pybind11::init( [](){ return new genesis::utils::Matrix<unsigned int>(); } ) );
		cl.def( pybind11::init<unsigned long, unsigned long>(), pybind11::arg("rows"), pybind11::arg("cols") );

		cl.def( pybind11::init<unsigned long, unsigned long, unsigned int>(), pybind11::arg("rows"), pybind11::arg("cols"), pybind11::arg("init") );

		cl.def( pybind11::init<unsigned long, unsigned long, const class std::vector<unsigned int, class std::allocator<unsigned int> > &>(), pybind11::arg("rows"), pybind11::arg("cols"), pybind11::arg("data") );

		cl.def( pybind11::init( [](genesis::utils::Matrix<unsigned int> const &o){ return new genesis::utils::Matrix<unsigned int>(o); } ) );
		cl.def("assign", (class genesis::utils::Matrix<unsigned int> & (genesis::utils::Matrix<unsigned int>::*)(const class genesis::utils::Matrix<unsigned int> &)) &genesis::utils::Matrix<unsigned int>::operator=, "C++: genesis::utils::Matrix<unsigned int>::operator=(const class genesis::utils::Matrix<unsigned int> &) --> class genesis::utils::Matrix<unsigned int> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("swap", (void (genesis::utils::Matrix<unsigned int>::*)(class genesis::utils::Matrix<unsigned int> &)) &genesis::utils::Matrix<unsigned int>::swap, "C++: genesis::utils::Matrix<unsigned int>::swap(class genesis::utils::Matrix<unsigned int> &) --> void", pybind11::arg("other"));
		cl.def("rows", (unsigned long (genesis::utils::Matrix<unsigned int>::*)() const) &genesis::utils::Matrix<unsigned int>::rows, "C++: genesis::utils::Matrix<unsigned int>::rows() const --> unsigned long");
		cl.def("cols", (unsigned long (genesis::utils::Matrix<unsigned int>::*)() const) &genesis::utils::Matrix<unsigned int>::cols, "C++: genesis::utils::Matrix<unsigned int>::cols() const --> unsigned long");
		cl.def("size", (unsigned long (genesis::utils::Matrix<unsigned int>::*)() const) &genesis::utils::Matrix<unsigned int>::size, "C++: genesis::utils::Matrix<unsigned int>::size() const --> unsigned long");
		cl.def("empty", (bool (genesis::utils::Matrix<unsigned int>::*)() const) &genesis::utils::Matrix<unsigned int>::empty, "C++: genesis::utils::Matrix<unsigned int>::empty() const --> bool");
		cl.def("data", (const class std::vector<unsigned int, class std::allocator<unsigned int> > & (genesis::utils::Matrix<unsigned int>::*)() const) &genesis::utils::Matrix<unsigned int>::data, "C++: genesis::utils::Matrix<unsigned int>::data() const --> const class std::vector<unsigned int, class std::allocator<unsigned int> > &", pybind11::return_value_policy::reference_internal);
		cl.def("at", (unsigned int & (genesis::utils::Matrix<unsigned int>::*)(const unsigned long, const unsigned long)) &genesis::utils::Matrix<unsigned int>::at, "C++: genesis::utils::Matrix<unsigned int>::at(const unsigned long, const unsigned long) --> unsigned int &", pybind11::return_value_policy::reference_internal, pybind11::arg("row"), pybind11::arg("col"));
		cl.def("__call__", (unsigned int & (genesis::utils::Matrix<unsigned int>::*)(const unsigned long, const unsigned long)) &genesis::utils::Matrix<unsigned int>::operator(), "C++: genesis::utils::Matrix<unsigned int>::operator()(const unsigned long, const unsigned long) --> unsigned int &", pybind11::return_value_policy::reference_internal, pybind11::arg("row"), pybind11::arg("col"));
		cl.def("row", (class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int> (genesis::utils::Matrix<unsigned int>::*)(unsigned long)) &genesis::utils::Matrix<unsigned int>::row, "C++: genesis::utils::Matrix<unsigned int>::row(unsigned long) --> class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int>", pybind11::arg("row"));
		cl.def("begin", (class __gnu_cxx::__normal_iterator<unsigned int *, class std::vector<unsigned int, class std::allocator<unsigned int> > > (genesis::utils::Matrix<unsigned int>::*)()) &genesis::utils::Matrix<unsigned int>::begin, "C++: genesis::utils::Matrix<unsigned int>::begin() --> class __gnu_cxx::__normal_iterator<unsigned int *, class std::vector<unsigned int, class std::allocator<unsigned int> > >");
		cl.def("end", (class __gnu_cxx::__normal_iterator<unsigned int *, class std::vector<unsigned int, class std::allocator<unsigned int> > > (genesis::utils::Matrix<unsigned int>::*)()) &genesis::utils::Matrix<unsigned int>::end, "C++: genesis::utils::Matrix<unsigned int>::end() --> class __gnu_cxx::__normal_iterator<unsigned int *, class std::vector<unsigned int, class std::allocator<unsigned int> > >");
		cl.def("cbegin", (class __gnu_cxx::__normal_iterator<const unsigned int *, class std::vector<unsigned int, class std::allocator<unsigned int> > > (genesis::utils::Matrix<unsigned int>::*)() const) &genesis::utils::Matrix<unsigned int>::cbegin, "C++: genesis::utils::Matrix<unsigned int>::cbegin() const --> class __gnu_cxx::__normal_iterator<const unsigned int *, class std::vector<unsigned int, class std::allocator<unsigned int> > >");
		cl.def("cend", (class __gnu_cxx::__normal_iterator<const unsigned int *, class std::vector<unsigned int, class std::allocator<unsigned int> > > (genesis::utils::Matrix<unsigned int>::*)() const) &genesis::utils::Matrix<unsigned int>::cend, "C++: genesis::utils::Matrix<unsigned int>::cend() const --> class __gnu_cxx::__normal_iterator<const unsigned int *, class std::vector<unsigned int, class std::allocator<unsigned int> > >");
		cl.def("__eq__", (bool (genesis::utils::Matrix<unsigned int>::*)(const class genesis::utils::Matrix<unsigned int> &) const) &genesis::utils::Matrix<unsigned int>::operator==, "C++: genesis::utils::Matrix<unsigned int>::operator==(const class genesis::utils::Matrix<unsigned int> &) const --> bool", pybind11::arg("other"));
		cl.def("__ne__", (bool (genesis::utils::Matrix<unsigned int>::*)(const class genesis::utils::Matrix<unsigned int> &) const) &genesis::utils::Matrix<unsigned int>::operator!=, "C++: genesis::utils::Matrix<unsigned int>::operator!=(const class genesis::utils::Matrix<unsigned int> &) const --> bool", pybind11::arg("other"));

		extend_matrix(cl);
	}
	// genesis::utils::transpose_inplace(class genesis::utils::Matrix<unsigned int> &) file:genesis/utils/containers/matrix.hpp line:170
	M("genesis::utils").def("transpose_inplace", (void (*)(class genesis::utils::Matrix<unsigned int> &)) &genesis::utils::transpose_inplace<unsigned int>, "C++: genesis::utils::transpose_inplace(class genesis::utils::Matrix<unsigned int> &) --> void", pybind11::arg(""));

	{ // genesis::utils::Matrix file:genesis/utils/containers/matrix.hpp line:60
		pybind11::class_<genesis::utils::Matrix<int>, std::shared_ptr<genesis::utils::Matrix<int>>> cl(M("genesis::utils"), "Matrix_int_t", "");
		cl.def( pybind11::init( [](){ return new genesis::utils::Matrix<int>(); } ) );
		cl.def( pybind11::init<unsigned long, unsigned long>(), pybind11::arg("rows"), pybind11::arg("cols") );

		cl.def( pybind11::init<unsigned long, unsigned long, int>(), pybind11::arg("rows"), pybind11::arg("cols"), pybind11::arg("init") );

		cl.def( pybind11::init<unsigned long, unsigned long, const class std::vector<int, class std::allocator<int> > &>(), pybind11::arg("rows"), pybind11::arg("cols"), pybind11::arg("data") );

		cl.def( pybind11::init( [](genesis::utils::Matrix<int> const &o){ return new genesis::utils::Matrix<int>(o); } ) );
		cl.def("assign", (class genesis::utils::Matrix<int> & (genesis::utils::Matrix<int>::*)(const class genesis::utils::Matrix<int> &)) &genesis::utils::Matrix<int>::operator=, "C++: genesis::utils::Matrix<int>::operator=(const class genesis::utils::Matrix<int> &) --> class genesis::utils::Matrix<int> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("swap", (void (genesis::utils::Matrix<int>::*)(class genesis::utils::Matrix<int> &)) &genesis::utils::Matrix<int>::swap, "C++: genesis::utils::Matrix<int>::swap(class genesis::utils::Matrix<int> &) --> void", pybind11::arg("other"));
		cl.def("rows", (unsigned long (genesis::utils::Matrix<int>::*)() const) &genesis::utils::Matrix<int>::rows, "C++: genesis::utils::Matrix<int>::rows() const --> unsigned long");
		cl.def("cols", (unsigned long (genesis::utils::Matrix<int>::*)() const) &genesis::utils::Matrix<int>::cols, "C++: genesis::utils::Matrix<int>::cols() const --> unsigned long");
		cl.def("size", (unsigned long (genesis::utils::Matrix<int>::*)() const) &genesis::utils::Matrix<int>::size, "C++: genesis::utils::Matrix<int>::size() const --> unsigned long");
		cl.def("empty", (bool (genesis::utils::Matrix<int>::*)() const) &genesis::utils::Matrix<int>::empty, "C++: genesis::utils::Matrix<int>::empty() const --> bool");
		cl.def("data", (const class std::vector<int, class std::allocator<int> > & (genesis::utils::Matrix<int>::*)() const) &genesis::utils::Matrix<int>::data, "C++: genesis::utils::Matrix<int>::data() const --> const class std::vector<int, class std::allocator<int> > &", pybind11::return_value_policy::reference_internal);
		cl.def("at", (int & (genesis::utils::Matrix<int>::*)(const unsigned long, const unsigned long)) &genesis::utils::Matrix<int>::at, "C++: genesis::utils::Matrix<int>::at(const unsigned long, const unsigned long) --> int &", pybind11::return_value_policy::reference_internal, pybind11::arg("row"), pybind11::arg("col"));
		cl.def("__call__", (int & (genesis::utils::Matrix<int>::*)(const unsigned long, const unsigned long)) &genesis::utils::Matrix<int>::operator(), "C++: genesis::utils::Matrix<int>::operator()(const unsigned long, const unsigned long) --> int &", pybind11::return_value_policy::reference_internal, pybind11::arg("row"), pybind11::arg("col"));
		cl.def("begin", (class __gnu_cxx::__normal_iterator<int *, class std::vector<int, class std::allocator<int> > > (genesis::utils::Matrix<int>::*)()) &genesis::utils::Matrix<int>::begin, "C++: genesis::utils::Matrix<int>::begin() --> class __gnu_cxx::__normal_iterator<int *, class std::vector<int, class std::allocator<int> > >");
		cl.def("end", (class __gnu_cxx::__normal_iterator<int *, class std::vector<int, class std::allocator<int> > > (genesis::utils::Matrix<int>::*)()) &genesis::utils::Matrix<int>::end, "C++: genesis::utils::Matrix<int>::end() --> class __gnu_cxx::__normal_iterator<int *, class std::vector<int, class std::allocator<int> > >");
		cl.def("cbegin", (class __gnu_cxx::__normal_iterator<const int *, class std::vector<int, class std::allocator<int> > > (genesis::utils::Matrix<int>::*)() const) &genesis::utils::Matrix<int>::cbegin, "C++: genesis::utils::Matrix<int>::cbegin() const --> class __gnu_cxx::__normal_iterator<const int *, class std::vector<int, class std::allocator<int> > >");
		cl.def("cend", (class __gnu_cxx::__normal_iterator<const int *, class std::vector<int, class std::allocator<int> > > (genesis::utils::Matrix<int>::*)() const) &genesis::utils::Matrix<int>::cend, "C++: genesis::utils::Matrix<int>::cend() const --> class __gnu_cxx::__normal_iterator<const int *, class std::vector<int, class std::allocator<int> > >");
		cl.def("__eq__", (bool (genesis::utils::Matrix<int>::*)(const class genesis::utils::Matrix<int> &) const) &genesis::utils::Matrix<int>::operator==, "C++: genesis::utils::Matrix<int>::operator==(const class genesis::utils::Matrix<int> &) const --> bool", pybind11::arg("other"));
		cl.def("__ne__", (bool (genesis::utils::Matrix<int>::*)(const class genesis::utils::Matrix<int> &) const) &genesis::utils::Matrix<int>::operator!=, "C++: genesis::utils::Matrix<int>::operator!=(const class genesis::utils::Matrix<int> &) const --> bool", pybind11::arg("other"));

		extend_matrix(cl);
	}
}
