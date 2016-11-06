
#ifndef RANUNCULUS_TYPE_SEQUENCE_HPP
#define RANUNCULUS_TYPE_SEQUENCE_HPP

#include "integer_sequence.hpp"

namespace ranunculus { namespace type_sequence {

namespace v1 {

namespace detail {

template<typename ...TA> struct concat_;
template<typename T, typename ...TA>
struct concat_<T, TA...> {
    using type = typename concat_<T, typename concat_<TA ...>::type>::type;
};
template<template<typename...> class TT, typename ...TA1, typename ...TA2>
struct concat_<TT<TA1...>, TT<TA2...>> {
    using type = TT<TA1..., TA2...>;
};
template<typename ...TA>
using concat = typename concat_<TA...>::type;

template<template<typename...> class TT, typename T, size_t N>
struct make_type_sequence_ {
    using type = concat<
        typename make_type_sequence_<TT, T, N / 2>::type,
        typename make_type_sequence_<TT, T, (N + 1) / 2>::type
    >;
};
template<template<typename...> class TT, typename T>
struct make_type_sequence_<TT, T, 0> {
    using type = TT<>;
};
template<template<typename...> class TT, typename T>
struct make_type_sequence_<TT, T, 1> {
    using type = TT<T>;
};
template<template<typename...> class TT, typename T, size_t N>
using make_type_sequence = typename make_type_sequence_<TT, T, N>::type;

template<typename T, typename ...TA> struct append_;
template<template<typename...> class TT, typename ...TA1, typename ...TA2>
struct append_<TT<TA1...>, TA2...> {
    using type = TT<TA1..., TA2...>;
};
template<typename T, typename ...TA>
using append = typename append_<T, TA...>::type;

template<typename T, typename ...TA> struct prepend_;
template<template<typename...> class TT, typename ...TA1, typename ...TA2>
struct prepend_<TT<TA1...>, TA2...> {
    using type = TT<TA2..., TA1...>;
};
template<typename T, typename ...TA>
using prepend = typename prepend_<T, TA...>::type;

template<typename T> struct size_of_;
template<template<typename...> class TT, typename ...TA>
struct size_of_<TT<TA...>> {
    static constexpr size_t value = sizeof...(TA);
};
template<typename T>
static constexpr size_t size_of = size_of_<T>::value;

template<typename T, size_t N> struct at_;
template<template<typename...> class TT, typename ...TA, size_t N>
class at_<TT<TA...>, N> {
    template<typename ...UA>
    struct helper {
        template<typename T>
        static T invoke(UA..., T, ...);
    };
    struct wrapper_base {};
    template<typename U> struct wrapper : wrapper_base {
        using type = U;
    };
public:
    using type = typename decltype(
        make_type_sequence<
            helper,
            wrapper_base,
            N
       >::invoke(std::declval<wrapper<TA>>()...))::type;
};
template<typename T, size_t N, enable_when<(N < size_of<T>)> = nullptr>
using at = typename at_<T, N>::type;

template<typename T, template<typename...> class TT> struct apply_;
template<template<typename...> class TT1, typename ...TA, template<typename...> class TT2>
struct apply_<TT1<TA...>, TT2> {
    using type = TT2<TA...>;
};
template<typename T, template<typename...> class TT>
using apply = typename detail::apply_<T, TT>::type;

template<typename T, size_t B, size_t E> struct slice_;
template<template<typename...> class TT, typename ...TA, size_t B, size_t E>
class slice_<TT<TA...>, B, E> {
    static constexpr size_t b = B > sizeof...(TA) ? sizeof...(TA) : B;
    static constexpr size_t e = E > sizeof...(TA) ? sizeof...(TA) : E;
    using range = integer_sequence::make_range<size_t, b, e>;
    template<integer_sequence::value_type_of<range> ...A1>
    struct helper {
        using type = TT<at<TT<TA...>, A1>...>;
    };
public:
    using type = typename integer_sequence::apply<range, helper>::type;
};
template<typename T, size_t B = 0, size_t E = size_of<T>, enable_when<(B<=E)> = nullptr>
using slice = typename slice_<T, B, E>::type;

} // namespce detail;

using detail::concat;
using detail::make_type_sequence;
using detail::append;
using detail::prepend;
using detail::size_of;
using detail::at;
using detail::apply;
using detail::slice;

template<typename T, size_t N>
using head = slice<T, 0, N>;

template<typename T, size_t N = 1>
using tail = slice<T, (N > size_of<T>) ? 0 : size_of<T> - N, size_of<T>>;

template<typename T, size_t N, typename ...TA>
using insert = concat<append<head<T, N>, TA...>, slice<T, N>>;

} // namespace v1

using namespace v1;

}} // namespace ranunculus::tyoe_sequence

#endif

