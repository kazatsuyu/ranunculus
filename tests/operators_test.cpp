#include <iutest.hpp>
#include <list>
#include <functional>
#include <iostream>
#include "../include/ranunculus/operators.hpp"

using namespace ranunculus::operators::arithmetic;
using namespace ranunculus::operators::conditional;

enum class hoge {};

struct piyo {};

bool operator ==(const piyo&, const piyo&) { return true; }
bool operator >(const piyo&, const piyo&) { return false; }

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

IUTEST(Test, test) {
    hoge a{};
    hoge b{};
    a | b;
    piyo c;
    piyo d;
    c == d;
    c > d;
    c != d;
    c <= d;
}
