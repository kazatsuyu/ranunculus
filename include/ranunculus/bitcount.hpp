#ifndef RANUNCULUS_BITCOUNT_HPP
#define RANUNCULUS_BITCOUNT_HPP

#include <limits>

#include "utility.hpp"
#include "arith.hpp"

namespace ranunculus{ namespace bitcount {

namespace v1 {

using arith::convertible_unsigned;
using arith::convertible_unsigned_t;
using arith::to_unsigned;
using arith::unsigned_to;

namespace detail {

template<typename T>
static constexpr uint_fast16_t bit_width = std::numeric_limits<convertible_unsigned_t<T>>::digits;

template<typename T, concepts::unsigned_<T> = nullptr>
static constexpr T popcnt_mask(uint_fast16_t n) noexcept {
    if(n >= bit_width<T>) {
        return std::numeric_limits<T>::max();
    }
    T next = popcnt_mask<T>(n << 1);
    return next ^ (next << n);
}

template<typename T>
constexpr T fill_trailing_one(T value) noexcept {
    auto val = to_unsigned(value);
    for(size_t i = 1; i < bit_width<T>; i <<= 1) {
        val = val | (val>>i);
    }
    return unsigned_to<T>(val);
}

template<size_t N> struct zero_count_magic;

static constexpr int_least8_t ntz_table8[15] = {8,  0, -1,  1,  6, -1, -1,  2,  7, -1,  5, -1, -1,  4,  3};
static constexpr int_least8_t nlz_table8[15] = {8,  7, -1,  6,  1, -1, -1,  5,  0, -1,  2, -1, -1,  3,  4};
template<>
struct zero_count_magic<8> {
    static constexpr uint_fast8_t value = 0x1d;
    static constexpr int_least8_t const* ntz_table = ntz_table8;
    static constexpr int_least8_t const* nlz_table = nlz_table8;
    static constexpr auto shift = 4;
};

static constexpr int_least8_t ntz_table16[31] = {
    16,  0, -1,  1, -1,  8, -1,  2, 14, -1, -1,  9, -1, 11, -1,  3,
    15, -1,  7, -1, 13, -1, 10, -1, -1,  6, 12, -1,  5, -1,  4,
};
static constexpr int_least8_t nlz_table16[31] = {
    16, 15, -1, 14, -1,  7, -1, 13,  1, -1, -1,  6, -1,  4, -1, 12,
     0, -1,  8, -1,  2, -1,  5, -1, -1,  9,  3, -1, 10, -1, 11,
};
template<>
struct zero_count_magic<16> {
    static constexpr uint_fast16_t value = 0x0f2d;
    static constexpr int_least8_t const* ntz_table = ntz_table16;
    static constexpr int_least8_t const* nlz_table = nlz_table16;
    static constexpr auto shift = 11;
};

static constexpr int_least8_t ntz_table32[63] = {
    32,  0, -1,  1, -1, 10, -1,  2, 29, -1, 11, -1, 25, -1, -1,  3,
    30, -1, -1, 23, -1, 12, 14, -1, -1, 26, -1, 16, -1, 19, -1,  4,
    31, -1,  9, -1, 28, -1, 24, -1, -1, 22, -1, 13, -1, 15, 18, -1,
    -1,  8, 27, -1, 21, -1, -1, 17,  7, -1, 20, -1,  6, -1,  5
};
static constexpr int_least8_t nlz_table32[63] = {
    32, 31, -1, 30, -1, 21, -1, 29,  2, -1, 20, -1,  6, -1, -1, 28,
     1, -1, -1,  8, -1, 19, 17, -1, -1,  5, -1, 15, -1, 12, -1, 27,
     0, -1, 22, -1,  3, -1,  7, -1, -1,  9, -1, 18, -1, 16, 13, -1,
    -1, 23,  4, -1, 10, -1, -1, 14, 24, -1, 11, -1, 25, -1, 26
};
template<>
struct zero_count_magic<32> {
    static constexpr uint_fast32_t value = 0x07c56e99;
    static constexpr int_least8_t const* ntz_table = ntz_table32;
    static constexpr int_least8_t const* nlz_table = nlz_table32;
    static constexpr auto shift = 26;
};

static constexpr int_least8_t ntz_table64[127] = {
    64,  0, -1,  1, -1, 12, -1,  2, 60, -1, 13, -1, -1, 53, -1,  3,
    61, -1, -1, 21, -1, 14, -1, 42, -1, 24, 54, -1, -1, 28, -1,  4,
    62, -1, 58, -1, 19, -1, 22, -1, -1, 17, 15, -1, -1, 33, -1, 43,
    -1, 50, -1, 25, 55, -1, -1, 35, -1, 38, 29, -1, -1, 45, -1,  5,
    63, -1, 11, -1, 59, -1, 52, -1, -1, 20, -1, 41, 23, -1, 27, -1,
    -1, 57, 18, -1, 16, -1, 32, -1, 49, -1, -1, 34, 37, -1, 44, -1,
    -1, 10, -1, 51, -1, 40, -1, 26, 56, -1, -1, 31, 48, -1, 36, -1,
     9, -1, 39, -1, -1, 30, 47, -1,  8, -1, -1, 46,  7, -1,  6,
};
static constexpr int_least8_t nlz_table64[127] = {
    64, 63, -1, 62, -1, 51, -1, 61,  3, -1, 50, -1, -1, 10, -1, 60,
     2, -1, -1, 42, -1, 49, -1, 21, -1, 39,  9, -1, -1, 35, -1, 59,
     1, -1,  5, -1, 44, -1, 41, -1, -1, 46, 48, -1, -1, 30, -1, 20,
    -1, 13, -1, 38,  8, -1, -1, 28, -1, 25, 34, -1, -1, 18, -1, 58,
     0, -1, 52, -1,  4, -1, 11, -1, -1, 43, -1, 22, 40, -1, 36, -1,
    -1,  6, 45, -1, 47, -1, 31, -1, 14, -1, -1, 29, 26, -1, 19, -1,
    -1, 53, -1, 12, -1, 23, -1, 37,  7, -1, -1, 32, 15, -1, 27, -1,
    54, -1, 24, -1, -1, 33, 16, -1, 55, -1, -1, 17, 56, -1, 57,
};
template<>
struct zero_count_magic<64> {
    static constexpr uint_fast64_t value = 0x03f0a933adcbd8d1;
    static constexpr int_least8_t const* ntz_table = ntz_table64;
    static constexpr int_least8_t const* nlz_table = nlz_table64;
    static constexpr auto shift = 57;
};

template<typename T>
struct traits {
    using unsigned_type = convertible_unsigned_t<T>;
    static constexpr uint_fast16_t bit_width = detail::bit_width<T>;
    static constexpr uint_fast16_t popcnt_return_mask = fill_trailing_one(bit_width);
    static constexpr unsigned_type popcnt_mask0 = popcnt_mask<unsigned_type>(1 << 0);
    static constexpr unsigned_type popcnt_mask1 = popcnt_mask<unsigned_type>(1 << 1);
    static constexpr unsigned_type popcnt_mask2 = popcnt_mask<unsigned_type>(1 << 2);
    static constexpr unsigned_type magic = zero_count_magic<bit_width>::value;
    static constexpr int_least8_t const* ntz_table = zero_count_magic<bit_width>::ntz_table;
    static constexpr int_least8_t const* nlz_table = zero_count_magic<bit_width>::nlz_table;
};

} // namespace detail

using detail::bit_width;
using detail::fill_trailing_one;

template<typename T, concepts::unsigned_<T> = nullptr>
constexpr uint_fast16_t popcount(T value) noexcept {
    using traits = detail::traits<T>;
    value -= ((value >> 1) & traits::popcnt_mask0);
    value = (value & traits::popcnt_mask1) + ((value >> 2) & traits::popcnt_mask1);
    if(traits::bit_width <= 32) {
        value = value + ((value >> 4) & traits::popcnt_mask2);
    } else {
        value = (value & traits::popcnt_mask2) + ((value >> 4) & traits::popcnt_mask2);
    }
    for(uint_fast16_t i = 8; i < traits::bit_width; i <<= 1) {
        value = value + (value >> i);
    }
    return value & traits::popcnt_return_mask;
}

template<typename T, concepts::not_unsigned<T> = nullptr>
constexpr uint_fast16_t popcount(T value) noexcept {
    return popcount(to_unsigned(value));
}

template<typename T, concepts::unsigned_<T> = nullptr>
constexpr uint_fast16_t nlz(T value) noexcept {
    using traits= detail::traits<T>;
    T val = fill_trailing_one(value);
    return traits::nlz_table[traits::magic*(val^(val>>1))>>traits::shift];
}

template<typename T, concepts::not_unsigned<T> = nullptr>
constexpr uint_fast16_t nlz(T value) noexcept {
    return nlz(to_unsigned(value));
}

template<typename T, concepts::unsigned_<T> = nullptr>
constexpr uint_fast16_t ntz(T value) noexcept {
    using traits= detail::traits<T>;
    return traits::ntz_table[traits::magic*(value&-value)>>traits::shift];
}

template<typename T, concepts::not_unsigned<T> = nullptr>
constexpr uint_fast16_t ntz(T value) noexcept {
    return ntz(to_unsigned(value));
}

} // namespace v1

using namespace v1;

}} // namespace ranunculus::bitcount

#endif

