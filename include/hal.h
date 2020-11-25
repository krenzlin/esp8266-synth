#pragma once
#include <stdint.h>

namespace hal {
    namespace i2s {
        void init(const uint32_t sr=44100);
        void write(const uint32_t sample);
        void write(const uint32_t left, const uint32_t right);
    }

    namespace wifi {
        void turn_off();
    }

    void set_cpu_freq(const uint8_t freq);
}
