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


TEST_CASE("velocity_to_volume", "[misc]") {
    REQUIRE(misc::velocity_to_volume(127) == 1.f);
    REQUIRE(misc::velocity_to_volume(0) == 0.f);
    REQUIRE(misc::velocity_to_volume(127 >> 1) == Approx(0.49606f));
}
