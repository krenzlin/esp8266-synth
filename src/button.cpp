#include "hal.h"
#include "Arduino.h"


hal::Button::Button(uint8_t pin) : pin_{pin} {
    pinMode(pin_, INPUT_PULLUP);
}

void hal::Button::update() {
    history_ <<= 1;
    history_ |= (digitalRead(pin_) == 0);
}

const uint8_t _MASK {0b11000111};
const uint8_t _RISING {0b00000111};
const uint8_t _PRESSED {0b11111111};

bool hal::Button::is_pressed() {
    update();
    if ((history_ & _MASK) == _RISING) {
        history_ = _PRESSED;
        return true;
    }
    return false;
}

bool hal::Button::is_held() {
    update();
    return digitalRead(pin_) == 0;
}
