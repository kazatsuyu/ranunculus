#include "../include/ranunculus/type_sequence.hpp"
#include <tuple>

namespace ts = ranunculus::type_sequence;

using t2 = ts::concat<std::tuple<char>, std::tuple<char>>;
using t3 = ts::make_type_sequence<std::tuple, int, 100>;
using t4 = ts::append<t3, char, short, long>;
using t5 = ts::prepend<t3, long long, float, double>;
using t6 = ts::at<t5, 10>;
template<typename ...> struct test {};
using t7 = ts::assign<t5, test>;
static constexpr auto t8 = ts::size_of<t5>;
using t9 = ts::slice<t5, 20, 30>;
using t10 = ts::head<t9, 2>;
using t11 = ts::tail<t9, 3>;
using t12 = ts::insert<t9, 3, void, std::nullptr_t>;
using t13 = ts::map<t12, std::add_lvalue_reference>;

