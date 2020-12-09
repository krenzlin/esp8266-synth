#include "drummer.h"
#include "misc.h"


RandomDrummer::RandomDrummer(Drums *drums) {
    this->drums_ = drums;
    this->next_pattern();
}

void RandomDrummer::next_pattern() {
    for (uint32_t i=0; i<steps_; i++) {
        this->bd_[i] = (misc::fast_float_rand() > 0.8);
    }

    for (uint32_t i=0; i<steps_; i++) {
        this->sn_[i] = (misc::fast_float_rand() > 0.8);
    }

    for (uint32_t i=0; i<steps_; i++) {
        this->hh_[i] = (misc::fast_float_rand() > 0.5);
    }
}


void RandomDrummer::step() {
    if (bd_[step_] > 0) drums_->on(35);
    if (sn_[step_] > 0) drums_->on(38);
    if (hh_[step_] > 0) drums_->on(44);

    step_ += 1;
    if (step_ >= 32) {
        step_ = 0;
    }
}
