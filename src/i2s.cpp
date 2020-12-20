#include "hal.h"
#include "Arduino.h"
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
