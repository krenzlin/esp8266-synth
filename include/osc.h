#pragma once
#include <stdint.h>

namespace osc {

    class Saw {
        uint16_t phase {0};
        uint16_t p_incr {0};

        public:
            uint16_t sample();
            uint16_t on(uint16_t note);
    };

    class Sampler {
        uint32_t index {0};

        public:
            uint16_t sample();
            void on(uint16_t note);
    };
}
