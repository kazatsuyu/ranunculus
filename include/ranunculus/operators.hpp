#ifndef RANUNCULUS_OPERATORS_HPP
#define RANUNCULUS_OPERATORS_HPP

#include "arith.hpp"

namespace ranunculus {
namespace operators {

template<typename T>
struct implement_flags;

namespace v1 {

template<typename T>
class implement_traits {
    template<typename U>
    static std::integral_constant<bool, implement_flags<U>::arithmetic> arithmetic_(U&&);
    static std::false_type arithmetic_(...);
    template<typename U>
    static std::integral_constant<bool, implement_flags<U>::conditional> conditional_(U&&);
    static std::false_type conditional_(...);
public:
    static constexpr bool arithmetic = decltype(arithmetic_(std::declval<T>()))::value;
    static constexpr bool conditional = decltype(conditional_(std::declval<T>()))::value;
};

namespace arithmetic {

namespace detail {

template<typename T>
using implementable = enable_when<implement_traits<T>::arithmetic>;

template<typename T, implementable<T> = nullptr>
constexpr T operator +(T lhs, T rhs) noexcept {
    return arith::add(lhs, rhs);
}

template<typename T, implementable<T> = nullptr>
constexpr T& operator +=(T& lhs, T rhs) noexcept {
    return lhs = lhs + rhs;
}

template<typename T, implementable<T> = nullptr>
constexpr T& operator ++(T& value) noexcept {
    return value = arith::inc(value);
}

template<typename T, implementable<T> = nullptr>
constexpr T operator ++(T& value, int) noexcept {
    T tmp = value; ++value; return tmp;
}

template<typename T, implementable<T> = nullptr>
constexpr T operator -(T lhs, T rhs) noexcept {
    return arith::sub(lhs, rhs);
}

template<typename T, implementable<T> = nullptr>
constexpr T& operator -=(T& lhs, T rhs) noexcept {
    return lhs = lhs - rhs;
}

template<typename T, implementable<T> = nullptr>
constexpr T& operator --(T& value) noexcept {
    return value = arith::dec(value);
}

template<typename T, implementable<T> = nullptr>
constexpr T operator --(T& value, int) noexcept {
    T tmp = value; --value; return tmp;
}

template<typename T, implementable<T> = nullptr>
constexpr T operator *(T lhs, T rhs) noexcept {
    return arith::mul(lhs, rhs);
}

template<typename T, implementable<T> = nullptr>
constexpr T& operator *=(T& lhs, T rhs) noexcept {
    return lhs = lhs % rhs;
}

template<typename T, implementable<T> = nullptr>
constexpr T operator /(T lhs, T rhs) noexcept {
    return arith::div(lhs, rhs);
}

template<typename T, implementable<T> = nullptr>
constexpr T& operator /=(T& lhs, T rhs) noexcept {
    return lhs = lhs / rhs;
}

template<typename T, implementable<T> = nullptr>
constexpr T operator %(T lhs, T rhs) noexcept {
    return arith::mod(lhs, rhs);
}

template<typename T, implementable<T> = nullptr>
constexpr T& operator %=(T& lhs, T rhs) noexcept {
    return lhs = lhs % rhs;
}

template<typename T, implementable<T> = nullptr>
constexpr T operator |(T lhs, T rhs) noexcept {
    return arith::bitwise_or(lhs, rhs);
}

template<typename T, implementable<T> = nullptr>
constexpr T operator |=(T& lhs, T rhs) noexcept {
    return lhs = lhs | rhs;
}

template<typename T, implementable<T> = nullptr>
constexpr T operator &(T lhs, T rhs) noexcept {
    return arith::bitwise_and(lhs, rhs);
}

template<typename T, implementable<T> = nullptr>
constexpr T operator &=(T& lhs, T rhs) noexcept {
    return lhs = lhs & rhs;
}

template<typename T, implementable<T> = nullptr>
constexpr T operator ^(T lhs, T rhs) noexcept {
    return arith::bitwise_xor(lhs, rhs);
}

template<typename T, implementable<T> = nullptr>
constexpr T operator ^=(T& lhs, T rhs) noexcept {
    return lhs = lhs ^ rhs;
}

template<typename T, implementable<T> = nullptr>
constexpr T operator ~(T value) noexcept {
    return arith::bitwise_not(value);
}

template<typename T, implementable<T> = nullptr>
constexpr T operator <<(T value, int n) noexcept {
    return arith::lshift(value, n);
}

template<typename T, implementable<T> = nullptr>
constexpr T operator <<=(T& lhs, int n) noexcept {
    return lhs = lhs << n;
}

template<typename T, implementable<T> = nullptr>
constexpr T operator >>(T value, int n) noexcept {
    return arith::rshift(value, n);
}

template<typename T, implementable<T> = nullptr>
constexpr T operator >>=(T& lhs, int n) noexcept {
    return lhs = lhs >> n;
}

} // namespace detail;

using detail::operator +;
using detail::operator +=;
using detail::operator ++;
using detail::operator -;
using detail::operator -=;
using detail::operator --;
using detail::operator *;
using detail::operator *=;
using detail::operator /;
using detail::operator /=;
using detail::operator %;
using detail::operator %=;
using detail::operator |;
using detail::operator |=;
using detail::operator &;
using detail::operator &=;
using detail::operator ^;
using detail::operator ^=;
using detail::operator ~;
using detail::operator <<;
using detail::operator <<=;
using detail::operator >>; 
using detail::operator >>=;

} // arithmetic_operators

namespace conditional {

namespace detail {

template<typename T>
using implementable = enable_when<implement_traits<T>::conditional>;

template<typename T, implementable<T> = nullptr>
bool operator ==(const T& lhs, const T& rhs) noexcept(noexcept(lhs != rhs)) {
    return !(lhs != rhs);
}

template<typename T, implementable<T> = nullptr>
bool operator !=(const T& lhs, const T& rhs) noexcept(noexcept(lhs == rhs)) {
    return !(lhs == rhs);
}

template<typename T, implementable<T> = nullptr>
constexpr bool operator <(const T& lhs, const T& rhs) noexcept(noexcept(lhs >= rhs)) {
    return !(lhs >= rhs);
}

template<typename T, implementable<T> = nullptr>
constexpr bool operator <=(const T& lhs, const T& rhs) noexcept(noexcept(lhs > rhs)) {
    return !(lhs > rhs);
}

template<typename T, implementable<T> = nullptr>
constexpr bool operator >=(const T& lhs, const T& rhs) noexcept(noexcept(lhs < rhs)) {
    return !(lhs < rhs);
}

template<typename T, implementable<T> = nullptr>
constexpr bool operator >(const T& lhs, const T& rhs) noexcept(noexcept(lhs <= rhs)) {
    return !(lhs <= rhs);
}

} // namespace detail

using detail::operator ==;
using detail::operator !=;
using detail::operator <;
using detail::operator <=;
using detail::operator >=;
using detail::operator >;

} // namespace conditional_operators

} // namespace v1

using namespace v1;

} // namespace operators
} // namespace ranunculus

#endif
