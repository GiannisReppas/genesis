#include <string>
#include <fstream>
#include <streambuf>

#include "log.hh"

namespace genesis {
namespace utils {

/**
 * @brief Returns the contents of a file as a string.
 *
 * If the file does not exist, a warning is triggered and an emtpty string
 * returned.
 */
std::string ReadFile (const std::string fn)
{
    std::ifstream t(fn);
    std::string str;

    if (!t.good()) {
        LOG_WARN << "File '" << fn << "' does not exist.";
        return "";
    }

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>());
    return str;
}

} // namespace utils
} // namespace genesis
