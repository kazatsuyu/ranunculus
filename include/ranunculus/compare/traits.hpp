#ifndef RANUNCULUS_COMPARE_TRAITS_HPP
#define RANUNCULUS_COMPARE_TRAITS_HPP

#include "../utility.hpp"
#include "../arith.hpp"

namespace ranunculus {
namespace compare {
namespace v1 {

namespace detail {

template<typename T, typename U>
class eq_comparable_ {
    template<typename V, typename W>
    static auto check(const V& v, const W& w) ->decltype(v == w, std::true_type{});
    static std::false_type check(...);
public:
    using type = decltype(check(std::declval<const T&>(), std::declval<const U&>()));
};

template<typename T, typename U>
class ne_comparable_ {
    template<typename V, typename W>
    static auto check(const V& v, const W& w) ->decltype(v != w, std::true_type{});
    static std::false_type check(...);
public:
    using type = decltype(check(std::declval<const T&>(), std::declval<const U&>()));
};

template<typename T, typename U>
class lt_comparable_ {
    template<typename V, typename W>
    static auto check(const V& v, const W& w) ->decltype(v < w, std::true_type{});
    static std::false_type check(...);
public:
    using type = decltype(check(std::declval<const T&>(), std::declval<const U&>()));
};

template<typename T, typename U>
class le_comparable_ {
    template<typename V, typename W>
    static auto check(const V& v, const W& w) ->decltype(v <= w, std::true_type{});
    static std::false_type check(...);
public:
    using type = decltype(check(std::declval<const T&>(), std::declval<const U&>()));
};

template<typename T, typename U>
class ge_comparable_ {
    template<typename V, typename W>
    static auto check(const V& v, const W& w) ->decltype(v >= w, std::true_type{});
    static std::false_type check(...);
public:
    using type = decltype(check(std::declval<const T&>(), std::declval<const U&>()));
};

template<typename T, typename U>
class gt_comparable_ {
    template<typename V, typename W>
    static auto check(const V& v, const W& w) ->decltype(v > w, std::true_type{});
    static std::false_type check(...);
public:
    using type = decltype(check(std::declval<const T&>(), std::declval<const U&>()));
};

}

template<typename T, typename U>
struct eq_comparable : detail::eq_comparable_<T, U>::type {};
template<typename T, typename U>
static constexpr auto eq_comparable_v = eq_comparable<T, U>::value;
template<typename T, typename U>
struct ne_comparable : detail::ne_comparable_<T, U>::type {};
template<typename T, typename U>
static constexpr auto ne_comparable_v = ne_comparable<T, U>::value;
template<typename T, typename U>
struct lt_comparable : detail::lt_comparable_<T, U>::type {};
template<typename T, typename U>
static constexpr auto lt_comparable_v = lt_comparable<T, U>::value;
template<typename T, typename U>
struct le_comparable : detail::le_comparable_<T, U>::type {};
template<typename T, typename U>
static constexpr auto le_comparable_v = le_comparable<T, U>::value;
template<typename T, typename U>
struct ge_comparable : detail::ge_comparable_<T, U>::type {};
template<typename T, typename U>
static constexpr auto ge_comparable_v = ge_comparable<T, U>::value;
template<typename T, typename U>
struct gt_comparable : detail::gt_comparable_<T, U>::type {};
template<typename T, typename U>
static constexpr auto gt_comparable_v = gt_comparable<T, U>::value;

namespace detail {

enum class require_t {
    eq, qe, ne, en, lt, tl, le, el, ge, eg, gt, tg, last
};

static constexpr require_t eq_ = require_t::eq;
static constexpr require_t qe_ = require_t::qe;
static constexpr require_t ne_ = require_t::ne;
static constexpr require_t en_ = require_t::en;
static constexpr require_t lt_ = require_t::lt;
static constexpr require_t tl_ = require_t::tl;
static constexpr require_t le_ = require_t::le;
static constexpr require_t el_ = require_t::el;
static constexpr require_t ge_ = require_t::ge;
static constexpr require_t eg_ = require_t::eg;
static constexpr require_t gt_ = require_t::gt;
static constexpr require_t tg_ = require_t::tg;

constexpr require_t operator!(require_t value) noexcept {
    return value < require_t::last ? arith::add(value, require_t::last) : arith::sub(value, require_t::last);
}


template<typename, typename, require_t ...>
struct require_ : std::true_type {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, eq_, A...> : bool_constant<eq_comparable<T, U>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, qe_, A...> : bool_constant<eq_comparable<U, T>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, ne_, A...> : bool_constant<ne_comparable<T, U>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, en_, A...> : bool_constant<ne_comparable<U, T>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, lt_, A...> : bool_constant<lt_comparable<T, U>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, tl_, A...> : bool_constant<gt_comparable<U, T>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, le_, A...> : bool_constant<le_comparable<T, U>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, el_, A...> : bool_constant<ge_comparable<U, T>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, ge_, A...> : bool_constant<ge_comparable<T, U>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, eg_, A...> : bool_constant<le_comparable<U, T>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, gt_, A...> : bool_constant<gt_comparable<T, U>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, tg_, A...> : bool_constant<lt_comparable<U, T>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, !eq_, A...> : bool_constant<!eq_comparable<T, U>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, !qe_, A...> : bool_constant<!eq_comparable<U, T>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, !ne_, A...> : bool_constant<!ne_comparable<T, U>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, !en_, A...> : bool_constant<!ne_comparable<U, T>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, !lt_, A...> : bool_constant<!lt_comparable<T, U>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, !tl_, A...> : bool_constant<!gt_comparable<U, T>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, !le_, A...> : bool_constant<!le_comparable<T, U>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, !el_, A...> : bool_constant<!ge_comparable<U, T>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, !ge_, A...> : bool_constant<!ge_comparable<T, U>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, !eg_, A...> : bool_constant<!le_comparable<U, T>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, !gt_, A...> : bool_constant<!gt_comparable<T, U>{} && require_<T, U, A...>{}> {};
template<typename T, typename U, require_t ...A>
struct require_<T, U, !tg_, A...> : bool_constant<!lt_comparable<U, T>{} && require_<T, U, A...>{}> {};

template<typename T, typename U, require_t ...A>
using require = enable_when<require_<T, U, A...>{}>;


} // namespace detail

} // namespace v1
} // namespace compare
} // namespace ranunculus

#endif
