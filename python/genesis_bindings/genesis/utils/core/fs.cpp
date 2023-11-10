#include <functional>
#include <genesis/utils/core/fs.hpp>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
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

void bind_genesis_utils_core_fs(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// genesis::utils::file_is_readable(const std::string &, std::string &) file:genesis/utils/core/fs.hpp line:83
	M("genesis::utils").def("file_is_readable", (bool (*)(const std::string &, std::string &)) &genesis::utils::file_is_readable, "Return whether a file is readable, and potentially store the error message.\n\n For this, the file has to exist, and be accessible.\n Another potential error is that too many files are opened already.\n\nC++: genesis::utils::file_is_readable(const std::string &, std::string &) --> bool", pybind11::arg("filename"), pybind11::arg("err_str"));

	// genesis::utils::file_read(const std::string &, bool) file:genesis/utils/core/fs.hpp line:93
	M("genesis::utils").def("file_read", [](const std::string & a0) -> std::string { return genesis::utils::file_read(a0); }, "", pybind11::arg("filename"));
	M("genesis::utils").def("file_read", (std::string (*)(const std::string &, bool)) &genesis::utils::file_read, "Return the contents of a file as a string.\n\n If the parameter  is `true` (default), it is first determined whether the\n file is gzip compressed, and if so, the file is decompressed when reading.\n\n If the file is not readable, the function throws `std::runtime_error`.\n\nC++: genesis::utils::file_read(const std::string &, bool) --> std::string", pybind11::arg("filename"), pybind11::arg("detect_compression"));

	// genesis::utils::file_read_lines(const std::string &, bool) file:genesis/utils/core/fs.hpp line:106
	M("genesis::utils").def("file_read_lines", [](const std::string & a0) -> std::vector<std::string, class std::allocator<std::string > > { return genesis::utils::file_read_lines(a0); }, "", pybind11::arg("filename"));
	M("genesis::utils").def("file_read_lines", (class std::vector<std::string, class std::allocator<std::string > > (*)(const std::string &, bool)) &genesis::utils::file_read_lines, "Return the contents of a file as a vector of strings, one entry for each line.\n\n If the parameter  is `true` (default), it is first determined whether the\n file is gzip compressed, and if so, the file is decompressed when reading.\n\n If the file is not readable, the function throws `std::runtime_error`.\n\nC++: genesis::utils::file_read_lines(const std::string &, bool) --> class std::vector<std::string, class std::allocator<std::string > >", pybind11::arg("filename"), pybind11::arg("detect_compression"));

	// genesis::utils::file_write(const std::string &, const std::string &, bool) file:genesis/utils/core/fs.hpp line:119
	M("genesis::utils").def("file_write", [](const std::string & a0, const std::string & a1) -> void { return genesis::utils::file_write(a0, a1); }, "", pybind11::arg("content"), pybind11::arg("filename"));
	M("genesis::utils").def("file_write", (void (*)(const std::string &, const std::string &, bool)) &genesis::utils::file_write, "Write the content of a string to a file.\n\n If the file cannot be written to, the function throws an exception. Also, by default, if the file\n already exists, an exception is thrown.\n See \n\n\n\n\nC++: genesis::utils::file_write(const std::string &, const std::string &, bool) --> void", pybind11::arg("content"), pybind11::arg("filename"), pybind11::arg("create_dirs"));

	// genesis::utils::file_append(const std::string &, const std::string &, bool) file:genesis/utils/core/fs.hpp line:130
	M("genesis::utils").def("file_append", [](const std::string & a0, const std::string & a1) -> void { return genesis::utils::file_append(a0, a1); }, "", pybind11::arg("content"), pybind11::arg("filename"));
	M("genesis::utils").def("file_append", (void (*)(const std::string &, const std::string &, bool)) &genesis::utils::file_append, "Append the content of a string to a file.\n\n If the file is not writable, the function throws `std::runtime_error`.\n\nC++: genesis::utils::file_append(const std::string &, const std::string &, bool) --> void", pybind11::arg("content"), pybind11::arg("filename"), pybind11::arg("create_dirs"));

	// genesis::utils::is_dir(const std::string &) file:genesis/utils/core/fs.hpp line:146
	M("genesis::utils").def("is_dir", (bool (*)(const std::string &)) &genesis::utils::is_dir, "Return true iff the provided path is a directory.\n\n Internally, this function simply return the value of dir_exists(), as this already does the\n needed check. Thus, it is an alias.\n\nC++: genesis::utils::is_dir(const std::string &) --> bool", pybind11::arg("path"));

	// genesis::utils::dir_exists(const std::string &) file:genesis/utils/core/fs.hpp line:151
	M("genesis::utils").def("dir_exists", (bool (*)(const std::string &)) &genesis::utils::dir_exists, "Return true iff the directory exists.\n\nC++: genesis::utils::dir_exists(const std::string &) --> bool", pybind11::arg("dir"));

	// genesis::utils::dir_create(const std::string &, bool) file:genesis/utils/core/fs.hpp line:160
	M("genesis::utils").def("dir_create", [](const std::string & a0) -> void { return genesis::utils::dir_create(a0); }, "", pybind11::arg("path"));
	M("genesis::utils").def("dir_create", (void (*)(const std::string &, bool)) &genesis::utils::dir_create, "Create a directory.\n\n If the directory already exists, nothing happens.\n If the path exists, but is not a directory, a `std::runtime_error` is thrown.\n If the creation fails for some other reason, also a `std::runtime_error` is thrown.\n\nC++: genesis::utils::dir_create(const std::string &, bool) --> void", pybind11::arg("path"), pybind11::arg("with_parents"));

	// genesis::utils::dir_normalize_path(const std::string &) file:genesis/utils/core/fs.hpp line:165
	M("genesis::utils").def("dir_normalize_path", (std::string (*)(const std::string &)) &genesis::utils::dir_normalize_path, "Normalize a dir name, i.e., make sure that the given path ends with exaclty one slash.\n\nC++: genesis::utils::dir_normalize_path(const std::string &) --> std::string", pybind11::arg("path"));

	// genesis::utils::dir_list_contents(const std::string &, bool, const std::string &) file:genesis/utils/core/fs.hpp line:175
	M("genesis::utils").def("dir_list_contents", [](const std::string & a0) -> std::vector<std::string, class std::allocator<std::string > > { return genesis::utils::dir_list_contents(a0); }, "", pybind11::arg("dir"));
	M("genesis::utils").def("dir_list_contents", [](const std::string & a0, bool const & a1) -> std::vector<std::string, class std::allocator<std::string > > { return genesis::utils::dir_list_contents(a0, a1); }, "", pybind11::arg("dir"), pybind11::arg("full_path"));
	M("genesis::utils").def("dir_list_contents", (class std::vector<std::string, class std::allocator<std::string > > (*)(const std::string &, bool, const std::string &)) &genesis::utils::dir_list_contents, "Get a list of files and directories in a directory.\n\n If  is set to `true`, the path of the provided  is prepended to the resulting\n list. If a non-empy  is provided, file names are filtered by this regular expression.\n\n If the directory is not readable, the function throws `std::runtime_error`.\n\nC++: genesis::utils::dir_list_contents(const std::string &, bool, const std::string &) --> class std::vector<std::string, class std::allocator<std::string > >", pybind11::arg("dir"), pybind11::arg("full_path"), pybind11::arg("regex"));

	// genesis::utils::dir_list_files(const std::string &, bool, const std::string &) file:genesis/utils/core/fs.hpp line:187
	M("genesis::utils").def("dir_list_files", [](const std::string & a0) -> std::vector<std::string, class std::allocator<std::string > > { return genesis::utils::dir_list_files(a0); }, "", pybind11::arg("dir"));
	M("genesis::utils").def("dir_list_files", [](const std::string & a0, bool const & a1) -> std::vector<std::string, class std::allocator<std::string > > { return genesis::utils::dir_list_files(a0, a1); }, "", pybind11::arg("dir"), pybind11::arg("full_path"));
	M("genesis::utils").def("dir_list_files", (class std::vector<std::string, class std::allocator<std::string > > (*)(const std::string &, bool, const std::string &)) &genesis::utils::dir_list_files, "Get a list of files in a directory.\n\n Behaves the same as dir_list_contents(), except tat only files are listed (i.e., no directories).\n See there for an explanation of the arguments.\n\nC++: genesis::utils::dir_list_files(const std::string &, bool, const std::string &) --> class std::vector<std::string, class std::allocator<std::string > >", pybind11::arg("dir"), pybind11::arg("full_path"), pybind11::arg("regex"));

	// genesis::utils::dir_list_directories(const std::string &, bool, const std::string &) file:genesis/utils/core/fs.hpp line:199
	M("genesis::utils").def("dir_list_directories", [](const std::string & a0) -> std::vector<std::string, class std::allocator<std::string > > { return genesis::utils::dir_list_directories(a0); }, "", pybind11::arg("dir"));
	M("genesis::utils").def("dir_list_directories", [](const std::string & a0, bool const & a1) -> std::vector<std::string, class std::allocator<std::string > > { return genesis::utils::dir_list_directories(a0, a1); }, "", pybind11::arg("dir"), pybind11::arg("full_path"));
	M("genesis::utils").def("dir_list_directories", (class std::vector<std::string, class std::allocator<std::string > > (*)(const std::string &, bool, const std::string &)) &genesis::utils::dir_list_directories, "Get a list of directories in a directory.\n\n Behaves the same as dir_list_contents(), except tat only directories are listed (i.e., no files).\n See there for an explanation of the arguments.\n\nC++: genesis::utils::dir_list_directories(const std::string &, bool, const std::string &) --> class std::vector<std::string, class std::allocator<std::string > >", pybind11::arg("dir"), pybind11::arg("full_path"), pybind11::arg("regex"));

	// genesis::utils::current_path() file:genesis/utils/core/fs.hpp line:217
	M("genesis::utils").def("current_path", (std::string (*)()) &genesis::utils::current_path, "Return the current (working) directory, simiar to getcwd().\n\n The function behaves similar to getcwd(). The path is returned with a trailing slash,\n for conveniently apppending file names to it.\n\n As this function changes the directory in the process, it is not thread safe.\n\nC++: genesis::utils::current_path() --> std::string");

	// genesis::utils::real_path(const std::string &, bool) file:genesis/utils/core/fs.hpp line:227
	M("genesis::utils").def("real_path", [](const std::string & a0) -> std::string { return genesis::utils::real_path(a0); }, "", pybind11::arg("path"));
	M("genesis::utils").def("real_path", (std::string (*)(const std::string &, bool)) &genesis::utils::real_path, "Return the real path of a file or directory, similar to realpath().\n\n The function behaves similar to realpath(), but (hopefully) offers better protability\n and error handling (long paths etc).\n\n As this function changes the directory in the process, it is not thread safe.\n\nC++: genesis::utils::real_path(const std::string &, bool) --> std::string", pybind11::arg("path"), pybind11::arg("resolve_link"));

	// genesis::utils::file_info(const std::string &) file:genesis/utils/core/fs.hpp line:236
	M("genesis::utils").def("file_info", (class std::unordered_map<std::string, std::string, struct std::hash<std::string>, struct std::equal_to<std::string >, class std::allocator<struct std::pair<const std::string, std::string > > > (*)(const std::string &)) &genesis::utils::file_info, "Return information about a file.\n\nC++: genesis::utils::file_info(const std::string &) --> class std::unordered_map<std::string, std::string, struct std::hash<std::string>, struct std::equal_to<std::string >, class std::allocator<struct std::pair<const std::string, std::string > > >", pybind11::arg("filename"));

	// genesis::utils::file_size(const std::string &) file:genesis/utils/core/fs.hpp line:241
	M("genesis::utils").def("file_size", (unsigned long (*)(const std::string &)) &genesis::utils::file_size, "Return the size of a file.\n\nC++: genesis::utils::file_size(const std::string &) --> unsigned long", pybind11::arg("filename"));

	// genesis::utils::file_path(const std::string &) file:genesis/utils/core/fs.hpp line:249
	M("genesis::utils").def("file_path", (std::string (*)(const std::string &)) &genesis::utils::file_path, "Return the path leading to a file.\n\n Does not resolve the path. Simply splits at the last directory separator.\n If there is no directory separator, it returns an empty string.\n\nC++: genesis::utils::file_path(const std::string &) --> std::string", pybind11::arg("filename"));

	// genesis::utils::file_basename(const std::string &) file:genesis/utils/core/fs.hpp line:254
	M("genesis::utils").def("file_basename", (std::string (*)(const std::string &)) &genesis::utils::file_basename, "Remove directory name from file name if present.\n\nC++: genesis::utils::file_basename(const std::string &) --> std::string", pybind11::arg("filename"));

	// genesis::utils::file_basename(const std::string &, const class std::vector<std::string, class std::allocator<std::string > > &) file:genesis/utils/core/fs.hpp line:273
	M("genesis::utils").def("file_basename", (std::string (*)(const std::string &, const class std::vector<std::string, class std::allocator<std::string > > &)) &genesis::utils::file_basename, "Remove the directory name from a file name if present, and remove a list of given extensions.\n\n After obtaining the file basename (the final rightmost segment of the file path after the last\n directory seperator `/`), the  are also removed from the file name.\n The given list is iterated regularly, and removed (from right to left, as these are suffixes)\n from the file name, if present.\n\n For example:\n\n     std::string path = \"/path/to/filename.txt.gz\";\n     std::cout << file_basename( path, { \".gz\", \".txt\" }) << \"\";\n\n yields \"filename\". This is useful for example to remove a set of known extensions for a file\n type, for clean user output. Not all extensions have to be present; those that are not, are\n simply skipped.\n\nC++: genesis::utils::file_basename(const std::string &, const class std::vector<std::string, class std::allocator<std::string > > &) --> std::string", pybind11::arg("filename"), pybind11::arg("remove_extensions"));

	// genesis::utils::file_filename(const std::string &) file:genesis/utils/core/fs.hpp line:284
	M("genesis::utils").def("file_filename", (std::string (*)(const std::string &)) &genesis::utils::file_filename, "Remove extension if present.\n\n Caveat: Does not remove the path. So, if the filename itself does not contain an extension\n separator \".\", but the path does, this will yield an unwanted result. Call file_basename() first.\n\nC++: genesis::utils::file_filename(const std::string &) --> std::string", pybind11::arg("filename"));

	// genesis::utils::file_extension(const std::string &) file:genesis/utils/core/fs.hpp line:291
	M("genesis::utils").def("file_extension", (std::string (*)(const std::string &)) &genesis::utils::file_extension, "Return the extension name of a file.\n\n Also see file_filename().\n\nC++: genesis::utils::file_extension(const std::string &) --> std::string", pybind11::arg("filename"));

	// genesis::utils::is_valid_filename(const std::string &) file:genesis/utils/core/fs.hpp line:317
	M("genesis::utils").def("is_valid_filename", (bool (*)(const std::string &)) &genesis::utils::is_valid_filename, "Check whether a file name is valid.\n\n Validating filenames depends on the operating system and file system of the disk. Thus, this is\n usually not an easy task. This function only checks some basics and is meant to catch the most\n common problems.\n\n The function is meant to be called on the file name itself, without the directory path leading\n to it. File extensions are allowed. Thus, you might need to call file_basename() before in order\n to get the file name without the path.\n\n Invalid filenames are:\n\n   * Those with spaces at the beginning or end, or only consisting of spaces (or empty).\n   * Those which contain any of the chars `< > : \" \\ / | ? *`.\n   * Those which contain any non-printable character, as determined via isprint().\n\n This might be too converative for some system, or allow too much for others. It however should\n return true for filenames that work on most systems.\n\nC++: genesis::utils::is_valid_filename(const std::string &) --> bool", pybind11::arg("filename"));

	// genesis::utils::sanitize_filename(const std::string &) file:genesis/utils/core/fs.hpp line:340
	M("genesis::utils").def("sanitize_filename", (std::string (*)(const std::string &)) &genesis::utils::sanitize_filename, "Remove or replace all invalid parts of a filename.\n\n Similar to is_valid_filename(), this function is not meant to be an ultimate solution to valid\n filenames. See there for details.\n\n The function is meant to be called on the file name itself, without the directory path leading\n to it. File extensions are allowed. Thus, you might need to call file_basename() before in order\n to get the file name without the path.\n\n This function does the following:\n\n   * All non-printable characters are removed.\n   * Spaces at the beginning and end are removed.\n   * All invalid chars are replaced by an underscore. See is_valid_filename() for a list of those\n     chars.\n\n If after this procedure the filename is empty, an exception is thrown. This is meant to save the\n user from checking this, or from running into trouble when trying to write to this \"file\" -\n because an empty filename will point to a directory name.\n\nC++: genesis::utils::sanitize_filename(const std::string &) --> std::string", pybind11::arg("filename"));

}
