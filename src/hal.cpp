#include "hal.h"
#include <ESP8266WiFi.h>
#include <i2s.h>
#include <i2s_reg.h>


void hal::wifi::turn_off() {
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
    delay(1); // 1ms; maybe use yield() instead
}

void hal::set_cpu_freq(const uint8_t freq) {
    system_update_cpu_freq(freq);
}
