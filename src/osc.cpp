#include "osc.h"
#include "luts.h"
#include "misc.h"
#include "dsp.h"
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

void osc::Sampler::on(const uint32_t note) {
    index_ = 0;
    end_ = len_; // * misc::fast_float_rand();
    vol_ = max_vol_; // * misc::fast_float_rand();
}

uint16_t osc::Sampler::sample() {
    uint16_t sample {osc::ZERO};

    if (index_ < end_) {
#if ARDUINO
        sample = pgm_read_word_near(sample_ + index);
#else
        sample = sample_[index_];
#endif
        index_++;
    }

    return dsp::volume(sample, vol_);
}
