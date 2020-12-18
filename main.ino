#include "hal.h"
#include "clock.h"
#include "cfg.h"
#include "osc.h"
#include "misc.h"
#include "drums.h"
#include "pattern.h"
#include "drummer.h"
#include "Arduino.h"

auto drums = Drums();
auto drummer = Pattern(&drums, 25);
auto clk = Clock(cfg::sr, cfg::ppq);
uint16_t bpm {100};
auto next = hal::Button(D6);
auto start = hal::Button(D5);


void setup() {
    hal::set_cpu_freq(160);
    hal::wifi::turn_off();
    hal::i2s::init(44100);


    auto cb = [&]() mutable {drummer.step();};
    clk.set_thirtysecond_callback(cb);
    clk.start(bpm);
}


void loop() {
    // updates at audio rate -> sr
    clk.tick();
    uint16_t sample = drums.sample();
    hal::i2s::write(sample, sample);

    // update at control rate sr/100
    static uint8_t cr_counter {0};
    if (cr_counter > 100) {
        if (next.is_pressed()) {
            drummer.next_pattern();
        }
        if (start.is_pressed()) {
            clk.toogle();
        }

        bpm = map(analogRead(A0), 10, 1024, 40, 220);
        clk.set_bpm(bpm);

       cr_counter = 0;
    }
    cr_counter++;
}
