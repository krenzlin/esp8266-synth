#include "pattern.h"

void Pattern::step() {
    // hihat on every step
    drums_->on(44);

    // kick
    if (steps % 2) {
        drums_->on(35);
    }

    // snare
    if (steps % 4) {
        drums_->on(38);
    }

    steps += 1;
    if (steps >= 8) {
        steps = 0;
    }
}
