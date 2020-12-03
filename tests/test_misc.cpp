#include "catch.hpp"
#include "misc.h"


TEST_CASE("fast_rand", "[Misc]") {
    for (auto i=0; i<100; i++) {
        auto x = misc::fast_rand();
        REQUIRE(x >= 0);
        REQUIRE(x <= 0xFFFFFFFF);
    }
}


TEST_CASE("fast_float_rand", "[Misc]") {
    for (auto i=0; i<100; i++) {
        auto x = misc::fast_float_rand();
        REQUIRE(x >= 0.f);
        REQUIRE(x <= 1.f);
    }
}
