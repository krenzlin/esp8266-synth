#pragma once
#include <stdint.h>

namespace OSC {

    class Saw {
        uint16_t phase {0};

        public:
            uint16_t sample();
    };
}
