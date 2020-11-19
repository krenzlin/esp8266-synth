#include "osc.h"
#include "luts.h"

uint16_t OSC::Saw::sample() {
    phase += LUT::mtoincr[72];
    if (phase > 0xFFFF) {
        phase -= 0xFFFF;
    }
    return phase;
}
