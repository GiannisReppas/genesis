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

void bind_std_stl_iterator_base_types(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // std::input_iterator_tag file:bits/stl_iterator_base_types.h line:93
		pybind11::class_<std::input_iterator_tag, std::shared_ptr<std::input_iterator_tag>> cl(M("std"), "input_iterator_tag", "");
		cl.def( pybind11::init( [](){ return new std::input_iterator_tag(); } ) );
		cl.def( pybind11::init( [](std::input_iterator_tag const &o){ return new std::input_iterator_tag(o); } ) );
		cl.def("assign", (struct std::input_iterator_tag & (std::input_iterator_tag::*)(const struct std::input_iterator_tag &)) &std::input_iterator_tag::operator=, "C++: std::input_iterator_tag::operator=(const struct std::input_iterator_tag &) --> struct std::input_iterator_tag &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
	}
	{ // std::forward_iterator_tag file:bits/stl_iterator_base_types.h line:99
		pybind11::class_<std::forward_iterator_tag, std::shared_ptr<std::forward_iterator_tag>, std::input_iterator_tag> cl(M("std"), "forward_iterator_tag", "");
		cl.def( pybind11::init( [](){ return new std::forward_iterator_tag(); } ) );
		cl.def( pybind11::init( [](std::forward_iterator_tag const &o){ return new std::forward_iterator_tag(o); } ) );
		cl.def("assign", (struct std::forward_iterator_tag & (std::forward_iterator_tag::*)(const struct std::forward_iterator_tag &)) &std::forward_iterator_tag::operator=, "C++: std::forward_iterator_tag::operator=(const struct std::forward_iterator_tag &) --> struct std::forward_iterator_tag &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
	}
	{ // std::iterator file:bits/stl_iterator_base_types.h line:127
		pybind11::class_<std::iterator<std::random_access_iterator_tag,std::string,long,std::string *,std::string &>, std::shared_ptr<std::iterator<std::random_access_iterator_tag,std::string,long,std::string *,std::string &>>> cl(M("std"), "iterator_std_random_access_iterator_tag_std_string_long_std_string__star__std_string_&_t", "");
		cl.def( pybind11::init( [](){ return new std::iterator<std::random_access_iterator_tag,std::string,long,std::string *,std::string &>(); } ) );
		cl.def( pybind11::init( [](std::iterator<std::random_access_iterator_tag,std::string,long,std::string *,std::string &> const &o){ return new std::iterator<std::random_access_iterator_tag,std::string,long,std::string *,std::string &>(o); } ) );
		cl.def("assign", (struct std::iterator<struct std::random_access_iterator_tag, std::string, long, std::string *, std::string &> & (std::iterator<std::random_access_iterator_tag,std::string,long,std::string *,std::string &>::*)(const struct std::iterator<struct std::random_access_iterator_tag, std::string, long, std::string *, std::string &> &)) &std::iterator<std::random_access_iterator_tag, std::string, long, std::string *, std::string &>::operator=, "C++: std::iterator<std::random_access_iterator_tag, std::string, long, std::string *, std::string &>::operator=(const struct std::iterator<struct std::random_access_iterator_tag, std::string, long, std::string *, std::string &> &) --> struct std::iterator<struct std::random_access_iterator_tag, std::string, long, std::string *, std::string &> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
	}
	{ // std::reverse_iterator file:bits/stl_iterator.h line:128
		pybind11::class_<std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>, std::shared_ptr<std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>>, std::iterator<std::random_access_iterator_tag,std::string,long,std::string *,std::string &>> cl(M("std"), "reverse_iterator___gnu_cxx___normal_iterator_std_string__star__std_vector_std_string_t", "");
		cl.def( pybind11::init( [](){ return new std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>(); } ) );
		cl.def( pybind11::init<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > >>(), pybind11::arg("__x") );

		cl.def( pybind11::init( [](std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >> const &o){ return new std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>(o); } ) );
		cl.def("assign", (class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > & (std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>::*)(const class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > &)) &std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator=, "C++: std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator=(const class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > &) --> class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
		cl.def("base", (class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > (std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>::*)() const) &std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::base, "C++: std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::base() const --> class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > >");
		cl.def("dereference", (std::string & (std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>::*)() const) &std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator*, "C++: std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator*() const --> std::string &", pybind11::return_value_policy::reference_internal);
		cl.def("arrow", (std::string * (std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>::*)() const) &std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator->, "C++: std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator->() const --> std::string *", pybind11::return_value_policy::reference_internal);
		cl.def("pre_increment", (class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > & (std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>::*)()) &std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator++, "C++: std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator++() --> class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > &", pybind11::return_value_policy::reference_internal);
		cl.def("post_increment", (class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > (std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>::*)(int)) &std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator++, "C++: std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator++(int) --> class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > >", pybind11::arg(""));
		cl.def("pre_decrement", (class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > & (std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>::*)()) &std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator--, "C++: std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator--() --> class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > &", pybind11::return_value_policy::reference_internal);
		cl.def("post_decrement", (class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > (std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>::*)(int)) &std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator--, "C++: std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator--(int) --> class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > >", pybind11::arg(""));
		cl.def("__add__", (class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > (std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>::*)(long) const) &std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator+, "C++: std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator+(long) const --> class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > >", pybind11::arg("__n"));
		cl.def("__iadd__", (class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > & (std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>::*)(long)) &std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator+=, "C++: std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator+=(long) --> class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > &", pybind11::return_value_policy::reference_internal, pybind11::arg("__n"));
		cl.def("__sub__", (class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > (std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>::*)(long) const) &std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator-, "C++: std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator-(long) const --> class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > >", pybind11::arg("__n"));
		cl.def("__isub__", (class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > & (std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>::*)(long)) &std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator-=, "C++: std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator-=(long) --> class std::reverse_iterator<class __gnu_cxx::__normal_iterator<std::string *, class std::vector<std::string, class std::allocator<std::string > > > > &", pybind11::return_value_policy::reference_internal, pybind11::arg("__n"));
		cl.def("__getitem__", (std::string & (std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string> >>::*)(long) const) &std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator[], "C++: std::reverse_iterator<__gnu_cxx::__normal_iterator<std::string *, std::vector<std::string>>>::operator[](long) const --> std::string &", pybind11::return_value_policy::reference_internal, pybind11::arg("__n"));
		cl.def("assign", (struct std::iterator<struct std::random_access_iterator_tag, std::string, long, std::string *, std::string &> & (std::iterator<std::random_access_iterator_tag,std::string,long,std::string *,std::string &>::*)(const struct std::iterator<struct std::random_access_iterator_tag, std::string, long, std::string *, std::string &> &)) &std::iterator<std::random_access_iterator_tag, std::string, long, std::string *, std::string &>::operator=, "C++: std::iterator<std::random_access_iterator_tag, std::string, long, std::string *, std::string &>::operator=(const struct std::iterator<struct std::random_access_iterator_tag, std::string, long, std::string *, std::string &> &) --> struct std::iterator<struct std::random_access_iterator_tag, std::string, long, std::string *, std::string &> &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
	}
}
