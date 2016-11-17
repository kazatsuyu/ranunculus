#include <iutest.hpp>
#include "../include/ranunculus/array_view.hpp"

namespace av = ranunculus::array_view;

IUTEST(ArrayViewTest, testFixedArray) {

    char buffer[100];
    av::fixed_view<char, 10> view(buffer);
    IUTEST_ASSERT_THROW(view.at(10), std::out_of_range);
    av::flex_view<char> view2(view);
    IUTEST_ASSERT_NO_THROW(view.at(9));
    view2.shrink(5);
    IUTEST_ASSERT_THROW(view.at(9), std::out_of_range);
}
