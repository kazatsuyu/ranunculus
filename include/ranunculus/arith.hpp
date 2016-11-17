#ifndef RANUNCULUS_ARITH_HPP
#define RANUNCULUS_ARITH_HPP

#include "types.hpp"
#include "concepts.hpp"

namespace ranunculus {
namespace arith {

namespace v1 {

namespace detail {

template<typename T, concepts::integral<T> = nullptr>
std::make_unsigned_t<T> convertible_unsigned_(T);
template<typename T, concepts::enum_<T> = nullptr>
std::make_unsigned_t<std::underlying_type_t<T>> convertible_unsigned_(T);
template<typename T>
uintptr_t convertible_unsigned_(T*);
template<typename T>
struct convertible_unsigned {
    using type = decltype(convertible_unsigned_(std::declval<T>()));
};
template<typename T>
using convertible_unsigned_t = typename convertible_unsigned<T>::type;

template<typename T, concepts::not_pointer<T> = nullptr>
constexpr convertible_unsigned_t<T> to_unsigned(T value) noexcept {
    return static_cast<convertible_unsigned_t<T>>(value);
}

template<typename T, concepts::pointer<T> = nullptr>
uintptr_t to_unsigned(T value) noexcept {
    return reinterpret_cast<uintptr_t>(value);
}

template<typename T, concepts::not_pointer<T> = nullptr>
constexpr T unsigned_to(convertible_unsigned_t<T> value) noexcept {
    return static_cast<T>(value);
}

template<typename T, concepts::pointer<T> = nullptr>
constexpr T unsigned_to(uintptr_t value) noexcept {
    return reinterpret_cast<T>(value);
}

template<typename T, concepts::integral<T> = nullptr>
T convertible_integral_(T);
template<typename T, concepts::enum_<T> = nullptr>
std::underlying_type_t<T> convertible_integral_(T);
template<typename T>
uintptr_t convertible_integral_(T*);
template<typename T>
struct convertible_integral {
    using type = decltype(convertible_integral_(std::declval<T>()));
};
template<typename T>
using convertible_integral_t = typename convertible_integral<T>::type;

template<typename T, concepts::not_pointer<T> = nullptr>
constexpr convertible_integral_t<T> to_integral(T value) noexcept {
    return static_cast<convertible_integral_t<T>>(value);
}

template<typename T, concepts::pointer<T> = nullptr>
convertible_integral_t<T> to_integral(T value) noexcept {
    return reinterpret_cast<convertible_integral_t<T>>(value);
}

template<typename T, concepts::not_pointer<T> = nullptr>
constexpr T integral_to(convertible_integral_t<T> value) noexcept {
    return static_cast<T>(value);
}

template<typename T, concepts::pointer<T> = nullptr>
T integral_to(uintptr_t value) noexcept {
    return reinterpret_cast<T>(value);
}

template<typename T>
constexpr T add(T lhs, T rhs) noexcept {
    return integral_to<T>(to_integral(lhs) + to_integral(rhs));
}

template<typename T>
constexpr T inc(T value) noexcept {
    return integral_to<T>(to_integral(value) + 1);
}

template<typename T>
constexpr T sub(T lhs, T rhs) noexcept {
    return integral_to<T>(to_integral(lhs) - to_integral(rhs));
}

template<typename T>
constexpr T dec(T value) noexcept {
    return integral_to<T>(to_integral(value) - 1);
}

template<typename T>
constexpr T minus(T value) noexcept {
    return integral_to<T>(-to_integral(value));
}

template<typename T>
constexpr T mul(T lhs, T rhs) noexcept {
    return integral_to<T>(to_integral(lhs) * to_integral(rhs));
}

template<typename T>
constexpr T div(T lhs, T rhs) noexcept {
    return integral_to<T>(to_integral(lhs) / to_integral(rhs));
}

template<typename T>
constexpr T mod(T lhs, T rhs) noexcept {
    return integral_to<T>(to_integral(lhs) % to_integral(rhs));
}

template<typename T>
constexpr T bitwise_or(T lhs, T rhs) noexcept {
    return unsigned_to<T>(to_unsigned(lhs) | to_unsigned(rhs));
}

template<typename T>
constexpr T bitwise_and(T lhs, T rhs) noexcept {
    return unsigned_to<T>(to_unsigned(lhs) & to_unsigned(rhs));
}

template<typename T>
constexpr T bitwise_xor(T lhs, T rhs) noexcept {
    return unsigned_to<T>(to_unsigned(lhs) ^ to_unsigned(rhs));
}

template<typename T>
constexpr T bitwise_not(T value) noexcept {
    return unsigned_to<T>(~to_unsigned(value));
}

template<typename T>
constexpr T lshift(T lhs, int rhs) noexcept {
    return unsigned_to<T>(to_unsigned(lhs) << rhs);
}

template<typename T>
constexpr T rshift(T lhs, int rhs) noexcept {
    return unsigned_to<T>(to_unsigned(lhs) >> rhs);
}

} // namespace detail

using detail::convertible_unsigned;
using detail::convertible_unsigned_t;
using detail::to_unsigned;
using detail::unsigned_to;
using detail::convertible_integral;
using detail::convertible_integral_t;
using detail::to_integral;
using detail::integral_to;
using detail::add;
using detail::inc;
using detail::sub;
using detail::dec;
using detail::minus;
using detail::mul;
using detail::div;
using detail::mod;
using detail::bitwise_or;
using detail::bitwise_and;
using detail::bitwise_xor;
using detail::bitwise_not;
using detail::lshift;
using detail::rshift;

} // namespace v1

using namespace v1;

} // namespace operators
} // namespace ranunculus

#endif
