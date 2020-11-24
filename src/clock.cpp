#include "clock.h"

Clock::Clock(uint32_t sr, uint16_t ppq) : sr{sr}, ppq{ppq} {
};

void Clock::set_bpm(uint16_t bpm) {
    ticks_per_pulse = sr / (ppq * bpm / 60.f);
}

void Clock::start() {
    ticks = 0;
    running = true;
}

void Clock::stop() {
    running = false;
}

void Clock::tick() {
    if (!running) {
        return;
    }

    ticks += 1;

    if (ticks >= ticks_per_pulse) {
        ticks = 0;
    }
}
