#pragma once
#include "drums.h"

class Pattern {
    Drums *drums_;
    uint16_t steps {0};
    uint32_t pattern {0};

    public:
        Pattern(Drums *drums) : drums_{drums} {};

    void step();
};
