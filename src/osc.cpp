#include "osc.h"
#include "luts.h"

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
