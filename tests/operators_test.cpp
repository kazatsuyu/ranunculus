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

IUTEST(Test, test) {
    hoge a{};
    hoge b{};
    a | b;
}
