#include "misc.h"
#include "config.h"

const uint16_t MAX_16BIT {0xFFFF};

/*
Convert PCM sample into PCM with 32x oversampling

c.f. https://en.wikipedia.org/wiki/Pulse-density_modulation#Algorithm
*/
uint32_t misc::pcm_to_pdm(uint16_t sample) {
    static uint16_t qe {MAX_16BIT >> 1};
    uint32_t pdm {0};

    for (auto i=0; i<32; i++) {
        pdm <<= 1;
        if (sample >= qe) {
            pdm |= 1;
            qe += MAX_16BIT;
        }
        qe -= sample;
    }

    return pdm;
}

uint32_t misc::ticks_per_pulse(uint32_t sr, uint32_t bpm, uint32_t ppq) {
    return sr / (ppq * bpm / 60.f);
}

/* Fast random implementation
see https://en.wikipedia.org/wiki/Lehmer_random_number_generator

X_k+1 = a * X_k mod m

common parameters

m = 2^31 − 1 = 2,147,483,647 (Mersenne prime M31)
a = 7^5 = 16,807
update: a = 48271
*/
uint32_t misc::fast_rand() {
    static uint32_t X_k {config::random_seed};
    const uint32_t a {48271};
    const uint32_t m {2147483647};

    X_k = (a * X_k) % m;
    return X_k;
}

float misc::fast_float_rand() {
    static uint32_t X_k {config::random_seed};
    constexpr uint32_t a = 16807;
    constexpr float m_1 = 4.6566129e-010f; // 1/(2^31-1) = 1/2147483647

    X_k *=  a;
    return (float) X_k * m_1 / 2.f;
}

float misc::velocity_to_volume(uint32_t velocity) {
    return (float) velocity / 127.0;
}
