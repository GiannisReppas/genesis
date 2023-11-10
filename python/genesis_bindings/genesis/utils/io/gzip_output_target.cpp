#include <genesis/utils/io/base_output_target.hpp>
#include <genesis/utils/io/gzip_output_target.hpp>
#include <genesis/utils/io/gzip_stream.hpp>
#include <genesis/utils/io/output_target.hpp>
#include <genesis/utils/io/stream_output_target.hpp>
#include <genesis/utils/io/string_output_target.hpp>
#include <genesis/utils/math/common.hpp>
#include <ios>
#include <iterator>
#include <locale>
#include <memory>
#include <ostream>
#include <sstream> // __str__
#include <streambuf>
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

void bind_genesis_utils_io_gzip_output_target(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // genesis::utils::GzipOutputTarget file:genesis/utils/io/gzip_output_target.hpp line:61
		pybind11::class_<genesis::utils::GzipOutputTarget, std::shared_ptr<genesis::utils::GzipOutputTarget>, genesis::utils::BaseOutputTarget> cl(M("genesis::utils"), "GzipOutputTarget", "Output target for writing byte data to a gzip/zlib-compressed target.\n\n This output target is a wrapper that takes some other output target\n (FileOutputTarget, StringOutputTarget, StreamOutputTarget, etc),\n and compresses using the gzip format on the fly while writing to that other target.\n\n The class can be moved, but not copied, because of the internal state that is kept for\n compression, and which would mess up the output if copied.");
		cl.def( pybind11::init( [](class std::shared_ptr<class genesis::utils::BaseOutputTarget> const & a0){ return new genesis::utils::GzipOutputTarget(a0); } ), "doc" , pybind11::arg("output_target"));
		cl.def( pybind11::init<class std::shared_ptr<class genesis::utils::BaseOutputTarget>, enum genesis::utils::GzipCompressionLevel>(), pybind11::arg("output_target"), pybind11::arg("compression_level") );

	}
	{ // genesis::utils::GzipBlockOutputTarget file:genesis/utils/io/gzip_output_target.hpp line:174
		pybind11::class_<genesis::utils::GzipBlockOutputTarget, std::shared_ptr<genesis::utils::GzipBlockOutputTarget>, genesis::utils::BaseOutputTarget> cl(M("genesis::utils"), "GzipBlockOutputTarget", "Output target for writing byte data to a gzip-compressed target in blocks of gzip data.\n\n This output target is a wrapper that takes some other output target\n (FileOutputTarget, StringOutputTarget, StreamOutputTarget, etc),\n and compresses using the gzip format on the fly while writing to that other target.\n\n Using gzip blocks allows us to compress in parallel using multiple threads. Furthermore,\n it should allow for downstream indexing and random access into the compressed file, although\n we currently have not tested this. See the GzipBlockOStream class for details on gzip block\n compression.\n\n The class can be moved, but not copied, because of the internal state that is kept for\n compression, and which would mess up the output if copied.\n\n \n GzipBlockOStream\n \n\n to_gzip_block_file");
		cl.def( pybind11::init( [](class std::shared_ptr<class genesis::utils::BaseOutputTarget> const & a0){ return new genesis::utils::GzipBlockOutputTarget(a0); } ), "doc" , pybind11::arg("output_target"));
		cl.def( pybind11::init( [](class std::shared_ptr<class genesis::utils::BaseOutputTarget> const & a0, unsigned long const & a1){ return new genesis::utils::GzipBlockOutputTarget(a0, a1); } ), "doc" , pybind11::arg("output_target"), pybind11::arg("block_size"));
		cl.def( pybind11::init( [](class std::shared_ptr<class genesis::utils::BaseOutputTarget> const & a0, unsigned long const & a1, enum genesis::utils::GzipCompressionLevel const & a2){ return new genesis::utils::GzipBlockOutputTarget(a0, a1, a2); } ), "doc" , pybind11::arg("output_target"), pybind11::arg("block_size"), pybind11::arg("compression_level"));
		cl.def( pybind11::init<class std::shared_ptr<class genesis::utils::BaseOutputTarget>, unsigned long, enum genesis::utils::GzipCompressionLevel, unsigned long>(), pybind11::arg("output_target"), pybind11::arg("block_size"), pybind11::arg("compression_level"), pybind11::arg("num_threads") );

	}
	{ // genesis::utils::StreamOutputTarget file:genesis/utils/io/stream_output_target.hpp line:52
		pybind11::class_<genesis::utils::StreamOutputTarget, std::shared_ptr<genesis::utils::StreamOutputTarget>, genesis::utils::BaseOutputTarget> cl(M("genesis::utils"), "StreamOutputTarget", "Output target for writing data to a stream.\n\n The stream that is written to is kept by reference in this class. Hence, it has to stay\n alive for the duration of the data writing process where this class is used.");
		cl.def( pybind11::init<std::ostream &>(), pybind11::arg("target") );

		cl.def( pybind11::init( [](genesis::utils::StreamOutputTarget const &o){ return new genesis::utils::StreamOutputTarget(o); } ) );
		cl.def("assign", (class genesis::utils::StreamOutputTarget & (genesis::utils::StreamOutputTarget::*)(const class genesis::utils::StreamOutputTarget &)) &genesis::utils::StreamOutputTarget::operator=, "C++: genesis::utils::StreamOutputTarget::operator=(const class genesis::utils::StreamOutputTarget &) --> class genesis::utils::StreamOutputTarget &", pybind11::return_value_policy::reference_internal, pybind11::arg(""));
	}
	{ // genesis::utils::StringOutputTarget file:genesis/utils/io/string_output_target.hpp line:54
		pybind11::class_<genesis::utils::StringOutputTarget, std::shared_ptr<genesis::utils::StringOutputTarget>, genesis::utils::BaseOutputTarget> cl(M("genesis::utils"), "StringOutputTarget", "Output target for writing data to a string.\n\n The string that is written to is kept by reference in this class. Hence, it has to stay\n alive for the duration of the data writing process where this class is used.\n Internally, the data is buffered in a stringstream, and only written to the string\n on destruction of this class.");
		cl.def( pybind11::init<std::string &>(), pybind11::arg("target") );

	}
	// genesis::utils::to_file(const std::string &, enum genesis::utils::GzipCompressionLevel, bool) file:genesis/utils/io/output_target.hpp line:80
	M("genesis::utils").def("to_file", [](const std::string & a0, enum genesis::utils::GzipCompressionLevel const & a1) -> std::shared_ptr<class genesis::utils::BaseOutputTarget> { return genesis::utils::to_file(a0, a1); }, "", pybind11::arg("file_name"), pybind11::arg("compression_level"));
	M("genesis::utils").def("to_file", (class std::shared_ptr<class genesis::utils::BaseOutputTarget> (*)(const std::string &, enum genesis::utils::GzipCompressionLevel, bool)) &genesis::utils::to_file, "Obtain an output target for writing to a file.\n\n The output target returned from this function can be used in the writer classes, e.g.,\n placement::JplaceWriter or sequence::FastaWriter.\n\n If  is set to a compression level other than\n ::GzipCompressionLevel::kNoCompression, the output is compressed using\n gzip. We recommend to use ::GzipCompressionLevel::kDefaultCompression%.\n\n Furthermore, if  is set to `true` (default), the file name is\n adjusted according to the compression setting: If compression is used, the file name\n is appended by the `.gz` extension, if this is not alreay present. (For completeness,\n the oppositve also works: If the file name ends in `.gz`, but no compression is chosen, the `.gz`\n extension is removed.)\n\n If the file cannot be written to, the function throws an exception.\n Also, by default, if the file already exists, an exception is thrown. See\n \n\n\n\n\n\n\n\nC++: genesis::utils::to_file(const std::string &, enum genesis::utils::GzipCompressionLevel, bool) --> class std::shared_ptr<class genesis::utils::BaseOutputTarget>", pybind11::arg("file_name"), pybind11::arg("compression_level"), pybind11::arg("auto_adjust_filename"));

	// genesis::utils::to_file(const std::string &, enum std::_Ios_Openmode) file:genesis/utils/io/output_target.hpp line:116
	M("genesis::utils").def("to_file", [](const std::string & a0) -> std::shared_ptr<class genesis::utils::BaseOutputTarget> { return genesis::utils::to_file(a0); }, "", pybind11::arg("file_name"));
	M("genesis::utils").def("to_file", (class std::shared_ptr<class genesis::utils::BaseOutputTarget> (*)(const std::string &, enum std::_Ios_Openmode)) &genesis::utils::to_file, "Obtain an output target for writing to a file, using a specific output mode.\n\n The output target returned from this function can be used in the writer classes, e.g.,\n placement::JplaceWriter or sequence::FastaWriter.\n\n This version of the function allows to explicitly set the `openmode`, which is for example useful\n to append to an existing file, or to open it in binary mode.\n\nC++: genesis::utils::to_file(const std::string &, enum std::_Ios_Openmode) --> class std::shared_ptr<class genesis::utils::BaseOutputTarget>", pybind11::arg("file_name"), pybind11::arg("mode"));

	// genesis::utils::to_gzip_block_file(const std::string &, unsigned long, enum genesis::utils::GzipCompressionLevel, unsigned long, bool) file:genesis/utils/io/output_target.hpp line:136
	M("genesis::utils").def("to_gzip_block_file", [](const std::string & a0) -> std::shared_ptr<class genesis::utils::BaseOutputTarget> { return genesis::utils::to_gzip_block_file(a0); }, "", pybind11::arg("file_name"));
	M("genesis::utils").def("to_gzip_block_file", [](const std::string & a0, unsigned long const & a1) -> std::shared_ptr<class genesis::utils::BaseOutputTarget> { return genesis::utils::to_gzip_block_file(a0, a1); }, "", pybind11::arg("file_name"), pybind11::arg("block_size"));
	M("genesis::utils").def("to_gzip_block_file", [](const std::string & a0, unsigned long const & a1, enum genesis::utils::GzipCompressionLevel const & a2) -> std::shared_ptr<class genesis::utils::BaseOutputTarget> { return genesis::utils::to_gzip_block_file(a0, a1, a2); }, "", pybind11::arg("file_name"), pybind11::arg("block_size"), pybind11::arg("compression_level"));
	M("genesis::utils").def("to_gzip_block_file", [](const std::string & a0, unsigned long const & a1, enum genesis::utils::GzipCompressionLevel const & a2, unsigned long const & a3) -> std::shared_ptr<class genesis::utils::BaseOutputTarget> { return genesis::utils::to_gzip_block_file(a0, a1, a2, a3); }, "", pybind11::arg("file_name"), pybind11::arg("block_size"), pybind11::arg("compression_level"), pybind11::arg("num_threads"));
	M("genesis::utils").def("to_gzip_block_file", (class std::shared_ptr<class genesis::utils::BaseOutputTarget> (*)(const std::string &, unsigned long, enum genesis::utils::GzipCompressionLevel, unsigned long, bool)) &genesis::utils::to_gzip_block_file, "Obtain an output target for writing gzip block compressed data to a file.\n\n This output target uses multithreaded gzip compression by block-compressing chunks of data.\n See GzipBlockOStream for an explanation and more details on this technique and the parameters\n offered here.\n\n For general details on using this output target for writing data, see to_file().\n\n \n GzipBlockOStream\n \n\n GzipBlockOutputTarget\n \n\n to_file()\n\nC++: genesis::utils::to_gzip_block_file(const std::string &, unsigned long, enum genesis::utils::GzipCompressionLevel, unsigned long, bool) --> class std::shared_ptr<class genesis::utils::BaseOutputTarget>", pybind11::arg("file_name"), pybind11::arg("block_size"), pybind11::arg("compression_level"), pybind11::arg("num_threads"), pybind11::arg("auto_adjust_filename"));

	// genesis::utils::to_stream(std::ostream &, enum genesis::utils::GzipCompressionLevel) file:genesis/utils/io/output_target.hpp line:176
	M("genesis::utils").def("to_stream", [](std::ostream & a0) -> std::shared_ptr<class genesis::utils::BaseOutputTarget> { return genesis::utils::to_stream(a0); }, "", pybind11::arg("target_stream"));
	M("genesis::utils").def("to_stream", (class std::shared_ptr<class genesis::utils::BaseOutputTarget> (*)(std::ostream &, enum genesis::utils::GzipCompressionLevel)) &genesis::utils::to_stream, "Obtain an output target for writing to a stream.\n\n The output target returned from this function can be used in the writer classes, e.g.,\n placement::JplaceWriter or sequence::FastaWriter.\n\n If  is set to a compression level other than ::GzipCompressionLevel::kNoCompression\n (which is the default, which means, no compression by default), the output is compressed using\n gzip. In that case, it is recommended that the  uses `std::ios_base::binary`\n when opening the stream.\n\nC++: genesis::utils::to_stream(std::ostream &, enum genesis::utils::GzipCompressionLevel) --> class std::shared_ptr<class genesis::utils::BaseOutputTarget>", pybind11::arg("target_stream"), pybind11::arg("compression_level"));

	// genesis::utils::to_string(std::string &) file:genesis/utils/io/output_target.hpp line:195
	M("genesis::utils").def("to_string", (class std::shared_ptr<class genesis::utils::BaseOutputTarget> (*)(std::string &)) &genesis::utils::to_string, "Obtain an output target for writing to a string.\n\n The output target returned from this function can be used in the writer classes, e.g.,\n placement::JplaceWriter or sequence::FastaWriter.\n\nC++: genesis::utils::to_string(std::string &) --> class std::shared_ptr<class genesis::utils::BaseOutputTarget>", pybind11::arg("target_string"));

	// genesis::utils::circumference(double) file:genesis/utils/math/common.hpp line:57
	M("genesis::utils").def("circumference", (double (*)(double)) &genesis::utils::circumference, "C++: genesis::utils::circumference(double) --> double", pybind11::arg("radius"));

	// genesis::utils::almost_equal_relative(double, double, double) file:genesis/utils/math/common.hpp line:157
	M("genesis::utils").def("almost_equal_relative", [](double const & a0, double const & a1) -> bool { return genesis::utils::almost_equal_relative(a0, a1); }, "", pybind11::arg("lhs"), pybind11::arg("rhs"));
	M("genesis::utils").def("almost_equal_relative", (bool (*)(double, double, double)) &genesis::utils::almost_equal_relative, "Check whether two doubles are almost equal, using a relative epsilon to compare them.\n\nC++: genesis::utils::almost_equal_relative(double, double, double) --> bool", pybind11::arg("lhs"), pybind11::arg("rhs"), pybind11::arg("max_rel_diff"));

	// genesis::utils::round_to(double, unsigned long) file:genesis/utils/math/common.hpp line:175
	M("genesis::utils").def("round_to", (double (*)(double, unsigned long)) &genesis::utils::round_to, "Retun the value of `x`, rounded to the decimal digit given by `accuracy_order`.\n\nC++: genesis::utils::round_to(double, unsigned long) --> double", pybind11::arg("x"), pybind11::arg("accuracy_order"));

	// genesis::utils::int_pow(unsigned long, unsigned long) file:genesis/utils/math/common.hpp line:191
	M("genesis::utils").def("int_pow", (unsigned long (*)(unsigned long, unsigned long)) &genesis::utils::int_pow, "Calculate the power `base^exp` for positive integer values.\n\n Remark: This overflows quite easily. The function does not check whether the desired power\n actually fits within `size_t`. Use is_valid_int_pow() to check for this first.\n\n Rationale for this function: One could argue that int powers are not really useful, particularly\n because of the fast overflow. However, using doubles leads to rounding errors, at least for\n bigger numbers. So, within the valid range, this function is more accurate. Also, it is faster.\n\nC++: genesis::utils::int_pow(unsigned long, unsigned long) --> unsigned long", pybind11::arg("base"), pybind11::arg("exp"));

	// genesis::utils::is_valid_int_pow(unsigned long, unsigned long) file:genesis/utils/math/common.hpp line:211
	M("genesis::utils").def("is_valid_int_pow", (bool (*)(unsigned long, unsigned long)) &genesis::utils::is_valid_int_pow, "Return whether the given power can be stored within a `size_t`.\n\n Use int_pow() to calculate the actual value of the power.\n\nC++: genesis::utils::is_valid_int_pow(unsigned long, unsigned long) --> bool", pybind11::arg("base"), pybind11::arg("exp"));

	// genesis::utils::squared(double) file:genesis/utils/math/common.hpp line:223
	M("genesis::utils").def("squared", (double (*)(double)) &genesis::utils::squared, "Square of a number.\n\n Simply \n, but faster than `std::pow` for the low exponent. Meant as an abbreviation\n where the argument is not already a variable, e.g., `squared( x - 1.0 )`,\n without the need to store the intermediate argument term.\n\nC++: genesis::utils::squared(double) --> double", pybind11::arg("x"));

	// genesis::utils::cubed(double) file:genesis/utils/math/common.hpp line:235
	M("genesis::utils").def("cubed", (double (*)(double)) &genesis::utils::cubed, "Cube of a number.\n\n Simply \n, but faster than `std::pow` for the low exponent. Meant as an abbreviation\n where the argument is not already a variable, e.g., `cubed( x - 1.0 )`,\n without the need to store the intermediate argument term.\n\nC++: genesis::utils::cubed(double) --> double", pybind11::arg("x"));

	// genesis::utils::finite_pairs(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) file:genesis/utils/math/common.hpp line:252
	M("genesis::utils").def("finite_pairs", (struct std::pair<class std::vector<double, class std::allocator<double> >, class std::vector<double, class std::allocator<double> > > (*)(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >)) &genesis::utils::finite_pairs<__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >,__gnu_cxx::__normal_iterator<const double *, std::vector<double, std::allocator<double> > >>, "C++: genesis::utils::finite_pairs(class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >, class __gnu_cxx::__normal_iterator<const double *, class std::vector<double, class std::allocator<double> > >) --> struct std::pair<class std::vector<double, class std::allocator<double> >, class std::vector<double, class std::allocator<double> > >", pybind11::arg("first_a"), pybind11::arg("last_a"), pybind11::arg("first_b"), pybind11::arg("last_b"));

}
