#pragma once
#include <stdint.h>
#include <functional>

using cb_t = std::function<void()>;

class Clock {
    public:
        Clock(const uint32_t sr=44100, const uint32_t ppq=24);

        uint32_t ticks {0};
        bool running {false};
        uint32_t sr {0};
        uint32_t ppq {0};
        uint32_t bpm {0};
        uint32_t ticks_per_pulse {0};

        cb_t pulse_cb {};

        void set_bpm(const uint32_t bpm);
        void start();
        void start(const uint32_t bpm);
        void stop();
        void tick();

        void set_pulse_callback(const cb_t cb);
};
