#include "catch.hpp"
#include "clock.h"

TEST_CASE("Clock") {
    auto clock = Clock();

    SECTION("after init") {
        REQUIRE(clock.running == false);
        REQUIRE(clock.ticks == 0);
    }

    SECTION("start") {
        clock.start();
        REQUIRE(clock.running == true);
        REQUIRE(clock.ticks == 0);
    }

    SECTION("stopping") {
        clock.start();
        clock.stop();
        REQUIRE(clock.running == false);
        REQUIRE(clock.ticks == 0);
    }

    SECTION("tick") {
        clock.start();
        REQUIRE(clock.ticks == 0);
        clock.tick();
        REQUIRE(clock.ticks == 1);
    }

    SECTION("tick while stopped") {
        clock.stop();
        REQUIRE(clock.ticks == 0);
        clock.tick();
        REQUIRE(clock.ticks == 0);
    }
}
