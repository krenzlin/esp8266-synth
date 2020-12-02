#include "hal.h"
#include "clock.h"
#include "config.h"
#include "osc.h"
#include "misc.h"
#include "drums.h"
#include "pattern.h"

auto drums = Drums();
auto drummer = Pattern(&drums);
auto clk = Clock(config::sr, config::ppq);
uint16_t bpm {160};
auto start_stop = hal::Button();


void setup() {
    hal::set_cpu_freq(160);
    hal::wifi::turn_off();
    hal::i2s::init(44100);

    auto cb = [&]() mutable {drummer.step();};
    clk.set_sixteenth_callback(cb);
    clk.start(bpm);
}


void loop() {
    if (start_stop.is_pressed()) {
        drummer.next_pattern();
    }
    clk.tick();
    uint16_t sample = drums.sample() >> 2;
    hal::i2s::write(sample, sample);
}
