#include "drums.h"
#include "osc.h"

void Drums::on(const uint32_t note, const uint32_t velocity) {
    if (note == BD_NOTE) {
        bd.on(0, velocity);
    } else if (note == SN_NOTE) {
        sn.on(0, velocity);
    } else if (note == HH_NOTE) {
        hh.on(0, velocity);
    }
}

int16_t Drums::sample() {
    return (bd.sample() + sn.sample() + hh.sample()) / 3;
}

void Drums::set_sampler(osc::Sampler bd, osc::Sampler sn, osc::Sampler hh) {
    this->bd = bd;
    this->sn = sn;
    this->hh = hh;
}
