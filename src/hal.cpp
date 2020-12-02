#include "hal.h"
#include <ESP8266WiFi.h>
#include <i2s.h>
#include <i2s_reg.h>

void hal::i2s::init(const uint32_t sr) {
    i2s_begin();
    i2s_set_rate(sr);
}

void hal::i2s::write(const uint32_t sample) {
    i2s_write_sample(sample);
}

void hal::i2s::write(const uint32_t left, const uint32_t right) {  // looking at the assembly using int32 saved one conversion compared to int16
    i2s_write_sample(left << 16 | right);
}

void hal::wifi::turn_off() {
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
    delay(1); // 1ms; maybe use yield() instead
}

void hal::set_cpu_freq(const uint8_t freq) {
    system_update_cpu_freq(freq);
}


hal::Button::Button() {
    pin = D6;
    pinMode(pin, INPUT_PULLUP);
}

void hal::Button::update() {
    history <<= 1;
    history |= (digitalRead(pin) == 0);
}

const uint8_t _MASK {0b11000111};
const uint8_t _RISING {0b00000111};
const uint8_t _PRESSED {0b11111111};

bool hal::Button::is_pressed() {
    update();
    if ((history & _MASK) == _RISING) {
        history = _PRESSED;
        return true;
    }
    return false;
}
