#include "clock.h"
#include "misc.h"


void Clock::set_bpm(const uint32_t bpm) {
    ticks_per_pulse = misc::ticks_per_pulse(sr, bpm, ppq);
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
    call(pulse_cb);
    if ((pulses % ppq) == 0) call(quarter_cb);
    if ((pulses % pp8) == 0) call(eigth_cb);
    if ((pulses % pp16) == 0) call(sixteenth_cb);

    pulses += 1;
    if (pulses >= ppq) {
        pulses = 0;
    }
}

void Clock::call(cb_t func) {
    if (func != nullptr) {
        func();
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
