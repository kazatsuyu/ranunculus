#ifndef RANUNCULUS_COMPARE_GT_HPP
#define RANUNCULUS_COMPARE_GT_HPP

#include "traits.hpp"

namespace ranunculus {
namespace compare {
namespace v1 {

namespace detail {

template<typename T, typename U, require<T, U, gt_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(lhs >  rhs)) { return   lhs >  rhs ; }
template<typename T, typename U, require<T, U, !gt_, tg_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(rhs <  lhs)) { return   rhs <  lhs ; }
template<typename T, typename U, require<T, U, !gt_, !tg_, le_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(lhs <= rhs)) { return !(lhs <= rhs); }
template<typename T, typename U, require<T, U, !gt_, !tg_, !le_, el_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(rhs >= lhs)) { return !(rhs >= lhs); }

template<typename T, typename U, require_t ...A>
using require_gt_0 = require<T, U, !gt_, !tg_, !le_, !el_, A...>;

template<typename T, typename U, require_t ...A>
using require_gt_1 = require_gt_0<T, U, eq_, A...>;
template<typename T, typename U, require_gt_1<T, U, ge_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(lhs == rhs, lhs >= rhs)) { return !(lhs == rhs) &&   lhs >= rhs ; }
template<typename T, typename U, require_gt_1<T, U, !ge_, eg_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(lhs == rhs, rhs <= lhs)) { return !(lhs == rhs) &&   rhs <= lhs ; }
template<typename T, typename U, require_gt_1<T, U, !ge_, !eg_, lt_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(lhs == rhs, lhs <  rhs)) { return !(lhs == rhs  ||   lhs <  rhs); }
template<typename T, typename U, require_gt_1<T, U, !ge_, !eg_, !lt_, tl_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(lhs == rhs, rhs >  lhs)) { return !(lhs == rhs  ||   rhs >  lhs); }

template<typename T, typename U, require_t ...A>
using require_gt_2 = require_gt_0<T, U, !eq_, qe_, A...>;
template<typename T, typename U, require_gt_2<T, U, ge_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(rhs == lhs, lhs >= rhs)) { return !(rhs == lhs) &&   lhs >= rhs ; }
template<typename T, typename U, require_gt_2<T, U, !ge_, eg_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(rhs == lhs, rhs <= lhs)) { return !(rhs == lhs) &&   rhs <= lhs ; }
template<typename T, typename U, require_gt_2<T, U, !ge_, !eg_, lt_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(rhs == lhs, lhs <  rhs)) { return !(rhs == lhs  ||   lhs <  rhs); }
template<typename T, typename U, require_gt_2<T, U, !ge_, !eg_, !lt_, tl_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(rhs == lhs, rhs >  lhs)) { return !(rhs == lhs  ||   rhs >  lhs); }

template<typename T, typename U, require_t ...A>
using require_gt_3 = require_gt_0<T, U, !eq_, !qe_, ne_, A...>;
template<typename T, typename U, require_gt_3<T, U, ge_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(lhs != rhs, lhs >= rhs)) { return   lhs != rhs  &&   lhs >= rhs ; }
template<typename T, typename U, require_gt_3<T, U, !ge_, eg_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(lhs != rhs, rhs <= lhs)) { return   lhs != rhs  &&   rhs <= lhs ; }
template<typename T, typename U, require_gt_3<T, U, !ge_, !eg_, lt_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(lhs != rhs, lhs <  rhs)) { return   lhs != rhs  && !(lhs <  rhs); }
template<typename T, typename U, require_gt_3<T, U, !ge_, !eg_, !lt_, tl_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(lhs != rhs, rhs >  lhs)) { return   lhs != rhs  && !(rhs >  lhs); }

template<typename T, typename U, require_t ...A>
using require_gt_4 = require_gt_0<T, U, !eq_, !qe_, !ne_, en_, A...>;
template<typename T, typename U, require_gt_4<T, U, ge_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(rhs != lhs, lhs >= rhs)) { return   rhs != lhs  &&   lhs >= rhs ; }
template<typename T, typename U, require_gt_4<T, U, !ge_, eg_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(rhs != lhs, rhs <= lhs)) { return   rhs != lhs  &&   rhs <= lhs ; }
template<typename T, typename U, require_gt_4<T, U, !ge_, !eg_, lt_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(rhs != lhs, lhs <  rhs)) { return   rhs != lhs  && !(lhs <  rhs); }
template<typename T, typename U, require_gt_4<T, U, !ge_, !eg_, !lt_, tl_> = nullptr>
constexpr bool gt(const T& lhs, const U& rhs) noexcept(noexcept(rhs != lhs, rhs >  lhs)) { return   rhs != lhs  && !(rhs >  lhs); }
} // namespace detail

using detail::gt;

} // namespace v1
} // namespace compare
} // namespace ranunculus

#endif
