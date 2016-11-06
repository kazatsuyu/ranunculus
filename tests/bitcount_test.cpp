#include <iutest.hpp>
#include <list>
#include <functional>
#include <iostream>
#include "../include/ranunculus/bitcount.hpp"


namespace bc = ranunculus::bitcount;

static_assert(bc::popcount(-1) == 32, "Something wrong!");
static_assert(bc::popcount(-1ll) == bc::bit_width<long long>, "Something wrong!");
static_assert(bc::popcount(0x0123456789abcdefll) == 32, "Something wrong!");

IUTEST(BitCountTest, testBitCount) {
    
}
