#include "pattern.h"

bool bd[8] = {1, 0, 1, 0, 1, 0, 1, 0};
bool sn[8] = {0, 0, 1, 0, 0, 1, 0, 1};
bool hh[8] = {1, 1, 1, 1, 1, 1, 1, 1};

void Pattern::step() {
    if (bd[steps]) drums_->on(35);
    if (sn[steps]) drums_->on(38);
    if (hh[steps]) drums_->on(44);

    steps += 1;
    if (steps >= 8) {
        steps = 0;
    }
}
