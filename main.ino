#include "Arduino.h"
#include <user_interface.h>

#include "hal.h"
#include "osc.h"
#include "misc.h"


auto synth = OSC::Saw();

void setup() {
    system_update_cpu_freq(160);
    HAL::WIFI::turn_off();
    HAL::I2S::init(44100);
}

void loop() {
    static auto sample = synth.sample();
    HAL::I2S::write(sample);
}
