#include "osc.h"
#include "luts.h"
#include "samples.h"

uint16_t osc::Saw::set_note(int note) {
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

void osc::Sampler::on() {
    phase = 0;
}

uint16_t osc::Sampler::sample() {
    uint16_t sample {0};

    if (phase < BD16LEN) {
        sample = samples::BD16[phase];
        phase++;
    }

    return sample;
}
