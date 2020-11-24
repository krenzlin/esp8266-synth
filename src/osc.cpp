#include "osc.h"
#include "luts.h"
#include "samples.h"

void osc::Saw::on(uint16_t note) {
    p_incr = lut::mtoincr[note];
}

uint16_t osc::Saw::sample() {
    uint16_t sample = phase;

    phase += p_incr;
    if (phase > 0xFFFF) {
        phase -= 0xFFFF;
    }

    return sample;
}

osc::Sampler::Sampler(const uint16_t sample[], uint32_t len) {
    sample_ = sample;
    len_ = len;
}

void osc::Sampler::on(uint16_t note) {
    index = 0;
}

uint16_t osc::Sampler::sample() {
    uint16_t sample {0x7FFF};

    if (index < len_) {
        sample = sample_[index];
        index++;
    }

    return sample;
}
