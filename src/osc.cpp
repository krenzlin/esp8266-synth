#include "osc.h"
#include "luts.h"
#include "samples.h"

uint16_t OSC::Saw::set_note(int note) {
    p_incr = LUT::mtoincr[note];
}

uint16_t OSC::Saw::sample() {
    uint16_t sample = phase;

    phase += p_incr;
    if (phase > 0xFFFF) {
        phase -= 0xFFFF;
    }

    return sample;
}

void OSC::Sampler::on() {
    phase = 0;
}

uint16_t OSC::Sampler::sample() {
    uint16_t sample {0};

    if (phase < BD16LEN) {
        sample = BD16[phase];
        phase++;
    }

    return sample;
}
