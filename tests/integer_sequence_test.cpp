#include "../include/integer_sequence.hpp"

namespace is = ranunculus::integer_sequence;

using t1 = is::value_type_of<std::integer_sequence<int>>;
using t2 = is::concat<std::integer_sequence<int, 0>, std::integer_sequence<int, 1>>;
using t3 = is::make_range<int, 10, 100>;
using t4 = is::append<t3, 0, 1, 2>;
using t5 = is::prepend<t3, 3, 4, 5>;
static constexpr auto t6 = is::at<t5>(10);
template<int ...> struct test {};
using t7 = is::apply<t5, test>;
static constexpr auto t8 = is::size_of<t5>;
using t9 = is::slice<t5, 20, 30>;
using t10 = is::head<t9, 2>;
using t11 = is::tail<t9, 3>;
using t12 = is::insert<t9, 3, 1, 4>;

int main() {}
