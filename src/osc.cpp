#include "osc.h"
#include "luts.h"
#include "samples.h"

uint16_t OSC::Saw::set_note(int note) {
    p_incr = LUT::mtoincr[note];
}

uint16_t OSC::Saw::sample() {
    auto sample = phase;

    phase += p_incr;
    if (phase > 0xFFFF) {
        phase -= 0xFFFF;
    }

    return sample;
}

uint16_t OSC::Sampler::sample() {
    auto sample = BD16[phase];

    phase++;
    if (phase >= BD16LEN) {
        phase = 0;
    }

    return sample;
}
