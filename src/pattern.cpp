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
    if (rand_trigger(pattern, 0, steps)) drums_->on(35);
    if (rand_trigger(pattern, 1, steps)) drums_->on(38);
    if (rand_trigger(pattern, 2, steps)) drums_->on(44);

    steps += 1;
    if (steps >= 32) {
        steps = 0;
    }
}

void Pattern::next_pattern() {
    pattern += 1;
    if (pattern >= 25) {
        pattern = 0;
    }
}
