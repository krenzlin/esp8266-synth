#include "dsp.h"


uint16_t dsp::volume(const uint16_t sample, float vol) {
    return (uint16_t) ((sample - 0x7FFF) * vol + 0x7FFF);
}
