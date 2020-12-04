#include "drums.h"
#include "osc.h"

void Drums::on(const uint32_t note) {
    if (note == BD_NOTE) {
        bd.on(0);
    } else if (note == SN_NOTE) {
        sn.on(0);
    } else if (note == HH_NOTE) {
        hh.on(0);
    }
}

uint16_t Drums::sample() {
    return (bd.sample() + sn.sample() + hh.sample()) / 3;
}
