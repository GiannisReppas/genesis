#ifndef CUSTOM_BINDING_TO_STRING_INCLUDED_
#define CUSTOM_BINDING_TO_STRING_INCLUDED_

#include "genesis/utils/io/base_output_target.hpp"
#include "genesis/utils/io/string_output_target.hpp"

#include <iostream>

inline void extend_to_string(pybind11::module &handle)
{
    handle.def(
        "to_string",
        []( std::string& target_string) -> std::shared_ptr<::genesis::utils::StringOutputTarget>
        {
            return std::make_shared< ::genesis::utils::StringOutputTarget >( target_string );
        }
        , pybind11::return_value_policy::copy
    );
}

#endif