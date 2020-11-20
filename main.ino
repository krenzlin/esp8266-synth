#include "hal.h"
#include "osc.h"
#include "misc.h"


auto synth = OSC::Saw();

void setup() {
    HAL::set_cpu_freq(160);
    HAL::WIFI::turn_off();
    HAL::I2S::init(44100);
}

void loop() {
    auto sample = synth.sample();
    HAL::I2S::write(sample, sample);
}
