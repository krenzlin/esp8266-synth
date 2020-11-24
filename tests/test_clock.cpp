#include "catch.hpp"
#include "clock.h"


TEST_CASE("Clock basics", "[Clock]") {
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

    SECTION("set bpm") {
        auto clock = Clock(44100, 24);
        REQUIRE(clock.ticks_per_pulse == 0);
        clock.set_bpm(120);
        REQUIRE(clock.ticks_per_pulse == 918);
    }

    SECTION("set bpm at start") {
        auto clock = Clock(44100, 24);
        REQUIRE(clock.ticks_per_pulse == 0);
        clock.start(120);
        REQUIRE(clock.ticks_per_pulse == 918);
    }
}


TEST_CASE("Clock pulse cycle", "[Clock]") {

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
}

class Mock {
    public:
        bool called {false};
        void call() {
            called = true;
        }
};


TEST_CASE("Clock callback", "[Clock]") {
    auto clock = Clock(2, 1);
    clock.start(60);
    REQUIRE(clock.ticks_per_pulse == 2);

    SECTION("call function") {
        auto mock = Mock();
        auto cb = [&]() mutable {mock.call();};
        clock.set_pulse_callback(cb);

        clock.tick();
        REQUIRE(clock.ticks == 1);
        REQUIRE(mock.called == false);

        clock.tick();
        REQUIRE(clock.ticks == 0);
        REQUIRE(mock.called == true);
    }
}
