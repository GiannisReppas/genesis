#include <genesis/utils/containers/matrix.hpp>
#include <genesis/utils/containers/matrix/operators.hpp>
#include <genesis/utils/containers/matrix/row.hpp>
#include <ios>
#include <iterator>
#include <locale>
#include <memory>
#include <ostream>
#include <sstream> // __str__
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

void bind_genesis_utils_containers_matrix_1(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // genesis::utils::Matrix file:genesis/utils/containers/matrix.hpp line:50
		pybind11::class_<genesis::utils::Matrix<unsigned long>, std::shared_ptr<genesis::utils::Matrix<unsigned long>>> cl(M("genesis::utils"), "Matrix_unsigned_long_t", "");
		cl.def( pybind11::init( [](){ return new genesis::utils::Matrix<unsigned long>(); } ) );
		cl.def( pybind11::init<unsigned long, unsigned long>(), pybind11::arg("rows"), pybind11::arg("cols") );

		cl.def( pybind11::init<unsigned long, unsigned long, unsigned long>(), pybind11::arg("rows"), pybind11::arg("cols"), pybind11::arg("init") );

		cl.def( pybind11::init<unsigned long, unsigned long, const class std::vector<unsigned long, class std::allocator<unsigned long> > &>(), pybind11::arg("rows"), pybind11::arg("cols"), pybind11::arg("data") );

		cl.def( pybind11::init( [](genesis::utils::Matrix<unsigned long> const &o){ return new genesis::utils::Matrix<unsigned long>(o); } ) );
		cl.def("assign", (class genesis::utils::Matrix<unsigned long> & (genesis::utils::Matrix<unsigned long>::*)(const class genesis::utils::Matrix<unsigned long> &)) &genesis::utils::Matrix<unsigned long>::operator=, "C++: genesis::utils::Matrix<unsigned long>::operator=(const class genesis::utils::Matrix<unsigned long> &) --> class genesis::utils::Matrix<unsigned long> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("swap", (void (genesis::utils::Matrix<unsigned long>::*)(class genesis::utils::Matrix<unsigned long> &)) &genesis::utils::Matrix<unsigned long>::swap, "C++: genesis::utils::Matrix<unsigned long>::swap(class genesis::utils::Matrix<unsigned long> &) --> void", pybind11::arg("other"));
		cl.def("rows", (unsigned long (genesis::utils::Matrix<unsigned long>::*)() const) &genesis::utils::Matrix<unsigned long>::rows, "C++: genesis::utils::Matrix<unsigned long>::rows() const --> unsigned long");
		cl.def("cols", (unsigned long (genesis::utils::Matrix<unsigned long>::*)() const) &genesis::utils::Matrix<unsigned long>::cols, "C++: genesis::utils::Matrix<unsigned long>::cols() const --> unsigned long");
		cl.def("size", (unsigned long (genesis::utils::Matrix<unsigned long>::*)() const) &genesis::utils::Matrix<unsigned long>::size, "C++: genesis::utils::Matrix<unsigned long>::size() const --> unsigned long");
		cl.def("empty", (bool (genesis::utils::Matrix<unsigned long>::*)() const) &genesis::utils::Matrix<unsigned long>::empty, "C++: genesis::utils::Matrix<unsigned long>::empty() const --> bool");
		cl.def("data", (const class std::vector<unsigned long, class std::allocator<unsigned long> > & (genesis::utils::Matrix<unsigned long>::*)() const) &genesis::utils::Matrix<unsigned long>::data, "C++: genesis::utils::Matrix<unsigned long>::data() const --> const class std::vector<unsigned long, class std::allocator<unsigned long> > &", pybind11::return_value_policy::reference_internal);
		cl.def("at", (unsigned long & (genesis::utils::Matrix<unsigned long>::*)(const unsigned long, const unsigned long)) &genesis::utils::Matrix<unsigned long>::at, "C++: genesis::utils::Matrix<unsigned long>::at(const unsigned long, const unsigned long) --> unsigned long &", pybind11::return_value_policy::reference_internal, pybind11::arg("row"), pybind11::arg("col"));
		cl.def("__call__", (unsigned long & (genesis::utils::Matrix<unsigned long>::*)(const unsigned long, const unsigned long)) &genesis::utils::Matrix<unsigned long>::operator(), "C++: genesis::utils::Matrix<unsigned long>::operator()(const unsigned long, const unsigned long) --> unsigned long &", pybind11::return_value_policy::reference_internal, pybind11::arg("row"), pybind11::arg("col"));
		cl.def("begin", (class __gnu_cxx::__normal_iterator<unsigned long *, class std::vector<unsigned long, class std::allocator<unsigned long> > > (genesis::utils::Matrix<unsigned long>::*)()) &genesis::utils::Matrix<unsigned long>::begin, "C++: genesis::utils::Matrix<unsigned long>::begin() --> class __gnu_cxx::__normal_iterator<unsigned long *, class std::vector<unsigned long, class std::allocator<unsigned long> > >");
		cl.def("end", (class __gnu_cxx::__normal_iterator<unsigned long *, class std::vector<unsigned long, class std::allocator<unsigned long> > > (genesis::utils::Matrix<unsigned long>::*)()) &genesis::utils::Matrix<unsigned long>::end, "C++: genesis::utils::Matrix<unsigned long>::end() --> class __gnu_cxx::__normal_iterator<unsigned long *, class std::vector<unsigned long, class std::allocator<unsigned long> > >");
		cl.def("cbegin", (class __gnu_cxx::__normal_iterator<const unsigned long *, class std::vector<unsigned long, class std::allocator<unsigned long> > > (genesis::utils::Matrix<unsigned long>::*)() const) &genesis::utils::Matrix<unsigned long>::cbegin, "C++: genesis::utils::Matrix<unsigned long>::cbegin() const --> class __gnu_cxx::__normal_iterator<const unsigned long *, class std::vector<unsigned long, class std::allocator<unsigned long> > >");
		cl.def("cend", (class __gnu_cxx::__normal_iterator<const unsigned long *, class std::vector<unsigned long, class std::allocator<unsigned long> > > (genesis::utils::Matrix<unsigned long>::*)() const) &genesis::utils::Matrix<unsigned long>::cend, "C++: genesis::utils::Matrix<unsigned long>::cend() const --> class __gnu_cxx::__normal_iterator<const unsigned long *, class std::vector<unsigned long, class std::allocator<unsigned long> > >");
		cl.def("__eq__", (bool (genesis::utils::Matrix<unsigned long>::*)(const class genesis::utils::Matrix<unsigned long> &) const) &genesis::utils::Matrix<unsigned long>::operator==, "C++: genesis::utils::Matrix<unsigned long>::operator==(const class genesis::utils::Matrix<unsigned long> &) const --> bool", pybind11::arg("other"));
		cl.def("__ne__", (bool (genesis::utils::Matrix<unsigned long>::*)(const class genesis::utils::Matrix<unsigned long> &) const) &genesis::utils::Matrix<unsigned long>::operator!=, "C++: genesis::utils::Matrix<unsigned long>::operator!=(const class genesis::utils::Matrix<unsigned long> &) const --> bool", pybind11::arg("other"));

		cl.def("__str__", [](genesis::utils::Matrix<unsigned long> const &o) -> std::string { std::ostringstream s; genesis::utils::operator<<(s, o); return s.str(); } );

		extend_matrix(cl);
	}
	{ // genesis::utils::Matrix file:genesis/utils/containers/matrix.hpp line:50
		pybind11::class_<genesis::utils::Matrix<pybind11::object>, std::shared_ptr<genesis::utils::Matrix<pybind11::object>>> cl(M("genesis::utils"), "Matrix_pybind11_object_t", "");
		cl.def( pybind11::init( [](){ return new genesis::utils::Matrix<pybind11::object>(); } ) );
		cl.def( pybind11::init<unsigned long, unsigned long>(), pybind11::arg("rows"), pybind11::arg("cols") );

		cl.def( pybind11::init<unsigned long, unsigned long, class pybind11::object>(), pybind11::arg("rows"), pybind11::arg("cols"), pybind11::arg("init") );

		cl.def( pybind11::init<unsigned long, unsigned long, const class std::vector<class pybind11::object, class std::allocator<class pybind11::object> > &>(), pybind11::arg("rows"), pybind11::arg("cols"), pybind11::arg("data") );

		cl.def( pybind11::init( [](genesis::utils::Matrix<pybind11::object> const &o){ return new genesis::utils::Matrix<pybind11::object>(o); } ) );
		cl.def("assign", (class genesis::utils::Matrix<class pybind11::object> & (genesis::utils::Matrix<pybind11::object>::*)(const class genesis::utils::Matrix<class pybind11::object> &)) &genesis::utils::Matrix<pybind11::object>::operator=, "C++: genesis::utils::Matrix<pybind11::object>::operator=(const class genesis::utils::Matrix<class pybind11::object> &) --> class genesis::utils::Matrix<class pybind11::object> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("swap", (void (genesis::utils::Matrix<pybind11::object>::*)(class genesis::utils::Matrix<class pybind11::object> &)) &genesis::utils::Matrix<pybind11::object>::swap, "C++: genesis::utils::Matrix<pybind11::object>::swap(class genesis::utils::Matrix<class pybind11::object> &) --> void", pybind11::arg("other"));
		cl.def("rows", (unsigned long (genesis::utils::Matrix<pybind11::object>::*)() const) &genesis::utils::Matrix<pybind11::object>::rows, "C++: genesis::utils::Matrix<pybind11::object>::rows() const --> unsigned long");
		cl.def("cols", (unsigned long (genesis::utils::Matrix<pybind11::object>::*)() const) &genesis::utils::Matrix<pybind11::object>::cols, "C++: genesis::utils::Matrix<pybind11::object>::cols() const --> unsigned long");
		cl.def("size", (unsigned long (genesis::utils::Matrix<pybind11::object>::*)() const) &genesis::utils::Matrix<pybind11::object>::size, "C++: genesis::utils::Matrix<pybind11::object>::size() const --> unsigned long");
		cl.def("empty", (bool (genesis::utils::Matrix<pybind11::object>::*)() const) &genesis::utils::Matrix<pybind11::object>::empty, "C++: genesis::utils::Matrix<pybind11::object>::empty() const --> bool");
		cl.def("data", (const class std::vector<class pybind11::object, class std::allocator<class pybind11::object> > & (genesis::utils::Matrix<pybind11::object>::*)() const) &genesis::utils::Matrix<pybind11::object>::data, "C++: genesis::utils::Matrix<pybind11::object>::data() const --> const class std::vector<class pybind11::object, class std::allocator<class pybind11::object> > &", pybind11::return_value_policy::reference_internal);
		cl.def("at", (class pybind11::object & (genesis::utils::Matrix<pybind11::object>::*)(const unsigned long, const unsigned long)) &genesis::utils::Matrix<pybind11::object>::at, "C++: genesis::utils::Matrix<pybind11::object>::at(const unsigned long, const unsigned long) --> class pybind11::object &", pybind11::return_value_policy::reference_internal, pybind11::arg("row"), pybind11::arg("col"));
		cl.def("__call__", (class pybind11::object & (genesis::utils::Matrix<pybind11::object>::*)(const unsigned long, const unsigned long)) &genesis::utils::Matrix<pybind11::object>::operator(), "C++: genesis::utils::Matrix<pybind11::object>::operator()(const unsigned long, const unsigned long) --> class pybind11::object &", pybind11::return_value_policy::reference_internal, pybind11::arg("row"), pybind11::arg("col"));
		cl.def("begin", (class __gnu_cxx::__normal_iterator<class pybind11::object *, class std::vector<class pybind11::object, class std::allocator<class pybind11::object> > > (genesis::utils::Matrix<pybind11::object>::*)()) &genesis::utils::Matrix<pybind11::object>::begin, "C++: genesis::utils::Matrix<pybind11::object>::begin() --> class __gnu_cxx::__normal_iterator<class pybind11::object *, class std::vector<class pybind11::object, class std::allocator<class pybind11::object> > >");
		cl.def("end", (class __gnu_cxx::__normal_iterator<class pybind11::object *, class std::vector<class pybind11::object, class std::allocator<class pybind11::object> > > (genesis::utils::Matrix<pybind11::object>::*)()) &genesis::utils::Matrix<pybind11::object>::end, "C++: genesis::utils::Matrix<pybind11::object>::end() --> class __gnu_cxx::__normal_iterator<class pybind11::object *, class std::vector<class pybind11::object, class std::allocator<class pybind11::object> > >");
		cl.def("cbegin", (class __gnu_cxx::__normal_iterator<const class pybind11::object *, class std::vector<class pybind11::object, class std::allocator<class pybind11::object> > > (genesis::utils::Matrix<pybind11::object>::*)() const) &genesis::utils::Matrix<pybind11::object>::cbegin, "C++: genesis::utils::Matrix<pybind11::object>::cbegin() const --> class __gnu_cxx::__normal_iterator<const class pybind11::object *, class std::vector<class pybind11::object, class std::allocator<class pybind11::object> > >");
		cl.def("cend", (class __gnu_cxx::__normal_iterator<const class pybind11::object *, class std::vector<class pybind11::object, class std::allocator<class pybind11::object> > > (genesis::utils::Matrix<pybind11::object>::*)() const) &genesis::utils::Matrix<pybind11::object>::cend, "C++: genesis::utils::Matrix<pybind11::object>::cend() const --> class __gnu_cxx::__normal_iterator<const class pybind11::object *, class std::vector<class pybind11::object, class std::allocator<class pybind11::object> > >");
		cl.def("__eq__", (bool (genesis::utils::Matrix<pybind11::object>::*)(const class genesis::utils::Matrix<class pybind11::object> &) const) &genesis::utils::Matrix<pybind11::object>::operator==, "C++: genesis::utils::Matrix<pybind11::object>::operator==(const class genesis::utils::Matrix<class pybind11::object> &) const --> bool", pybind11::arg("other"));
		cl.def("__ne__", (bool (genesis::utils::Matrix<pybind11::object>::*)(const class genesis::utils::Matrix<class pybind11::object> &) const) &genesis::utils::Matrix<pybind11::object>::operator!=, "C++: genesis::utils::Matrix<pybind11::object>::operator!=(const class genesis::utils::Matrix<class pybind11::object> &) const --> bool", pybind11::arg("other"));

		cl.def("__str__", [](genesis::utils::Matrix<pybind11::object> const &o) -> std::string { std::ostringstream s; genesis::utils::operator<<(s, o); return s.str(); } );

		extend_matrix(cl);
	}
	{ // genesis::utils::MatrixRow file:genesis/utils/containers/matrix/row.hpp line:60
		pybind11::class_<genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>,unsigned int>, std::shared_ptr<genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>,unsigned int>>> cl(M("genesis::utils"), "MatrixRow_genesis_utils_Matrix_unsigned_int_unsigned_int_t", "");
		cl.def( pybind11::init<class genesis::utils::Matrix<unsigned int> &, unsigned long>(), pybind11::arg("mat"), pybind11::arg("row") );

		cl.def( pybind11::init( [](genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>,unsigned int> const &o){ return new genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>,unsigned int>(o); } ) );
		cl.def("assign", (class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int> & (genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>,unsigned int>::*)(const class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int> &)) &genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::operator=, "C++: genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::operator=(const class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int> &) --> class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("at", (unsigned int & (genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>,unsigned int>::*)(unsigned long) const) &genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::at, "C++: genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::at(unsigned long) const --> unsigned int &", pybind11::return_value_policy::reference_internal, pybind11::arg("column"));
		cl.def("__getitem__", (unsigned int & (genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>,unsigned int>::*)(unsigned long) const) &genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::operator[], "C++: genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::operator[](unsigned long) const --> unsigned int &", pybind11::return_value_policy::reference_internal, pybind11::arg("column"));
		cl.def("matrix", (class genesis::utils::Matrix<unsigned int> & (genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>,unsigned int>::*)() const) &genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::matrix, "C++: genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::matrix() const --> class genesis::utils::Matrix<unsigned int> &", pybind11::return_value_policy::reference_internal);
		cl.def("row", (unsigned long (genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>,unsigned int>::*)() const) &genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::row, "C++: genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::row() const --> unsigned long");
		cl.def("size", (unsigned long (genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>,unsigned int>::*)() const) &genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::size, "C++: genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::size() const --> unsigned long");
		cl.def("to_vector", (class std::vector<unsigned int, class std::allocator<unsigned int> > (genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>,unsigned int>::*)() const) &genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::to_vector, "C++: genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::to_vector() const --> class std::vector<unsigned int, class std::allocator<unsigned int> >");
		cl.def("assign", (class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int> & (genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>,unsigned int>::*)(const class std::vector<unsigned int, class std::allocator<unsigned int> > &)) &genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::operator=, "C++: genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::operator=(const class std::vector<unsigned int, class std::allocator<unsigned int> > &) --> class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int> &", pybind11::return_value_policy::reference_internal, pybind11::arg("vec"));
		cl.def("assign", (class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int> & (genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>,unsigned int>::*)(const class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int> &)) &genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::assign, "C++: genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::assign(const class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int> &) --> class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int> &", pybind11::return_value_policy::reference_internal, pybind11::arg("other"));
		cl.def("__eq__", (bool (genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>,unsigned int>::*)(const class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int> &) const) &genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::operator==, "C++: genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::operator==(const class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int> &) const --> bool", pybind11::arg("other"));
		cl.def("__ne__", (bool (genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>,unsigned int>::*)(const class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int> &) const) &genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::operator!=, "C++: genesis::utils::MatrixRow<genesis::utils::Matrix<unsigned int>, unsigned int>::operator!=(const class genesis::utils::MatrixRow<class genesis::utils::Matrix<unsigned int>, unsigned int> &) const --> bool", pybind11::arg("other"));
	}
}
