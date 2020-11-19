#pragma once
#include <stdint.h>

namespace HAL {
    namespace I2S {
        void init(int sr=44100);
        void write(uint32_t sample);
    }

    namespace WIFI {
        void turn_off();
    }
}
