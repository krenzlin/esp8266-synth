#include "pattern.h"
#include "patterns.h"
#include "misc.h"

uint8_t rand_trigger(uint32_t pattern, uint32_t instrument, uint32_t step) {
    uint32_t value = beat(pattern, instrument, step);
    if (misc::fast_float_rand() < value / 255.0) {
        return value;
    }
    return 0;
}

void Pattern::init() {
    for (uint32_t i=0; i<steps_; i++) {
        this->bd_[i] = beat(pattern_, BD, i);
    }
    for (uint32_t i=0; i<steps_; i++) {
        this->sn_[i] = beat(pattern_, SN, i);
    }
    for (uint32_t i=0; i<steps_; i++) {
        this->hh_[i] = beat(pattern_, HH, i);
    }
}

void Pattern::step() {
    if (bd_[step_]) drums_->on(BD_NOTE, bd_[step_] >> 1);
    if (sn_[step_]) drums_->on(SN_NOTE, sn_[step_] >> 1);
    if (hh_[step_]) drums_->on(HH_NOTE, hh_[step_] >> 1);

    step_ += 1;
    if (step_ >= steps_) {
        step_ = 0;
    }
}

void Pattern::next_pattern() {
    pattern_ += 1;
    if (pattern_ > 30) {
        pattern_ = 0;
    }

    this->init();
}


void Pattern::randomize_pattern() {
    for (uint32_t i=0; i<steps_; i++) {
        this->bd_[i] = rand_trigger(pattern_, BD, i);
    }
    for (uint32_t i=0; i<steps_; i++) {
        this->sn_[i] = rand_trigger(pattern_, SN, i);
    }
    for (uint32_t i=0; i<steps_; i++) {
        this->hh_[i] = rand_trigger(pattern_, HH, i);
    }
}
