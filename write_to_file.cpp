#ifndef ARDUINO

#include <iostream>
#include "osc.h"


void write_to_file(OSC::Saw gen, float ms, std::FILE* file) {
    int n_samples = int(44100 * ms/1000.0);

    for (auto i=0; i<n_samples; i++) {
        auto sample = (float)gen.sample() / 0xFFFF;
        std::fwrite(&sample, sizeof(float), 1, file);
    }
}


int main() {
    auto synth = OSC::Saw();
    std::FILE* file = std::fopen("generated.raw", "wb");



    write_to_file(synth, 1000, file);

    std::fclose(file);


    return 0;
}

#endif
