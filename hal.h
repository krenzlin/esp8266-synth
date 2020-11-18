#pragma once
#include <stdint.h>

namespace HAL {
    namespace I2S {
        void init(int sr=44100);
        void pdm_write(uint16_t signal);
    }

    namespace WIFI {
        void turn_off();
    }
}
