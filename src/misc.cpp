#include "misc.h"

const uint16_t MAX_16BIT {0xFFFF};

/*
Convert PCM sample into PCM with 32x oversampling

c.f. https://en.wikipedia.org/wiki/Pulse-density_modulation#Algorithm
*/
uint32_t misc::pcm_to_pdm(uint16_t sample) {
    static uint16_t qe {MAX_16BIT >> 1};
    uint32_t pdm {0};

    for (auto i=0; i<32; i++) {
        pdm <<= 1;
        if (sample >= qe) {
            pdm |= 1;
            qe += MAX_16BIT;
        }
        qe -= sample;
    }

    return pdm;
}
