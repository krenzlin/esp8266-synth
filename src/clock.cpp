#include "clock.h"

void Clock::set_bpm(const uint32_t bpm) {
    ticks_per_pulse = sr / (ppq * bpm / 60.f);
}

void Clock::start() {
    ticks = 0;
    running = true;
}

void Clock::start(const uint32_t bpm) {
    set_bpm(bpm);
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

    if (ticks == 0) {
        pulse();
    }

    ticks += 1;
    if (ticks >= ticks_per_pulse) {
        ticks = 0;
    }
}

void Clock::pulse() {
    if (pulse_cb != nullptr) pulse_cb();
    if ((pulses % ppq == 0) && quarter_cb != nullptr) quarter_cb();
    if ((pulses % ppq >> 1 == 0) && eigth_cb != nullptr) eigth_cb();
    if ((pulses % ppq >> 2 == 0) && sixteenth_cb != nullptr) sixteenth_cb();

    pulses += 1;
    if (pulses >= ppq) {
        pulses = 0;
    }
}

void Clock::set_pulse_callback(const cb_t cb) {
    pulse_cb = cb;
}

void Clock::set_quarter_callback(const cb_t cb) {
    quarter_cb = cb;
}

void Clock::set_eigth_callback(const cb_t cb) {
    eigth_cb = cb;
}

void Clock::set_sixteenth_callback(const cb_t cb) {
    sixteenth_cb = cb;
}
