#ifndef CUSTOM_BINDING_TO_STRING_INCLUDED_
#define CUSTOM_BINDING_TO_STRING_INCLUDED_

#include "genesis/utils/io/output_target.hpp"
#include "string_wrapper.hpp"

#include <iostream>

inline void extend_to_string(pybind11::module &handle)
{
    handle.def(
        "to_string",
        [](
            ::genesis::utils::StringTarget& name
        ) -> std::shared_ptr<::genesis::utils::BaseOutputTarget> {
            std::shared_ptr<::genesis::utils::BaseOutputTarget> a = ::genesis::utils::to_string( name.get() );
            return a;
        }
    );
/*
    handle.def(
        "to_string",
        []( ::genesis::utils::StringTarget& name ) -> std::shared_ptr<::genesis::utils::BaseOutputTarget>
        {
            return ::genesis::utils::to_string( name.get() );
        },
        pybind11::return_value_policy::copy,
        pybind11::keep_alive<0,1>()
    );
*/
}

#endif