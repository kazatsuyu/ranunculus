
#ifndef RANUNCULUS_UTILITY_HPP
#define RANUNCULUS_UTILITY_HPP

#include <type_traits>

namespace ranunculus {
inline namespace utility {

namespace v1 {

template<bool condition, typename T = std::nullptr_t>
using enable_when = std::enable_if_t<condition, T>;

} // namespace vi

using namespace v1;

} // namespace utility
} // namespace ranunculs

#endif

