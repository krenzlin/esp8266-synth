#pragma once
#include <stdint.h>

namespace osc {

    class Saw {
        uint16_t phase {0};
        uint16_t p_incr {0};

        public:
            uint16_t sample();
            uint16_t set_note(int note);
    };

    class Sampler {
        uint16_t phase {0};

        public:
            uint16_t sample();
            void on();
    };
}
