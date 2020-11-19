#include "osc.h"
#include "luts.h"

uint16_t OSC::Saw::sample() {
    auto sample = phase;

    phase += LUT::mtoincr[72];
    if (phase > 0xFFFF) {
        phase -= 0xFFFF;
    }
    return sample;
}
