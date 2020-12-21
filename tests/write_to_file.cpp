#ifndef ARDUINO

#include <iostream>
#include <stdio.h>
#include <string>

#include "clock.h"
#include "cfg.h"
#include "drums.h"
#include "pattern.h"
#include "808.h"

#include "wav_writer.h"
using stmlib::WavWriter;

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("error: you need to provide a output file name");
        return -1;
    }

    auto drums = Drums();
    auto drummer = Pattern(&drums);
    auto clk = Clock(cfg::sr, cfg::ppq);
    drummer.next_pattern();

    auto cb = [&]() mutable {drummer.step();};
    clk.set_sixteenth_callback(cb);

    uint16_t bpm {160};
    clk.start(bpm);

    auto writer = WavWriter(1, cfg::sr, 10); // channels, sr, duration in s
    writer.Open(argv[1]);

    while (!writer.done()) {
        clk.tick();
        int16_t sample = drums.sample();
        float f_sample = sample / (float) 0x7FFF;
        writer.Write(&f_sample, 1);
    }

}

#endif
