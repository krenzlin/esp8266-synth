#pragma once
#include <stdint.h>
#include "osc.h"
#include "samples.h"

class Drums {
    osc::Sampler bd {osc::Sampler(samples::BD16, samples::BD16LEN)};
    osc::Sampler sn {osc::Sampler(samples::SD16, samples::SD16LEN)};
    osc::Sampler hh {osc::Sampler(samples::HH16, samples::HH16LEN)};

    public:
        void on(uint16_t note);
        uint16_t sample();
};
