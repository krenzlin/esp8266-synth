#pragma once
#include "drums.h"

class RandomDrummer {
    Drums *drums_;
    uint32_t step_ {0};
    uint32_t steps_ {32};
    uint32_t bd_[32];
    uint32_t sn_[32];
    uint32_t hh_[32];

    public:
        RandomDrummer(Drums *drums);
        void step();
        void next_pattern();
};
