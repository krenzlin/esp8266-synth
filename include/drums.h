#pragma once
#include <stdint.h>
#include "osc.h"
#include "808.h"

const uint8_t BD_NOTE = 35;
const uint8_t SN_NOTE = 38;
const uint8_t HH_NOTE = 44;

class Drums {
    osc::Sampler bd {osc::Sampler(samples::Kick13_mugent, samples::Kick13_mugent_len, 1.0)};
    osc::Sampler sn {osc::Sampler(samples::Snare7_mugent, samples::Snare7_mugent_len, 0.6)};
    osc::Sampler hh {osc::Sampler(samples::CH5_mugent, samples::CH5_mugent_len, 0.3)};

    public:
        void on(const uint32_t note);
        uint16_t sample();
};
