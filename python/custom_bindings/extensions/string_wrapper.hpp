#ifndef CUSTOM_BINDING_STRING_WRAPPER_INCLUDED_
#define CUSTOM_BINDING_STRING_WRAPPER_INCLUDED_

#include "genesis/utils/io/base_output_target.hpp"
#include "genesis/utils/io/output_target.hpp"
#include "genesis/utils/io/string_output_target.hpp"

#include <pybind11/pytypes.h>

#include <sstream>
#include <string>

namespace genesis {
namespace utils {

/**
 * @brief Helper class to use to_string() and StringOutputTarget in Python.
 *
 * Python has immutable strings, so, we cannot write to them with our references as usual.
 * Instead, we write to this class, which wraps the string on the C++ side, and
 * access it later from Python.
 */
struct StringTarget
{
public:

    // -------------------------------------------------------------------------
    //     Constructors and Rule of Five
    // -------------------------------------------------------------------------

    StringTarget()
    {
        target_ = ::genesis::utils::to_string( data_ );
    }
    
    ~StringTarget() = default;

    StringTarget(StringTarget const&) = default;
    StringTarget(StringTarget&&)      = default;

    StringTarget& operator= (StringTarget const&) = default;
    StringTarget& operator= (StringTarget&&)      = default;

    // -------------------------------------------------------------------------
    //     Accessors
    // -------------------------------------------------------------------------

    std::string const& get() const
    {
        target_->flush();
        return data_;
    }

    std::string& get()
    {
        target_->flush();
        return data_;
    }

    // -------------------------------------------------------------------------
    //     Data Members
    // -------------------------------------------------------------------------

private:

    std::string data_;
    std::shared_ptr<::genesis::utils::BaseOutputTarget> target_;

};

}
}

#endif