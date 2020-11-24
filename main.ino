#include "hal.h"
#include "clock.h"
#include "osc.h"
#include "misc.h"

auto synth1 = OSC::Saw();
auto synth2 = OSC::Saw();
auto drum = OSC::Sampler();
auto clk = Clock(44100, 1);
uint16_t bpm {120};


void setup() {
    HAL::set_cpu_freq(160);
    HAL::WIFI::turn_off();
    HAL::I2S::init(44100);

    auto cb = [&]() mutable {drum.on();};
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
    HAL::I2S::write(sample, sample);
}
