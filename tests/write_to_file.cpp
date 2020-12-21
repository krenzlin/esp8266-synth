#ifndef ARDUINO

#include <iostream>
#include <stdio.h>

#include "clock.h"
#include "cfg.h"
#include "drums.h"
#include "pattern.h"
#include "808.h"

#include "wav_writer.h"
using stmlib::WavWriter;

int main() {
    auto drums = Drums();
    auto drummer = Pattern(&drums);
    auto clk = Clock(cfg::sr, cfg::ppq);
    drummer.next_pattern();

    auto cb = [&]() mutable {drummer.step();};
    clk.set_sixteenth_callback(cb);

    uint16_t bpm {160};
    clk.start(bpm);

    auto writer = WavWriter(1, cfg::sr, 10); // channels, sr, duration in s
    writer.Open("generated.wav");

    int ms = 10000;
    int n_samples = int(cfg::sr * ms/1000.0);

    for (auto i=0; i<n_samples; i++) {
        clk.tick();
        int16_t sample = drums.sample();
        float f_sample = sample / (float) 0x7FFF;
        writer.Write(&f_sample, 1);
    }

}

#endif
