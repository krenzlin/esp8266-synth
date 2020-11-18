#include "hal.h"
#include <ESP8266WiFi.h>
#include <i2s.h>
#include <i2s_reg.h>

void HAL::I2S::init(int sr) {
    i2s_begin();
    i2s_set_rate(sr);
}

void HAL::I2S::pdm_write(uint16_t signal) {
    static uint32_t i2sACC;
    static uint16_t err;

    for (uint8_t i = 0; i<32; i++) {
      i2sACC = i2sACC << 1;
      if (signal >= err) {
        i2sACC |= 1;
        err += 0xFFFF - signal;
      } else {
        err -= signal;
      }
    }

    i2s_write_sample(i2sACC);
}

void HAL::WIFI::turn_off() {
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
    delay(1); // 1ms; maybe use yield() instead
}
