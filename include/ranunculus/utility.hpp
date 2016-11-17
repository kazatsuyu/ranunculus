
#ifndef RANUNCULUS_UTILITY_HPP
#define RANUNCULUS_UTILITY_HPP

#include <type_traits>
#include "environment.hpp"

#define RANUNCULUS_MACRO_STR_(x) #x
#define RANUNCULUS_MACRO_STR(x) RANUNCULUS_MACRO_STR_(x)
#define RANUNCULUS_EXCEPT_WHEN(condition, exception) \
    if(condition) {\
        throw exception(std::string(RANUNCULUS_FUNCTION_NAME) + \
                        ": (" \
                        #condition \
                        ") at " \
                        __FILE__\
                        ":" \
                        RANUNCULUS_MACRO_STR(__LINE__));\
    }

#if RANUNCULUS_COMPILER_IS(GCC) || RANUNCULUS_COMPILER_IS(CLANG)
#define RANUNCULUS_FUNCTION_NAME __PRETTY_FUNCTION__
#elif RANUNCULUS_COMPILER_IS(MSVC) __FUNCSIG__
#endif

#define RANUNCULUS_MACRO_WORKAROUND

namespace ranunculus {
inline namespace utility {

namespace v1 {

template<bool condition, typename T = std::nullptr_t>
using enable_when = std::enable_if_t<condition, T>;

template<bool value>
using bool_constant = std::integral_constant<bool, value>;

} // namespace vi

using namespace v1;

} // namespace utility
} // namespace ranunculs


#endif

