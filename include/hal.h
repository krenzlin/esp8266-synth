#pragma once
#include <stdint.h>

namespace hal {
    namespace i2s {
        void init(int sr=44100);
        void write(uint32_t sample);
        void write(uint16_t left, uint16_t right);
    }

    namespace wifi {
        void turn_off();
    }

    void set_cpu_freq(uint8_t freq);
}
