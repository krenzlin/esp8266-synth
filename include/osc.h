#pragma once
#include <stdint.h>

namespace osc {
    const uint16_t ZERO = 0xFFFF >> 1;

    class Saw {
        uint16_t phase_ {0};
        uint16_t p_incr_ {0};

        public:
            uint16_t sample();
            void on(const uint32_t note);
    };

    class Sampler {
        const uint16_t *sample_;
        uint32_t len_ {0};
        uint32_t index_ {0};
        uint32_t end_ {0};
        float max_vol_{1.0f};
        float vol_ {1.0f};

        public:
            Sampler(const uint16_t sample[], const uint32_t len, const float vol=1.f) :
                sample_{sample},
                len_{len},
                index_{len},
                end_{len},
                max_vol_{vol},
                vol_{vol}
                {};
            uint16_t sample();
            void on(const uint32_t note);
    };
}
