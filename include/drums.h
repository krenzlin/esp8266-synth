#pragma once
#include <stdint.h>
#include "osc.h"
#include "acoustic.h"

const uint8_t BD_NOTE = 35;
const uint8_t SN_NOTE = 38;
const uint8_t HH_NOTE = 44;

class Drums {
    osc::Sampler bd {osc::Sampler(samples::RD_K_2, samples::RD_K_2_len, 1.0)};
    osc::Sampler sn {osc::Sampler(samples::RD_S_9, samples::RD_S_9_len, 0.8)};
    osc::Sampler hh {osc::Sampler(samples::RD_C_R_11, samples::RD_C_R_11_len, 0.3)};

    public:
        void on(const uint32_t note, const uint32_t velocity=127);
        uint16_t sample();
};
