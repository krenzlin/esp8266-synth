#ifndef ARDUINO

#include <iostream>
#include <stdio.h>

#include "clock.h"
#include "cfg.h"
#include "drums.h"
#include "pattern.h"
#include "808.h"


int main() {
    auto drums = Drums();
    auto drummer = Pattern(&drums);
    auto clk = Clock(cfg::sr, cfg::ppq);
    drummer.next_pattern();

    auto cb = [&]() mutable {drummer.step();};
    clk.set_sixteenth_callback(cb);

    uint16_t bpm {160};
    clk.start(bpm);

    std::FILE* file = std::fopen("generated.raw", "wb");

    int ms = 10000;
    int n_samples = int(cfg::sr * ms/1000.0);

    for (auto i=0; i<n_samples; i++) {
        clk.tick();
        uint16_t sample = drums.sample();
        float f_sample = (sample - 0x7FFF) / (float) 0x8000;
        //printf("%d -> %f\n", sample, f_sample);
        std::fwrite(&f_sample, sizeof(float), 1, file);
    }

    std::fclose(file);
}

#endif
