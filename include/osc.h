#pragma once
#include <stdint.h>

namespace osc {

    class Saw {
        uint16_t phase {0};
        uint16_t p_incr {0};

        public:
            uint16_t sample();
            void on(const uint32_t note);
    };

    class Sampler {
        uint32_t index {0};
        uint32_t len_ {0};
        const uint16_t *sample_;

        public:
            Sampler(const uint16_t sample[], const uint32_t len);
            uint16_t sample();
            void on(const uint32_t note);
    };
}
