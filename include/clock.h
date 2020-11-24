#pragma once
#include <stdint.h>

class Clock {
    public:
        Clock(uint32_t sr=44100, uint16_t ppq=24);


        uint32_t ticks {0};
        bool running {false};
        uint32_t sr {0};
        uint16_t ppq {0};
        uint16_t bpm {0};
        uint32_t ticks_per_pulse {0};

        void set_bpm(uint16_t bpm);
        void start();
        void stop();
        void tick();
};
