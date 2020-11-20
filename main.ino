#include "hal.h"
#include "osc.h"
#include "misc.h"


auto synth1 = OSC::Saw();
auto synth2 = OSC::Saw();

void setup() {
    HAL::set_cpu_freq(160);
    HAL::WIFI::turn_off();
    HAL::I2S::init(44100);

    synth1.set_note(74);
    synth2.set_note(69);
}

void loop() {
    auto sample = (synth1.sample() + synth2.sample()) >> 6;
    HAL::I2S::write(sample, sample);
}
