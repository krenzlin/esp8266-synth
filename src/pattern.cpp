#include "pattern.h"
#include "patterns.h"


void Pattern::step() {
    if (node_0[0+steps] > 0) drums_->on(35);
    if (node_0[32+steps] > 0) drums_->on(38);
    if (node_0[64+steps] > 0) drums_->on(44);

    steps += 1;
    if (steps >= 32) {
        steps = 0;
    }
}
