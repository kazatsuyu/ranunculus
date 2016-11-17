#ifndef RANUNCULUS_COMPARE_EQ_HPP
#define RANUNCULUS_COMPARE_EQ_HPP

#include "traits.hpp"

namespace ranunculus {
namespace compare {
namespace v1 {

namespace detail {
template<typename T, typename U, require<T, U, eq_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(lhs == rhs)) { return lhs == rhs; }
template<typename T, typename U, require<T, U, !eq_, qe_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(rhs == lhs)) { return rhs == lhs; }
template<typename T, typename U, require<T, U, !eq_, !qe_, ne_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(lhs != rhs)) { return !(lhs != rhs); }
template<typename T, typename U, require<T, U, !eq_, !qe_, !ne_, en_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(rhs != lhs)) { return !(rhs != lhs); }

template<typename T, typename U, require_t ...A>
using require_eq_0 = require<T, U, !eq_, !qe_, !ne_, !en_, A...>;

template<typename T, typename U, require_t ...A>
using require_eq_1 = require_eq_0<T, U, lt_, A...>;
template<typename T, typename U, require_eq_1<T, U, gt_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(lhs <  rhs, lhs >  rhs)) { return !(lhs <  rhs  ||   lhs >  rhs); }
template<typename T, typename U, require_eq_1<T, U, !gt_, tg_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(lhs <  rhs, rhs <  lhs)) { return !(lhs <  rhs  ||   rhs <  lhs); }
template<typename T, typename U, require_eq_1<T, U, !gt_, !tg_, le_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(lhs <  rhs, lhs <= rhs)) { return !(lhs <  rhs) &&   lhs <= rhs ; }
template<typename T, typename U, require_eq_1<T, U, !gt_, !le_, !le_, el_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(lhs <  rhs, rhs >= lhs)) { return !(lhs <  rhs) &&   rhs >= lhs ; }

template<typename T, typename U, require_t ...A>
using require_eq_2 = require_eq_0<T, U, !lt_, tl_, A...>;
template<typename T, typename U, require_eq_2<T, U, gt_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(rhs >  lhs, lhs >  rhs)) { return !(rhs >  lhs  ||   lhs >  rhs); }
template<typename T, typename U, require_eq_2<T, U, !gt_, tg_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(rhs >  lhs, rhs <  lhs)) { return !(rhs >  lhs  ||   rhs <  lhs); }
template<typename T, typename U, require_eq_2<T, U, !gt_, !tg_, le_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(rhs >  lhs, lhs <= rhs)) { return !(rhs >  lhs) &&   lhs <= rhs ; }
template<typename T, typename U, require_eq_2<T, U, !gt_, !tg_, !le_, el_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(rhs >  lhs, rhs >= lhs)) { return !(rhs >  lhs) &&   rhs >= lhs ; }

template<typename T, typename U, require_t ...A>
using require_eq_3 = require_eq_0<T, U, !lt_, !tl_, ge_, A...>;
template<typename T, typename U, require_eq_3<T, U, gt_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(lhs >= rhs, lhs >  rhs)) { return   lhs >= rhs  && !(lhs >  rhs); }
template<typename T, typename U, require_eq_3<T, U, !gt_, tg_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(lhs >= rhs, lhs <  rhs)) { return   lhs >= rhs  && !(rhs <  lhs); }
template<typename T, typename U, require_eq_3<T, U, !gt_, !tg_, le_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(lhs >= rhs, rhs <= lhs)) { return   lhs >= rhs  &&   lhs <= rhs ; }
template<typename T, typename U, require_eq_3<T, U, !gt_, !tg_, !le_, el_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(lhs >= rhs, rhs >= lhs)) { return   lhs >= rhs  &&   rhs >= lhs ; }

template<typename T, typename U, require_t ...A>
using require_eq_4 = require_eq_0<T, U, !lt_, !tl_, !ge_, eg_, A...>;
template<typename T, typename U, require_eq_4<T, U, gt_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(rhs <= lhs, lhs >  rhs)) { return   rhs <= lhs  && !(lhs >  rhs); }
template<typename T, typename U, require_eq_4<T, U, !gt_, tg_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(rhs <= lhs, lhs <  rhs)) { return   rhs <= lhs  && !(lhs <  rhs); }
template<typename T, typename U, require_eq_4<T, U, !gt_, !tg_, le_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(rhs <= lhs, rhs <= lhs)) { return   rhs <= lhs  &&   lhs <= rhs ; }
template<typename T, typename U, require_eq_4<T, U, !gt_, !tg_, !le_, el_> = nullptr>
constexpr bool eq(const T& lhs, const U& rhs) noexcept(noexcept(rhs <= lhs, rhs >= lhs)) { return   rhs <= lhs  &&   rhs >= lhs ; }

} // namespace detail

using detail::eq;

} // namespace v1
} // namespace compare
} // namespace ranunculus

#endif
