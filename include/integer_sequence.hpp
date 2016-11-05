
#ifndef RANUNCULUS_INTEGER_SEQUENCE_HPP
#define RANUNCULUS_INTEGER_SEQUENCE_HPP

#include <utility>
#include <stdexcept>

#include "utility.hpp"
#include "types.hpp"

namespace ranunculus { namespace integer_sequence {

namespace v1 {

namespace detail {


template<typename T1> struct value_type_of_;
template<typename T, template<typename, T ...> class TT, T ...A>
struct value_type_of_<TT<T, A...>> {
    using type = T;
};
template<typename T>
using value_type_of = typename detail::value_type_of_<T>::type;

template<typename ...TA> struct concat_;
template<typename T, typename ...TA>
struct concat_<T, TA...> {
    using type = typename concat_<T, typename concat_<TA ...>::type>::type;
};
template<typename T, template<typename, T ...> class TT, T ...A1, T ...A2>
struct concat_<TT<T, A1...>, TT<T, A2...>> {
    using type = TT<T, A1..., A2...>;
};
template<typename ...TA>
using concat = typename concat_<TA...>::type;

template<typename T, T B, size_t N> struct make_range_;
template<typename T, T B, size_t N>
struct make_range_ {
    using type = concat<
        typename make_range_<T, B, N / 2>::type,
        typename make_range_<T, B + N / 2, (N + 1) / 2>::type>;
};
template<typename T, T N>
struct make_range_<T, N, 1> {
    using type = std::integer_sequence<T, N>;
};
template<typename T, T N>
struct make_range_<T, N, 0> {
    using type = std::integer_sequence<T>;
};
template<typename T, T B, T E, enable_when<(B <= E)> = nullptr>
using make_range = typename make_range_<T, B, E - B>::type;

template<typename T, value_type_of<T> ...A> struct append_;
template<typename T, template<typename, T ...> class TT, T ...A1, T ...A2>
struct append_<TT<T, A1...>, A2...> {
    using type = TT<T, A1..., A2...>;
};
template<typename T, value_type_of<T>...A>
using append = typename append_<T, A...>::type;

template<typename T, value_type_of<T> ...A> struct prepend_;
template<typename T, template<typename, T ...> class TT, T ...A1, T ...A2>
struct prepend_<TT<T, A1...>, A2...> {
    using type = TT<T, A2..., A1...>;
};
template<typename T, value_type_of<T>...A>
using prepend = typename prepend_<T, A...>::type;

template<typename T> struct size_of_;
template<typename T, template<typename, T ...> class TT, T ...A>
struct size_of_<TT<T, A...>> {
    static constexpr size_t value = sizeof...(A);
};
template<typename T>
static constexpr size_t size_of = size_of_<T>::value;

template<typename T> struct at_;
template<typename T, template<typename, T...> class TT, T ...A>
struct at_<TT<T, A...>> {
    static constexpr T invoke(size_t n) noexcept {
        constexpr T table[sizeof...(A)]{A...};
        return table[n];
    }
};
template<typename T>
constexpr auto at(size_t n) noexcept { return at_<T>::invoke(n); }

template<typename T, template<value_type_of<T>...> class TT> struct apply_;
template<typename T, template<typename, T...> class TT1, T ...A, template<T...> class TT2>
struct apply_<TT1<T, A...>, TT2> {
    using type = TT2<A...>;
};
template<typename T, template<value_type_of<T>...> class TT>
using apply = typename detail::apply_<T, TT>::type;

template<typename T, size_t B, size_t E> struct slice_;
template<typename T, template<typename, T...> class TT, T ...A, size_t B, size_t E>
class slice_<TT<T, A...>, B, E> {
    static constexpr size_t b = B > sizeof...(A) ? sizeof...(A) : B;
    static constexpr size_t e = E > sizeof...(A) ? sizeof...(A) : E;
    using range = make_range<size_t, b, e>;
    template<value_type_of<range> ...A1>
    struct helper {
        using type = TT<T, at<TT<T, A...>>(A1)...>;
    };
public:
    using type = typename apply<range, helper>::type;
};
template<typename T, size_t B = 0, size_t E = size_of<T>, enable_when<(B<=E)> = nullptr>
using slice = typename slice_<T, B, E>::type;

} // namespce detail;

using detail::value_type_of;
using detail::concat;
using detail::make_range;
using detail::append;
using detail::prepend;
using detail::at;
using detail::apply;
using detail::size_of;
using detail::slice;

template<typename T, size_t N>
using head = slice<T, 0, N>;

template<typename T, size_t N = 1>
using tail = slice<T, (N > size_of<T>) ? 0 : size_of<T> - N, size_of<T>>;

template<typename T, size_t N, value_type_of<T> ...A>
using insert = concat<append<head<T, N>, A...>, slice<T, N>>;

} // namespace v1

using namespace v1;

}} // namespace ranunculus::integer_sequence

#endif

