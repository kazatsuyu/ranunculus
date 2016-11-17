#include <iutest.hpp>
#include <list>
#include <functional>
#include <iostream>
#include "../include/ranunculus/operators.hpp"

using namespace ranunculus::operators::arithmetic;
using namespace ranunculus::operators::conditional;


enum class hoge {};

struct piyo {};

constexpr bool operator ==(const piyo&, const piyo&) noexcept { return true; }
constexpr bool operator >(const piyo&, const piyo&) noexcept { return false; }

namespace ranunculus { namespace operators {

template<>
struct implement_flags<hoge> {
    static constexpr bool arithmetic = true;
};

template<>
struct implement_flags<piyo> {
    static constexpr bool conditional = true;
};

}} // namespace ranunculus::operators

constexpr piyo c{}, d{};

static_assert(c == d, "");
static_assert(!(c != d), "");
static_assert(c <= d, "");
static_assert(!(c > d), "");

struct test1 {};
struct test2 {};
struct test3 {};
struct test4 {};
struct test5 {};
struct test6 {};

namespace ranunculus { namespace operators {

template<> struct implement_flags<test1> { static constexpr bool conditional = true; };
template<> struct implement_flags<test2> { static constexpr bool conditional = true; };
template<> struct implement_flags<test3> { static constexpr bool conditional = true; };
template<> struct implement_flags<test4> { static constexpr bool conditional = true; };

}} // namespace ranunculus::operators
constexpr bool operator < (test1, test1) noexcept { return false; }
constexpr bool operator <= (test2, test2) noexcept { return true; }
constexpr bool operator >= (test3, test3) noexcept { return true; }
constexpr bool operator > (test4, test4) noexcept { return false; }
static_assert(test1{} == test1{}, "");
static_assert(!(test1{} != test1{}), "");
static_assert(!(test1{} < test1{}), "");
static_assert(test1{} <= test1{}, "");
static_assert(test1{} >= test1{}, "");
static_assert(!(test1{} > test1{}), "");
static_assert(test2{} == test2{}, "");
static_assert(!(test2{} != test2{}), "");
static_assert(!(test2{} < test2{}), "");
static_assert(test2{} <= test2{}, "");
static_assert(test2{} >= test2{}, "");
static_assert(!(test2{} > test2{}), "");
static_assert(test3{} == test3{}, "");
static_assert(!(test3{} != test3{}), "");
static_assert(!(test3{} < test3{}), "");
static_assert(test3{} <= test3{}, "");
static_assert(test3{} >= test3{}, "");
static_assert(!(test3{} > test3{}), "");
static_assert(test4{} == test4{}, "");
static_assert(!(test4{} != test4{}), "");
static_assert(!(test4{} < test4{}), "");
static_assert(test4{} <= test4{}, "");
static_assert(test4{} >= test4{}, "");
static_assert(!(test4{} > test4{}), "");


IUTEST(Test, test) {
    hoge a{};
    hoge b{};
    a | b;
}
