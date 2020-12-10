#pragma once
#include <stdint.h>

namespace misc {

uint32_t ticks_per_pulse(uint32_t sr, uint32_t bpm, uint32_t ppq);

uint32_t fast_rand();
float fast_float_rand();

float velocity_to_volume(uint32_t velocity);
}
