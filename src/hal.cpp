#include "hal.h"
#include <ESP8266WiFi.h>
#include <i2s.h>
#include <i2s_reg.h>

void hal::i2s::init(int sr) {
    i2s_begin();
    i2s_set_rate(sr);
}

void hal::i2s::write(uint32_t sample) {
    i2s_write_sample(sample);
}

void hal::i2s::write(uint32_t left, uint32_t right) {
    i2s_write_sample(left << 16 | right);
}

void hal::wifi::turn_off() {
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
    delay(1); // 1ms; maybe use yield() instead
}

void hal::set_cpu_freq(uint8_t freq) {
    system_update_cpu_freq(freq);
}
