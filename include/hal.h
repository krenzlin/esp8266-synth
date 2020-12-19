#pragma once
#include <stdint.h>
#include "cfg.h"

namespace hal {
    namespace i2s {
        void init(const uint32_t sr=cfg::sr);
        void write(const uint32_t sample);
        void write(const uint32_t left, const uint32_t right);
    }

    namespace wifi {
        void turn_off();
    }

    void set_cpu_freq(const uint8_t freq);

    class Button {
        public:
            uint8_t pin_;
            uint8_t history_ {0};

            void update();

            Button(uint8_t pin);
            bool is_pressed();
            bool is_held();
    };
}
