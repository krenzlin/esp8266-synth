#include "osc.h"
#include "luts.h"
#include "misc.h"
#if ARDUINO
#include "pgmspace.h"
#endif

void osc::Saw::on(const uint32_t note) {
    p_incr_ = lut::mtoincr[note];
}

uint16_t osc::Saw::sample() {
    uint16_t sample = phase_;

    phase_ += p_incr_;
    if (phase_ > 0xFFFF) {  // compiler will optimize this away as int16 wraps around 0xFFFF
        phase_ -= 0xFFFF;
    }

    return sample;
}

void osc::Sampler::on(const uint32_t /*note*/, uint32_t velocity) {
    index_ = 0;
    vol_ = misc::velocity_to_volume(velocity) * max_vol_;
}

int16_t osc::Sampler::sample() {
    int16_t sample {0};

    if (index_ < end_) {
#if ARDUINO
        sample = pgm_read_word_near(sample_ + index_);
#else
        sample = sample_[index_];
#endif
        index_++;
    }

    return sample * vol_;
}
