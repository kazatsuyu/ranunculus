
#ifndef RANUNCULUS_TYPES_HPP
#define RANUNCULUS_TYPES_HPP

#include <cstddef>
#include <cstdint>

namespace ranunculs {
inline namespace types {

namespace v1 {

using std::int8_t;
using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint16_t;
using std::size_t;
using std::ptrdiff_t;
using std::intptr_t;
using std::uintptr_t;
using std::nullptr_t;

} // namespace v1

template<nullptr_t>
struct default_t {
    using char_type = char;
};


namespace v1 {

using char_t = default_t<nullptr>::char_type;

} // namespace v1

using namespace v1;

} // namespace types
} // namespace ranunculs

#endif

