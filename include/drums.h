#pragma once
#include <stdint.h>
#include "osc.h"
#include "808.h"

class Drums {
    osc::Sampler bd {osc::Sampler(samples::Kick13_mugent, samples::Kick13_mugent_len)};
    osc::Sampler sn {osc::Sampler(samples::Snare7_mugent, samples::Snare7_mugent_len)};
    osc::Sampler hh {osc::Sampler(samples::CH5_mugent, samples::CH5_mugent_len)};

    public:
        void on(const uint32_t note);
        uint16_t sample();
};
