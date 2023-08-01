#include <genesis/utils/core/fs.hpp>
#include <genesis/utils/core/logging.hpp>
#include <ios>
#include <iterator>
#include <memory>
#include <ostream>
#include <sstream>
#include <sstream> // __str__
#include <streambuf>
#include <string>

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

void bind_genesis_utils_core_logging(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// genesis::utils::logging_progress_value(long) file:genesis/utils/core/logging.hpp line:179
	M("genesis::utils").def("logging_progress_value", []() -> long { return genesis::utils::logging_progress_value(); }, "");
	M("genesis::utils").def("logging_progress_value", (long (*)(long)) &genesis::utils::logging_progress_value, "Hack function to make sure that the value arugment in #LOG_PROG is only evaluated once.\n\n Without this function, #LOG_PROG would include two appearances of its variable `value`, which\n means that a statement like\n\n     LOG_PROG(++i, n) << \"of progress.\";\n\n would lead to a double evaluation of the increment statement `++i`. That is not intended, thus\n we need this hack function.\n\nC++: genesis::utils::logging_progress_value(long) --> long", pybind11::arg("value"));

	{ // genesis::utils::LoggingDetails file:genesis/utils/core/logging.hpp line:267
		pybind11::class_<genesis::utils::LoggingDetails, std::shared_ptr<genesis::utils::LoggingDetails>> cl(M("genesis::utils"), "LoggingDetails", "POD stuct containing the settings for which information is included\n with each logging message.\n\n The details are activated via accessing the static variable of the\n Logging class:\n\n     Logging::details.level = true;\n\n All active details are prepended to the actual log message and\n separated by spaces (execpt file and line, they are separated by a\n colon). Their order is fixed.\n\n A message with all details activates looks like this\n\n     0003 2014-10-28 11:40:47 0.001859 0.000103 src/main/main.cc:28 (int main (int argc, char* argv[])) INFO Hello World.\n\n It was the third message being logged in this run of the program, at\n a date and time, 0.001859 sec after the program started and 0.000103\n sec after the last log message. It was called from main.cc line 28 in function main\n and has LoggingLevel Info.");
		cl.def( pybind11::init( [](){ return new genesis::utils::LoggingDetails(); } ) );
		cl.def( pybind11::init<bool, bool, bool, bool, bool, bool, bool, bool, bool>(), pybind11::arg("v_count"), pybind11::arg("v_date"), pybind11::arg("v_time"), pybind11::arg("v_runtime"), pybind11::arg("v_rundiff"), pybind11::arg("v_file"), pybind11::arg("v_line"), pybind11::arg("v_function"), pybind11::arg("v_level") );

		cl.def( pybind11::init( [](genesis::utils::LoggingDetails const &o){ return new genesis::utils::LoggingDetails(o); } ) );
		cl.def_readwrite("count", &genesis::utils::LoggingDetails::count);
		cl.def_readwrite("date", &genesis::utils::LoggingDetails::date);
		cl.def_readwrite("time", &genesis::utils::LoggingDetails::time);
		cl.def_readwrite("runtime", &genesis::utils::LoggingDetails::runtime);
		cl.def_readwrite("rundiff", &genesis::utils::LoggingDetails::rundiff);
		cl.def_readwrite("file", &genesis::utils::LoggingDetails::file);
		cl.def_readwrite("line", &genesis::utils::LoggingDetails::line);
		cl.def_readwrite("function", &genesis::utils::LoggingDetails::function);
		cl.def_readwrite("level", &genesis::utils::LoggingDetails::level);
	}
	{ // genesis::utils::Logging file:genesis/utils/core/logging.hpp line:386
		pybind11::class_<genesis::utils::Logging, std::shared_ptr<genesis::utils::Logging>> cl(M("genesis::utils"), "Logging", "%Logging class with easy and fast usage.\n\n The basic usage of this class is to invoke the macros for the different types\n of log messages and send a stream of messages to them:\n\n     LOG_DBG << \"you are here\";\n     LOG_ERR << \"there was an error: \" << 42;\n\n The provided types of macros are: #LOG_ERR, #LOG_WARN, #LOG_INFO,\n #LOG_DBG, #LOG_DBG1, #LOG_DBG2, #LOG_DBG3, #LOG_DBG4 for all levels of\n logging explained in LoggingLevel.\n\n The details that are logged with each message can be changed via accessing\n Logging::details -- see LoggingDetails for more on that.\n\n In order to use this class, at least one output stream has to be added first\n by invoking either AddOutputStream or AddOutputFile.\n\n The depths of logging can be changed in order to reduce the amount of written\n messages. First, at compile time the macro constant LOG_LEVEL_MAX can be set\n (e.g. in the Makefile) to the highest level that shall be logged. All log\n invoakations with a higher level are never called, and moreover will be\n pruned from the code by most compilers completetly. This makes the log class\n fast -- instead of deleting all log invokations by hand, it is sufficient to\n set the constant to a low level.\n Second, the depths of logging can be changed dynamically at run time by\n setting Logging::max_level to the desired value. Of course, this value\n cannot be higher than LOG_LEVEL_MAX, because those logs are already pruned\n by the compiler.\n\n There are also three more special log types that create a different output than\n the previously mentioned types: #LOG_BOLD, #LOG_TIME and #LOG_PROG. See their\n respective documentation for more information.\n\n The inner working of this class is as follows: Upon invokation via one of the\n macros, an instance is created that stays alive only for the rest of the\n source code line. In this line, the log message is inserted to the buffer\n stream. After the line finishes, the object is automatically destroyed, so\n that its destructor is called. In the destructor, the message is composed and\n logged to all given output streams.\n\n Caveat: Because the macro contains conditions depending on the log level,\n do not use code in a log line that changes the program state.\n Therefore, instead of\n\n     LOG_INFO << \"this is iteration \" << ++i;\n\n use\n\n     ++i;\n     LOG_INFO << \"this is iteration \" << i;\n\n because the former will not work when the max log level is below info level.");
		cl.def( pybind11::init( [](){ return new genesis::utils::Logging(); } ) );
		cl.def( pybind11::init( [](genesis::utils::Logging const &o){ return new genesis::utils::Logging(o); } ) );

		pybind11::enum_<genesis::utils::Logging::LoggingLevel>(cl, "LoggingLevel", pybind11::arithmetic(), "Levels of severity used for logging.\n\n The levels are in ascending order and are used both to signal what\n kind of message is being logged and to provide a threshold for less\n important messages that can be filtered out, for example debug\n messages in the production build of the program. Because some of the\n filtering is already done at compile time, log messages with a level\n higher than #LOG_LEVEL_MAX do not produce any overhead. See also\n Logging class for more on this.")
			.value("kNone", genesis::utils::Logging::kNone)
			.value("kError", genesis::utils::Logging::kError)
			.value("kWarning", genesis::utils::Logging::kWarning)
			.value("kInfo", genesis::utils::Logging::kInfo)
			.value("kProgress", genesis::utils::Logging::kProgress)
			.value("kMessage", genesis::utils::Logging::kMessage)
			.value("kMessage1", genesis::utils::Logging::kMessage1)
			.value("kMessage2", genesis::utils::Logging::kMessage2)
			.value("kMessage3", genesis::utils::Logging::kMessage3)
			.value("kMessage4", genesis::utils::Logging::kMessage4)
			.value("kDebug", genesis::utils::Logging::kDebug)
			.value("kDebug1", genesis::utils::Logging::kDebug1)
			.value("kDebug2", genesis::utils::Logging::kDebug2)
			.value("kDebug3", genesis::utils::Logging::kDebug3)
			.value("kDebug4", genesis::utils::Logging::kDebug4)
			.export_values();

		cl.def("get", (class std::basic_ostringstream<char> & (genesis::utils::Logging::*)(const std::string &, const int, const std::string &, const enum genesis::utils::Logging::LoggingLevel)) &genesis::utils::Logging::get, "C++: genesis::utils::Logging::get(const std::string &, const int, const std::string &, const enum genesis::utils::Logging::LoggingLevel) --> class std::basic_ostringstream<char> &", pybind11::return_value_policy::reference_internal, pybind11::arg("file"), pybind11::arg("line"), pybind11::arg("function"), pybind11::arg("level"));
		cl.def("get", (class std::basic_ostringstream<char> & (genesis::utils::Logging::*)(const std::string &, const int, const std::string &, const enum genesis::utils::Logging::LoggingLevel, const struct genesis::utils::LoggingDetails)) &genesis::utils::Logging::get, "C++: genesis::utils::Logging::get(const std::string &, const int, const std::string &, const enum genesis::utils::Logging::LoggingLevel, const struct genesis::utils::LoggingDetails) --> class std::basic_ostringstream<char> &", pybind11::return_value_policy::reference_internal, pybind11::arg("file"), pybind11::arg("line"), pybind11::arg("function"), pybind11::arg("level"), pybind11::arg("dets"));
		cl.def_static("log_to_stdout", (void (*)()) &genesis::utils::Logging::log_to_stdout, "C++: genesis::utils::Logging::log_to_stdout() --> void");
		cl.def_static("log_to_stream", (void (*)(std::ostream &)) &genesis::utils::Logging::log_to_stream, "C++: genesis::utils::Logging::log_to_stream(std::ostream &) --> void", pybind11::arg("os"));
		cl.def_static("log_to_file", (void (*)(const std::string &)) &genesis::utils::Logging::log_to_file, "C++: genesis::utils::Logging::log_to_file(const std::string &) --> void", pybind11::arg("fn"));
		cl.def_static("clear", (void (*)()) &genesis::utils::Logging::clear, "C++: genesis::utils::Logging::clear() --> void");
		cl.def_static("max_level", (enum genesis::utils::Logging::LoggingLevel (*)()) &genesis::utils::Logging::max_level, "Get the highest log level that is reported. \n\nC++: genesis::utils::Logging::max_level() --> enum genesis::utils::Logging::LoggingLevel");
		cl.def_static("max_level", (void (*)(const enum genesis::utils::Logging::LoggingLevel)) &genesis::utils::Logging::max_level, "C++: genesis::utils::Logging::max_level(const enum genesis::utils::Logging::LoggingLevel) --> void", pybind11::arg("level"));
		cl.def_static("report_percentage", (int (*)()) &genesis::utils::Logging::report_percentage, "Get the current percentage for reporting #LOG_PROG messages. \n\nC++: genesis::utils::Logging::report_percentage() --> int");
		cl.def_static("report_percentage", (void (*)(const int)) &genesis::utils::Logging::report_percentage, "C++: genesis::utils::Logging::report_percentage(const int) --> void", pybind11::arg("percentage"));
		cl.def_static("level_to_string", (std::string (*)(const enum genesis::utils::Logging::LoggingLevel)) &genesis::utils::Logging::level_to_string, "C++: genesis::utils::Logging::level_to_string(const enum genesis::utils::Logging::LoggingLevel) --> std::string", pybind11::arg("level"));
		cl.def_static("log_error", (void (*)(const std::string &)) &genesis::utils::Logging::log_error, "C++: genesis::utils::Logging::log_error(const std::string &) --> void", pybind11::arg("msg"));
		cl.def_static("log_warning", (void (*)(const std::string &)) &genesis::utils::Logging::log_warning, "C++: genesis::utils::Logging::log_warning(const std::string &) --> void", pybind11::arg("msg"));
		cl.def_static("log_info", (void (*)(const std::string &)) &genesis::utils::Logging::log_info, "C++: genesis::utils::Logging::log_info(const std::string &) --> void", pybind11::arg("msg"));
		cl.def_static("log_message", (void (*)(const std::string &)) &genesis::utils::Logging::log_message, "C++: genesis::utils::Logging::log_message(const std::string &) --> void", pybind11::arg("msg"));
		cl.def_static("log_message_1", (void (*)(const std::string &)) &genesis::utils::Logging::log_message_1, "C++: genesis::utils::Logging::log_message_1(const std::string &) --> void", pybind11::arg("msg"));
		cl.def_static("log_message_2", (void (*)(const std::string &)) &genesis::utils::Logging::log_message_2, "C++: genesis::utils::Logging::log_message_2(const std::string &) --> void", pybind11::arg("msg"));
		cl.def_static("log_message_3", (void (*)(const std::string &)) &genesis::utils::Logging::log_message_3, "C++: genesis::utils::Logging::log_message_3(const std::string &) --> void", pybind11::arg("msg"));
		cl.def_static("log_message_4", (void (*)(const std::string &)) &genesis::utils::Logging::log_message_4, "C++: genesis::utils::Logging::log_message_4(const std::string &) --> void", pybind11::arg("msg"));
		cl.def_static("log_debug", (void (*)(const std::string &)) &genesis::utils::Logging::log_debug, "C++: genesis::utils::Logging::log_debug(const std::string &) --> void", pybind11::arg("msg"));
		cl.def_static("log_debug_1", (void (*)(const std::string &)) &genesis::utils::Logging::log_debug_1, "C++: genesis::utils::Logging::log_debug_1(const std::string &) --> void", pybind11::arg("msg"));
		cl.def_static("log_debug_2", (void (*)(const std::string &)) &genesis::utils::Logging::log_debug_2, "C++: genesis::utils::Logging::log_debug_2(const std::string &) --> void", pybind11::arg("msg"));
		cl.def_static("log_debug_3", (void (*)(const std::string &)) &genesis::utils::Logging::log_debug_3, "C++: genesis::utils::Logging::log_debug_3(const std::string &) --> void", pybind11::arg("msg"));
		cl.def_static("log_debug_4", (void (*)(const std::string &)) &genesis::utils::Logging::log_debug_4, "C++: genesis::utils::Logging::log_debug_4(const std::string &) --> void", pybind11::arg("msg"));
	}
	{ // genesis::utils::LoggingScopeLevel file:genesis/utils/core/logging.hpp line:621
		pybind11::class_<genesis::utils::LoggingScopeLevel, std::shared_ptr<genesis::utils::LoggingScopeLevel>> cl(M("genesis::utils"), "LoggingScopeLevel", "Class that sets the Logging Level to a value von construction and set it back on\n destruction. This is used by the log scope level macro.");
		cl.def( pybind11::init<enum genesis::utils::Logging::LoggingLevel>(), pybind11::arg("scope_level") );

	}
	// genesis::utils::path_exists(const std::string &) file:genesis/utils/core/fs.hpp line:48
	M("genesis::utils").def("path_exists", (bool (*)(const std::string &)) &genesis::utils::path_exists, "Return whether a path exists, i.e., is a file or directory.\n\nC++: genesis::utils::path_exists(const std::string &) --> bool", pybind11::arg("path"));

	// genesis::utils::is_file(const std::string &) file:genesis/utils/core/fs.hpp line:57
	M("genesis::utils").def("is_file", (bool (*)(const std::string &)) &genesis::utils::is_file, "Return true iff the provided path is a (readable) file.\n\n Internally, this function simply returns the value of file_is_readable(), meaning that we also\n check that the file can actually be read. That is semantically a bit different from just stating\n that it is a file... But file system stuff in C++ pre-17 is hard, and this works for now.\n\nC++: genesis::utils::is_file(const std::string &) --> bool", pybind11::arg("path"));

	// genesis::utils::file_exists(const std::string &) file:genesis/utils/core/fs.hpp line:64
	M("genesis::utils").def("file_exists", (bool (*)(const std::string &)) &genesis::utils::file_exists, "Return true iff the file exists (and is in fact a file, and not, e.g., a directory).\n\n  is_file( std::string const& )\n\nC++: genesis::utils::file_exists(const std::string &) --> bool", pybind11::arg("filename"));

	// genesis::utils::file_is_readable(const std::string &) file:genesis/utils/core/fs.hpp line:75
	M("genesis::utils").def("file_is_readable", (bool (*)(const std::string &)) &genesis::utils::file_is_readable, "Return whether a file is readable.\n\n For this, the file has to exist, and be accessible.\n Another potential error is that too many files are opened already.\n\n See file_is_readable( std::string const&, std::string& ) for a version of the function that also\n allows to retrieve the error message in cases where the result is `false`.\n\nC++: genesis::utils::file_is_readable(const std::string &) --> bool", pybind11::arg("filename"));

	// genesis::utils::file_is_readable(const std::string &, std::string &) file:genesis/utils/core/fs.hpp line:83
	M("genesis::utils").def("file_is_readable", (bool (*)(const std::string &, std::string &)) &genesis::utils::file_is_readable, "Return whether a file is readable, and potentially store the error message.\n\n For this, the file has to exist, and be accessible.\n Another potential error is that too many files are opened already.\n\nC++: genesis::utils::file_is_readable(const std::string &, std::string &) --> bool", pybind11::arg("filename"), pybind11::arg("err_str"));

	// genesis::utils::file_read(const std::string &, bool) file:genesis/utils/core/fs.hpp line:93
	M("genesis::utils").def("file_read", [](const std::string & a0) -> std::string { return genesis::utils::file_read(a0); }, "", pybind11::arg("filename"));
	M("genesis::utils").def("file_read", (std::string (*)(const std::string &, bool)) &genesis::utils::file_read, "Return the contents of a file as a string.\n\n If the parameter  is `true` (default), it is first determined whether the\n file is gzip compressed, and if so, the file is decompressed when reading.\n\n If the file is not readable, the function throws `std::runtime_error`.\n\nC++: genesis::utils::file_read(const std::string &, bool) --> std::string", pybind11::arg("filename"), pybind11::arg("detect_compression"));

}
