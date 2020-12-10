#pragma once
#include <stdint.h>
#include <functional>
#include "cfg.h"

using cb_t = std::function<void()>;

class Clock {
    public:
        Clock(const uint32_t sr=cfg::sr, const uint32_t ppq=cfg::ppq) : sr{sr}, ppq{ppq}, pp8{ppq >> 1}, pp16{ppq >> 2}, pp32{ppq >> 3} {}

        uint32_t sr {0};
        uint32_t ppq {0};
        uint32_t pp8 {0};
        uint32_t pp16 {0};
        uint32_t pp32 {0};
        uint32_t ticks {0};
        uint32_t pulses {0};
        bool running {false};
        uint32_t bpm {0};
        uint32_t ticks_per_pulse {0};

        cb_t pulse_cb {};
        cb_t quarter_cb {};
        cb_t eigth_cb {};
        cb_t sixteenth_cb {};
        cb_t thirtysecond_cb {};


        void set_bpm(const uint32_t bpm);
        void start();
        void start(const uint32_t bpm);
        void stop();
        void toogle();
        void tick();
        void pulse();
        void call(const cb_t func);

        void set_pulse_callback(const cb_t cb);
        void set_quarter_callback(const cb_t cb);
        void set_eigth_callback(const cb_t cb);
        void set_sixteenth_callback(const cb_t cb);
        void set_thirtysecond_callback(const cb_t cb);
};
