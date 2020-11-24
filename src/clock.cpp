#include "clock.h"

void Clock::start() {
    running = true;
}

void Clock::stop() {
    running = false;
}

void Clock::tick() {
    if (running) {
        ticks += 1;
    }
}
