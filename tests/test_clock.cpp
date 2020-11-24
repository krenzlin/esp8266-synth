#include "catch.hpp"
#include "clock.h"

TEST_CASE("Clock basics") {
    auto clock = Clock();
    clock.set_bpm(100);

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

    SECTION("reset when restarted") {
        clock.start();
        clock.tick();
        REQUIRE(clock.ticks == 1);
        clock.stop();
        clock.start();
        REQUIRE(clock.ticks == 0);
    }
}

TEST_CASE("Clock pulse cycle") {

    SECTION("cycle @ 60bpm") {
        auto clock = Clock(2, 1); // sr, ppq
        clock.set_bpm(60);

        clock.start();
        REQUIRE(clock.ticks == 0);
        clock.tick();
        REQUIRE(clock.ticks == 1);
        clock.tick();
        REQUIRE(clock.ticks == 0);
    }

    SECTION("cycle @ 30bpm") {
        auto clock = Clock(2, 1); // sr, ppq
        clock.set_bpm(30);

        clock.start();
        REQUIRE(clock.ticks == 0);
        clock.tick();
        REQUIRE(clock.ticks == 1);
        clock.tick();
        REQUIRE(clock.ticks == 2);
        clock.tick();
        REQUIRE(clock.ticks == 3);
        clock.tick();
        REQUIRE(clock.ticks == 0);

    }

    SECTION("set bpm -> ticks per pulse") {
        auto clock = Clock(44100, 24);
        clock.set_bpm(120);
        REQUIRE(clock.ticks_per_pulse == 918);
    }
}
