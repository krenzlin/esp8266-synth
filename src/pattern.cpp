#include "pattern.h"
#include "patterns.h"
#include "misc.h"

bool rand_trigger(uint32_t pattern, uint32_t instrument, uint32_t step) {
    uint32_t value = beat(pattern, instrument, step);
    if (misc::fast_float_rand() < value / 255.0) {
        return true;
    }
    return false;
}

void Pattern::step() {
    if (rand_trigger(pattern_, BD, step_)) drums_->on(BD_NOTE);
    if (rand_trigger(pattern_, SN, step_)) drums_->on(SN_NOTE);
    if (rand_trigger(pattern_, HH, step_)) drums_->on(HH_NOTE);

    step_ += 1;
    if (step_ >= steps_) {
        step_ = 0;
    }
}

void Pattern::next_pattern() {
    pattern_ += 1;
    if (pattern_ >= 25) {
        pattern_ = 0;
    }
}
