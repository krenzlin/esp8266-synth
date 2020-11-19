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

void HAL::WIFI::turn_off() {
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
    delay(1); // 1ms; maybe use yield() instead
}
