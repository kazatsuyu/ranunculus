#ifndef RANUNCULUS_COMPARE_GE_HPP
#define RANUNCULUS_COMPARE_GE_HPP

#include "traits.hpp"

namespace ranunculus {
namespace compare {
namespace v1 {

namespace detail {
template<typename T, typename U, require<T, U, ge_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(lhs >= rhs)) { return lhs >= rhs; }
template<typename T, typename U, require<T, U, !ge_, eg_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(rhs <= lhs)) { return rhs <= lhs; }
template<typename T, typename U, require<T, U, !ge_, !eg_, lt_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(lhs < rhs)) { return !(lhs < rhs); }
template<typename T, typename U, require<T, U, !ge_, !eg_, !lt_, tl_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(rhs > lhs)) { return !(rhs > lhs); }

template<typename T, typename U, require_t ...A>
using require_ge_0 = require<T, U, !ge_, !eg_, !lt_, !tl_, A...>;

template<typename T, typename U, require_t ...A>
using require_ge_1 = require_ge_0<T, U, eq_, A...>;
template<typename T, typename U, require_ge_1<T, U, gt_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(lhs == rhs, lhs >  rhs)) { return   lhs == rhs  ||   lhs >  rhs ; }
template<typename T, typename U, require_ge_1<T, U, !gt_, tg_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(lhs == rhs, rhs <  lhs)) { return   lhs == rhs  ||   rhs <  lhs ; }
template<typename T, typename U, require_ge_1<T, U, !gt_, !tg_, le_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(lhs == rhs, lhs <= rhs)) { return   lhs == rhs  || !(lhs <= rhs); }
template<typename T, typename U, require_ge_1<T, U, !gt_, !tg_, !le_, el_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(lhs == rhs, rhs >= lhs)) { return   lhs == rhs  || !(rhs >= lhs); }

template<typename T, typename U, require_t ...A>
using require_ge_2 = require_ge_0<T, U, !eq_, qe_, A...>;
template<typename T, typename U, require_ge_2<T, U, gt_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(rhs == lhs, lhs >  rhs)) { return   rhs == lhs  ||   lhs >  rhs ; }
template<typename T, typename U, require_ge_2<T, U, !gt_, tg_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(rhs == lhs, rhs <  lhs)) { return   rhs == lhs  ||   rhs <  lhs ; }
template<typename T, typename U, require_ge_2<T, U, !gt_, !tg_, le_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(rhs == lhs, lhs <= rhs)) { return   rhs == lhs  || !(lhs <= rhs); }
template<typename T, typename U, require_ge_2<T, U, !gt_, !tg_, !le_, el_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(rhs == lhs, rhs >= lhs)) { return   rhs == lhs  || !(rhs >= lhs); }

template<typename T, typename U, require_t ...A>
using require_ge_3 = require_ge_0<T, U, !eq_, !qe_, ne_, A...>;
template<typename T, typename U, require_ge_3<T, U, gt_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(lhs != rhs, lhs >  rhs)) { return !(lhs != rhs) ||   rhs >  rhs ; }
template<typename T, typename U, require_ge_3<T, U, !gt_, tg_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(lhs != rhs, rhs <  lhs)) { return !(lhs != rhs) ||   rhs <  rhs ; }
template<typename T, typename U, require_ge_3<T, U, !gt_, !tg_, le_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(lhs != rhs, lhs <= rhs)) { return !(lhs != rhs  &&   lhs <= lhs); }
template<typename T, typename U, require_ge_3<T, U, !gt_, !tg_, !le_, el_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(lhs != rhs, rhs >= lhs)) { return !(lhs != rhs  &&   rhs >= lhs); }

template<typename T, typename U, require_t ...A>
using require_ge_4 = require_ge_0<T, U, !eq_, !qe_, !ne_, en_, A...>;
template<typename T, typename U, require_ge_4<T, U, gt_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(rhs != lhs, lhs >  rhs)) { return !(rhs != lhs) ||   lhs >  rhs ; }
template<typename T, typename U, require_ge_4<T, U, !gt_, tg_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(rhs != lhs, rhs <  lhs)) { return !(rhs != lhs) ||   rhs <  lhs ; }
template<typename T, typename U, require_ge_4<T, U, !gt_, !tg_, le_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(rhs != lhs, lhs <= rhs)) { return !(rhs != lhs  &&   lhs <= rhs); }
template<typename T, typename U, require_ge_4<T, U, !gt_, !tg_, !le_, el_> = nullptr>
constexpr bool ge(const T& lhs, const U& rhs) noexcept(noexcept(rhs != lhs, rhs >= lhs)) { return !(rhs != lhs  &&   rhs >= lhs); }
} // namespace detail

using detail::ge;

} // namespace v1
} // namespace compare
} // namespace ranunculus

#endif
