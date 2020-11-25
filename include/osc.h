#pragma once
#include <stdint.h>

namespace osc {
    const uint16_t ZERO = 0xFFFF >> 1;

    class Saw {
        uint16_t phase {0};
        uint16_t p_incr {0};

        public:
            uint16_t sample();
            void on(const uint32_t note);
    };

    class Sampler {
        const uint16_t *sample_;
        uint32_t len_ {0};
        uint32_t index {0};

        public:
            Sampler(const uint16_t sample[], const uint32_t len) : sample_{sample}, len_{len}, index{len} {};
            uint16_t sample();
            void on(const uint32_t note);
    };
}
