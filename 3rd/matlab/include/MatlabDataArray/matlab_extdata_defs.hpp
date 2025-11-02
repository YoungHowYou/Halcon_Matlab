/* Copyright 2016-2024 The MathWorks, Inc. */

#ifndef MATLAB_EXTDATA_DEFS_HPP_
#define MATLAB_EXTDATA_DEFS_HPP_

#include <functional>
#include <memory>


namespace matlab {
    namespace data {

        template <typename T = void>
        using buffer_deleter_t = void (*)(T*);

        template <typename T>
        using buffer_ptr_t = std::unique_ptr<T[], buffer_deleter_t<T>>;

        template <typename T>
        using buffer_ptr = std::unique_ptr<T[], buffer_deleter_t<>>;

        using void_buffer_ptr_t = std::unique_ptr<void, buffer_deleter_t<>>;

    }
}



#endif
