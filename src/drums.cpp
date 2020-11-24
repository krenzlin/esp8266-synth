#include "drums.h"
#include "osc.h"

void Drums::on(uint16_t note) {
    if (note == 35) {
        bd.on(0);
    } else if (note == 38) {
        sn.on(0);
    } else if (note == 44) {
        hh.on(0);
    }
}

uint16_t Drums::sample() {
    uint16_t sample = bd.sample() + sn.sample() + hh.sample();
    return sample >> 1;
}
