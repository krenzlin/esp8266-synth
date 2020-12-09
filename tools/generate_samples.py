import re

import numpy as np
from pathlib import Path
from scipy.io import wavfile


preamble = """#pragma once
#include <stdint.h>
#if ARDUINO
#include <pgmspace.h>
#else
#define PROGMEM
#endif

namespace samples {
"""

postamble = """
} // samples"""


if __name__ == "__main__":
    with open("samples.h", "w") as f:
        f.write(preamble)
        samples_dir = Path("samples/")
        for sample_file in sorted(samples_dir.iterdir()):
            if not sample_file.is_file():
                continue
            print("-"*5, sample_file, "-"*5)
            sr, raw_data = wavfile.read(sample_file)
            print("sr:", sr)
            data = np.array(raw_data) + 0x8000
            print("min/max/size:", data.min(), data.max(), data.size)
            assert data.min() >= 0
            assert data.max() <= 0xFFFF

            name = sample_file.name[:-4]
            name = re.sub("[,.\- ]", "_", name)
            print(name)

            f.write(f"const uint32_t {name}_len = {data.size};\n")
            str_data = ", ".join(str(value) for value in data)
            f.write(f"const uint16_t {name}[{name}_len] PROGMEM = {{\n{str_data}\n}};\n\n")

        f.write(postamble)
