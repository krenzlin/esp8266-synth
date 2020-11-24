#include "hal.h"
#include "clock.h"
#include "osc.h"
#include "misc.h"
#include "drums.h"

auto drums = Drums();
auto clk = Clock(44100, 1);
uint16_t bpm {120};


void setup() {
    hal::set_cpu_freq(160);
    hal::wifi::turn_off();
    hal::i2s::init(44100);

    auto cb = [&]() mutable {drums.on(35); drums.on(44);};
    clk.set_pulse_callback(cb);
    clk.start(bpm);
}


void loop() {
    clk.tick();
    uint16_t sample = drums.sample() >> 4;
    hal::i2s::write(sample, sample);
}
