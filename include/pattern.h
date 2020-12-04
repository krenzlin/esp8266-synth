#pragma once
#include "drums.h"

class Pattern {
    Drums *drums_;
    uint16_t step_ {0};
    uint32_t pattern_ {11};
    uint32_t steps_ {32};

    public:
        Pattern(Drums *drums) : drums_{drums} {};
        void step();
        void next_pattern();
};
