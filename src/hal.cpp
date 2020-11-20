#include "hal.h"
#include <ESP8266WiFi.h>
#include <i2s.h>
#include <i2s_reg.h>

void HAL::I2S::init(int sr) {
    i2s_begin();
    i2s_set_rate(sr);
}

void HAL::I2S::write(uint32_t sample) {
    i2s_write_sample(sample);
}

void HAL::I2S::write(uint16_t left, uint16_t right) {
    i2s_write_sample(left << 16 | right);
}

void HAL::WIFI::turn_off() {
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
    delay(1); // 1ms; maybe use yield() instead
}

void HAL::set_cpu_freq(uint8_t freq) {
    system_update_cpu_freq(freq);
}
