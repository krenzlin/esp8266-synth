#include "hal.h"
#include "clock.h"
#include "config.h"
#include "osc.h"
#include "misc.h"
#include "drums.h"
#include "pattern.h"

auto drums = Drums();
auto pattern = Pattern(&drums);
auto clk = Clock(config::sr, config::ppq);
uint16_t bpm {160};


void setup() {
    hal::set_cpu_freq(160);
    hal::wifi::turn_off();
    hal::i2s::init(44100);

    auto cb = [&]() mutable {pattern.step();};
    clk.set_sixteenth_callback(cb);
    clk.start(bpm);
}


void loop() {
    clk.tick();
    uint16_t sample = drums.sample() >> 4;
    hal::i2s::write(sample, sample);
}
