#ifndef RANUNCULUS_COMPARE_LE_HPP
#define RANUNCULUS_COMPARE_LE_HPP

#include "traits.hpp"

namespace ranunculus {
namespace compare {
namespace v1 {

namespace detail {
template<typename T, typename U, require<T, U, le_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(lhs <= rhs)) { return lhs <= rhs; }
template<typename T, typename U, require<T, U, !le_, el_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(rhs >= lhs)) { return rhs >= lhs; }
template<typename T, typename U, require<T, U, !le_, !el_, gt_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(lhs > rhs)) { return !(lhs > rhs); }
template<typename T, typename U, require<T, U, !le_, !el_, !gt_, tg_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(rhs < lhs)) { return !(rhs < lhs); }

template<typename T, typename U, require_t ...A>
using require_le_0 = require<T, U, !le_, !el_, !gt_, !tg_, A...>;

template<typename T, typename U, require_t ...A>
using require_le_1 = require_le_0<T, U, eq_, A...>;
template<typename T, typename U, require_le_1<T, U, lt_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(lhs == rhs, lhs <  rhs)) { return   lhs == rhs  ||   lhs <  rhs ; }
template<typename T, typename U, require_le_1<T, U, !lt_, tl_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(lhs == rhs, rhs >  lhs)) { return   lhs == rhs  ||   rhs >  lhs ; }
template<typename T, typename U, require_le_1<T, U, !lt_, !tl_, ge_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(lhs == rhs, lhs >= rhs)) { return   lhs == rhs  || !(lhs >= rhs); }
template<typename T, typename U, require_le_1<T, U, !lt_, !tl_, !ge_, eg_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(lhs == rhs, rhs <= lhs)) { return   lhs == rhs  || !(rhs <= lhs); }

template<typename T, typename U, require_t ...A>
using require_le_2 = require_le_0<T, U, !eq_, qe_, A...>;
template<typename T, typename U, require_le_2<T, U, lt_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(rhs == lhs, lhs <  rhs)) { return   rhs == lhs  ||   lhs <  rhs ; }
template<typename T, typename U, require_le_2<T, U, !lt_, tl_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(rhs == lhs, rhs >  lhs)) { return   rhs == lhs  ||   rhs >  lhs ; }
template<typename T, typename U, require_le_2<T, U, !lt_, !tl_, ge_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(rhs == lhs, lhs >= rhs)) { return   rhs == lhs  || !(lhs >= rhs); }
template<typename T, typename U, require_le_2<T, U, !lt_, !tl_, !ge_, eg_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(rhs == lhs, rhs <= lhs)) { return   rhs == lhs  || !(rhs <= lhs); }

template<typename T, typename U, require_t ...A>
using require_le_3 = require_le_0<T, U, !eq_, !qe_, ne_, A...>;
template<typename T, typename U, require_le_3<T, U, lt_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(lhs != rhs, lhs <  rhs)) { return !(lhs != rhs) ||   lhs <  rhs ; }
template<typename T, typename U, require_le_3<T, U, !lt_, tl_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(lhs != rhs, rhs >  lhs)) { return !(lhs != rhs) ||   rhs >  lhs ; }
template<typename T, typename U, require_le_3<T, U, !lt_, !tl_, ge_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(lhs != rhs, lhs >= rhs)) { return !(lhs != rhs  &&   lhs >= rhs); }
template<typename T, typename U, require_le_3<T, U, !lt_, !tl_, !ge_, eg_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(lhs != rhs, rhs <= lhs)) { return !(lhs != rhs  &&   rhs <= lhs); }

template<typename T, typename U, require_t ...A>
using require_le_4 = require_le_0<T, U, !eq_, !qe_, !ne_, en_, A...>;
template<typename T, typename U, require_le_4<T, U, lt_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(rhs != lhs, lhs <  rhs)) { return !(rhs != lhs) ||   lhs <  rhs ; }
template<typename T, typename U, require_le_4<T, U, !lt_, tl_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(rhs != lhs, rhs >  lhs)) { return !(rhs != lhs) ||   rhs >  lhs ; }
template<typename T, typename U, require_le_4<T, U, !lt_, !tl_, ge_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(rhs != lhs, lhs >= rhs)) { return !(rhs != lhs  &&   lhs >= rhs); }
template<typename T, typename U, require_le_4<T, U, !lt_, !tl_, !ge_, eg_> = nullptr>
constexpr bool le(const T& lhs, const U& rhs) noexcept(noexcept(rhs != lhs, rhs <= lhs)) { return !(rhs != lhs  &&   rhs <= lhs); }
} // namespace detail

using detail::le;

} // namespace v1
} // namespace compare
} // namespace ranunculus

#endif
