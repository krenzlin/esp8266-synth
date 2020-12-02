#pragma once
#include <stdint.h>
#include "config.h"

namespace hal {
    namespace i2s {
        void init(const uint32_t sr=config::sr);
        void write(const uint32_t sample);
        void write(const uint32_t left, const uint32_t right);
    }

    namespace wifi {
        void turn_off();
    }

    void set_cpu_freq(const uint8_t freq);

    class Button {
        public:
            uint8_t pin;
            uint32_t history {0};

            void update();

            Button();
            bool is_pressed();
    };
}
