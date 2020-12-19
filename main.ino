#include "hal.h"
#include "clock.h"
#include "cfg.h"
#include "osc.h"
#include "misc.h"
#include "drums.h"
#include "pattern.h"
#include "drummer.h"
#include "Arduino.h"
#include "808.h"

auto drums = Drums();
auto drummer = Pattern(&drums, 25);
auto clk = Clock(cfg::sr, cfg::ppq);
uint16_t bpm {100};
auto next = hal::Button(D5);
auto start = hal::Button(D6);


void setup() {
    hal::set_cpu_freq(160);
    hal::wifi::turn_off();
    hal::i2s::init(44100);

    if (next.is_held()) {
        osc::Sampler bd {osc::Sampler(samples::Kick13_mugent, samples::Kick13_mugent_len, 1.0)};
        osc::Sampler sn {osc::Sampler(samples::Snare7_mugent, samples::Snare7_mugent_len, 0.8)};
        osc::Sampler hh {osc::Sampler(samples::CH5_mugent, samples::CH5_mugent_len, 0.3)};
        drums.set_sampler(bd, sn, hh);
        next.history_ = 0b11111111; // set pressed state
    }

    auto cb = [&]() mutable {drummer.step();};
    clk.set_thirtysecond_callback(cb);
    clk.start(bpm);
}

void audio_loop() {
    // updates at audio rate
    uint16_t sample = drums.sample();
    hal::i2s::write(sample, sample);
}


void control_loop() {
    // update at control rate sr/100
    if (next.is_pressed()) {
        drummer.next_pattern();
    }
    if (start.is_pressed()) {
        drummer.reset();
        clk.toogle();
    }

    bpm = map(analogRead(A0), 10, 1024, 40, 220);
    clk.set_bpm(bpm);
}


void loop() {
    clk.tick();
    audio_loop();

    static uint8_t cr_counter {0};
    cr_counter++;

    if (cr_counter > 100) {
        control_loop();
        cr_counter = 0;
    }
}
