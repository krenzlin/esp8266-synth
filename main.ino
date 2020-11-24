#include "hal.h"
#include "clock.h"
#include "osc.h"
#include "misc.h"

auto synth = osc::Saw();
auto drum = osc::Sampler();
auto clk = Clock(44100, 1);
uint16_t bpm {120};


void setup() {
    hal::set_cpu_freq(160);
    hal::wifi::turn_off();
    hal::i2s::init(44100);

    synth.on(35);
    auto cb = [&]() mutable {drum.on(0);};
    clk.set_pulse_callback(cb);
    clk.start(bpm);
}


void loop() {
    static uint32_t ticks {0};
    ticks++;
    if (ticks > 44100) {
        bpm += 5;
        if (bpm > 200) {
            bpm = 60;
        }
        clk.set_bpm(bpm);
        ticks = 0;
    }
    clk.tick();
    uint16_t sample = drum.sample() >> 6;
    sample += synth.sample() >> 6;
    hal::i2s::write(sample, sample);
}
