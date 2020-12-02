#include "osc.h"
#include "luts.h"


void osc::Saw::on(const uint32_t note) {
    p_incr = lut::mtoincr[note];
}

uint16_t osc::Saw::sample() {
    uint16_t sample = phase;

    phase += p_incr;
    if (phase > 0xFFFF) {  // compiler will optimize this away as int16 wraps around 0xFFFF
        phase -= 0xFFFF;
    }

    return sample;
}

void osc::Sampler::on(const uint32_t note) {
    index = 0;
}

uint16_t osc::Sampler::sample() {
    uint16_t sample {osc::ZERO};

    if (index < len_) {
        sample = sample_[index];
        index++;
    }

    return sample;
}
