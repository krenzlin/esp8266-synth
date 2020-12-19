#pragma once
#include "drums.h"

class Pattern {
    Drums *drums_;
    uint16_t step_ {0};
    uint32_t pattern_ {25};
    uint32_t steps_ {32};
    uint32_t bd_[32];
    uint32_t sn_[32];
    uint32_t hh_[32];

    public:
        Pattern(Drums *drums, uint32_t pattern=26) : drums_{drums}, pattern_{pattern} {init();};
        void init();
        void step();
        void reset();
        void next_pattern();
        void randomize_pattern();

};
