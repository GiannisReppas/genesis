#include <genesis/utils/io/base_output_target.hpp>
#include <genesis/utils/io/gzip_block_ostream.hpp>
#include <genesis/utils/io/gzip_output_target.hpp>
#include <genesis/utils/io/gzip_stream.hpp>
#include <genesis/utils/io/output_target.hpp>
#include <genesis/utils/io/stream_output_target.hpp>
#include <genesis/utils/io/string_output_target.hpp>
#include <ios>
#include <iterator>
#include <locale>
#include <memory>
#include <ostream>
#include <sstream> // __str__
#include <streambuf>
#include <string>

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

void bind_genesis_utils_io_gzip_block_ostream(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // genesis::utils::GzipBlockOStream file:genesis/utils/io/gzip_block_ostream.hpp line:90
		pybind11::class_<genesis::utils::GzipBlockOStream, std::shared_ptr<genesis::utils::GzipBlockOStream>, std::ostream> cl(M("genesis::utils"), "GzipBlockOStream", "Output stream that writes blocks of gzip-compressed data to an underlying wrapped stream,\n using parallel compression.\n\n The gzip format specifies that concatenated blocks of gzip-compressed data (including the gzip\n header) are still valid gzip files, and are equivalent to concatenating the decompressed data.\n This is for example used in compressed vcf files (.vcf.gz, Variant Calling Format) to achieve\n random access into compressed data, by maintaining an index table of offsets to the beginning\n of individual compressed blocks.\n\n We here use a similar technique to achieve a compression speedup by using parallel threads\n on different gzip blocks. This gives almost linear speedup, at the cost of ~3% increase in\n resulting file size due to the additional gzip headers of each block. This downside can be\n alleivated by using larger blocks though. By default, we use 64kB blocks.\n\n Exemplary usage:\n\n     // Wrapped output stream to write to. Use binary mode, so that compressed output works.\n     std::ofstream ofile;\n     ofile.open( \"path/to/test.txt.gz\", std::ios_base::binary );\n\n     // Prepare stream\n     GzipBlockOStream ostr( ofile );\n\n     // Write data to stream\n     ostr << \"some data\";\n\n By default, the number of threads is determined using the number of available threads in an\n OpenMP parallel region. If set manually via  to a value other than 0, we recommend\n to use not more than the hardware concurrency, or fewer, if at the same time compressed data is\n read in some other part of the program, or other computation-heavy work is done.\n\n Furthermore, note that some file managers might not display the original (uncompressed) file size\n correctly when viewing the resulting gz file, as they might use only the size of one block\n instead of the full resulting uncompressed file size. This should not affect decompression or any\n other downstream processes though. As this class is a stream, we usually do not know beforehand\n how lare the resulting file will be, so there is not much we can do about this.\n\n The class could also be extended in the future to achieve indexing similar to compressed vcf.\n NB: We have not yet tested compatibility with the vcf format, as they might employ additional\n tricks to achieve their goals.");
		cl.def( pybind11::init( [](std::ostream & a0){ return new genesis::utils::GzipBlockOStream(a0); } ), "doc" , pybind11::arg("os"));
		cl.def( pybind11::init( [](std::ostream & a0, unsigned long const & a1){ return new genesis::utils::GzipBlockOStream(a0, a1); } ), "doc" , pybind11::arg("os"), pybind11::arg("block_size"));
		cl.def( pybind11::init( [](std::ostream & a0, unsigned long const & a1, enum genesis::utils::GzipCompressionLevel const & a2){ return new genesis::utils::GzipBlockOStream(a0, a1, a2); } ), "doc" , pybind11::arg("os"), pybind11::arg("block_size"), pybind11::arg("compression_level"));
		cl.def( pybind11::init<std::ostream &, unsigned long, enum genesis::utils::GzipCompressionLevel, unsigned long>(), pybind11::arg("os"), pybind11::arg("block_size"), pybind11::arg("compression_level"), pybind11::arg("num_threads") );

		cl.def( pybind11::init( [](class std::basic_streambuf<char> * a0){ return new genesis::utils::GzipBlockOStream(a0); } ), "doc" , pybind11::arg("sbuf_p"));
		cl.def( pybind11::init( [](class std::basic_streambuf<char> * a0, unsigned long const & a1){ return new genesis::utils::GzipBlockOStream(a0, a1); } ), "doc" , pybind11::arg("sbuf_p"), pybind11::arg("block_size"));
		cl.def( pybind11::init( [](class std::basic_streambuf<char> * a0, unsigned long const & a1, enum genesis::utils::GzipCompressionLevel const & a2){ return new genesis::utils::GzipBlockOStream(a0, a1, a2); } ), "doc" , pybind11::arg("sbuf_p"), pybind11::arg("block_size"), pybind11::arg("compression_level"));
		cl.def( pybind11::init<class std::basic_streambuf<char> *, unsigned long, enum genesis::utils::GzipCompressionLevel, unsigned long>(), pybind11::arg("sbuf_p"), pybind11::arg("block_size"), pybind11::arg("compression_level"), pybind11::arg("num_threads") );

	}
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

}
