#include "catch.hpp"
#include "clock.h"


TEST_CASE("basic interface", "[Clock]") {
    auto sr = 16;
    auto ppq = 8;
    auto bpm = 60;
    auto clock = Clock(sr, ppq);
    clock.set_bpm(bpm);

    SECTION("state after init") {
        REQUIRE(clock.ticks_per_pulse == 2);
        REQUIRE(clock.running == false);
        REQUIRE(clock.ticks == 0);
    }

    SECTION("starting") {
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

    SECTION("ticking") {
        clock.start();
        REQUIRE(clock.ticks == 0);
        clock.tick();
        REQUIRE(clock.ticks == 1);
    }

    SECTION("no ticking while stopped") {
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

TEST_CASE("ticks and pulses", "[Clock]") {
    auto sr = 16;
    auto ppq = 8;
    auto bpm = 60;
    auto clock = Clock(sr, ppq);

    clock.set_bpm(bpm);
    REQUIRE(clock.ticks_per_pulse == 2);
    REQUIRE(clock.ticks == 0);
    REQUIRE(clock.pulses == 0);

    clock.start();
    REQUIRE(clock.ticks == 0);
    REQUIRE(clock.pulses == 0);

    clock.tick();
    REQUIRE(clock.ticks == 1);
    REQUIRE(clock.pulses == 1); // first tick after start is a pulse

    clock.tick();
    REQUIRE(clock.ticks == 0);
    REQUIRE(clock.pulses == 1);

    clock.tick();
    REQUIRE(clock.ticks == 1);
    REQUIRE(clock.pulses == 2);

    clock.tick();
    REQUIRE(clock.ticks == 0);
    REQUIRE(clock.pulses == 2);

    clock.tick();
    REQUIRE(clock.ticks == 1);
    REQUIRE(clock.pulses == 3);
}

TEST_CASE("pulses cycle @ different bpm", "[Clock]") {
    auto sr = 16;
    auto ppq = 8;
    auto bpm = 60;
    auto clock = Clock(sr, ppq);
    clock.set_bpm(bpm);

    SECTION("cycle @ 60bpm") {
        clock.start();
        REQUIRE(clock.ticks == 0);
        clock.tick();
        REQUIRE(clock.ticks == 1);
        clock.tick();
        REQUIRE(clock.ticks == 0);
    }

    SECTION("cycle @ 30bpm") {
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
        bool called_pulse {false};
        bool called_32 {false};
        bool called_16 {false};
        bool called_8 {false};
        bool called_4 {false};
        bool called {false};

        void call() {
            called = true;
        }

        void cb_pulse() {
            called_pulse = true;
        }

        void cb_32() {
            called_32 = true;
        }

        void cb_16() {
            called_16 = true;
        }

        void cb_8() {
            called_8 = true;
        }

        void cb_4() {
            called_4 = true;
        }

        void reset() {
            called_pulse = false;
            called_32 = false;
            called_16 = false;
            called_8 = false;
            called_4 = false;
        }
};

TEST_CASE("calls all callbacks", "[Clock]") {
    auto ppq = 8; // 1/4 = 8 pulses, 1/8 = 4 pulses, 1/16 = 2 pulses, 1/32 = 1 pulse
    auto clock = Clock(0, ppq); // sr is not important

    auto mock = Mock();
    auto cb_pulse = [&]() mutable {mock.cb_pulse();};
    auto cb_32 = [&]() mutable {mock.cb_32();};
    auto cb_16 = [&]() mutable {mock.cb_16();};
    auto cb_8 = [&]() mutable {mock.cb_8();};
    auto cb_4 = [&]() mutable {mock.cb_4();};

    clock.set_pulse_callback(cb_pulse);
    clock.set_thirtysecond_callback(cb_32);
    clock.set_sixteenth_callback(cb_16);
    clock.set_eigth_callback(cb_8);
    clock.set_quarter_callback(cb_4);

    REQUIRE_FALSE(mock.called_pulse);
    REQUIRE_FALSE(mock.called_32);
    REQUIRE_FALSE(mock.called_16);
    REQUIRE_FALSE(mock.called_8);
    REQUIRE_FALSE(mock.called_4);

    clock.start();

    SECTION("full tick cycle") {

        // 1.e.+.a.2
        // ^
        clock.pulse();
        REQUIRE(mock.called_pulse);
        REQUIRE(mock.called_32);
        REQUIRE(mock.called_16);
        REQUIRE(mock.called_8);
        REQUIRE(mock.called_4);
        mock.reset();

        // 1.e.+.a.2
        //  ^
        clock.pulse();
        REQUIRE(mock.called_pulse);
        REQUIRE(mock.called_32);
        REQUIRE_FALSE(mock.called_16);
        REQUIRE_FALSE(mock.called_8);
        REQUIRE_FALSE(mock.called_4);
        mock.reset();

        // 1.e.+.a.2
        //   ^
        clock.pulse();
        REQUIRE(mock.called_pulse);
        REQUIRE(mock.called_32);
        REQUIRE(mock.called_16);
        REQUIRE_FALSE(mock.called_8);
        REQUIRE_FALSE(mock.called_4);
        mock.reset();


        // 1.e.+.a.2
        //    ^
        clock.pulse();
        REQUIRE(mock.called_pulse);
        REQUIRE(mock.called_32);
        REQUIRE_FALSE(mock.called_16);
        REQUIRE_FALSE(mock.called_8);
        REQUIRE_FALSE(mock.called_4);
        mock.reset();

        // 1.e.+.a.2
        //     ^
        clock.pulse();
        REQUIRE(mock.called_pulse);
        REQUIRE(mock.called_32);
        REQUIRE(mock.called_16);
        REQUIRE(mock.called_8);
        REQUIRE_FALSE(mock.called_4);
        mock.reset();

        // 1.e.+.a.2
        //      ^
        clock.pulse();
        REQUIRE(mock.called_pulse);
        REQUIRE(mock.called_32);
        REQUIRE_FALSE(mock.called_16);
        REQUIRE_FALSE(mock.called_8);
        REQUIRE_FALSE(mock.called_4);
        mock.reset();

        // 1.e.+.a.2
        //       ^
        clock.pulse();
        REQUIRE(mock.called_pulse);
        REQUIRE(mock.called_32);
        REQUIRE(mock.called_16);
        REQUIRE_FALSE(mock.called_8);
        REQUIRE_FALSE(mock.called_4);
        mock.reset();

        // 1.e.+.a.2
        //        ^
        clock.pulse();
        REQUIRE(mock.called_pulse);
        REQUIRE(mock.called_32);
        REQUIRE_FALSE(mock.called_16);
        REQUIRE_FALSE(mock.called_8);
        REQUIRE_FALSE(mock.called_4);
        mock.reset();

        // 1.e.+.a.2
        //         ^
        clock.pulse();
        REQUIRE(mock.called_pulse);
        REQUIRE(mock.called_32);
        REQUIRE(mock.called_16);
        REQUIRE(mock.called_8);
        REQUIRE(mock.called_4);
        mock.reset();
    }
}



