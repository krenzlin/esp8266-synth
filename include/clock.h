#pragma once
#include <stdint.h>

class Clock {
    public:
        uint32_t ticks {0};
        bool running {false};

        void start();
        void stop();
        void tick();
};
