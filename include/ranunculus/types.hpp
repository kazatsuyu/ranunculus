
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
using std::int_fast8_t;
using std::int_fast16_t;
using std::int_fast32_t;
using std::int_fast64_t;
using std::int_least8_t;
using std::int_least16_t;
using std::int_least32_t;
using std::int_least64_t;
using std::intmax_t;
using std::intptr_t;

using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint16_t;
using std::uint_fast8_t;
using std::uint_fast16_t;
using std::uint_fast32_t;
using std::uint_fast64_t;
using std::uint_least8_t;
using std::uint_least16_t;
using std::uint_least32_t;
using std::uint_least64_t;
using std::uintmax_t;
using std::uintptr_t;

using std::size_t;
using std::ptrdiff_t;
using std::nullptr_t;

} // namespace v1

template<std::nullptr_t = nullptr>
struct default_t {
    using char_type = char;
};


namespace v1 {

using char_t = default_t<>::char_type;

} // namespace v1

using namespace v1;

} // namespace types
} // namespace ranunculs

#endif

