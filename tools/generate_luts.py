def mtof(note, tuning=440.0):
    return pow(2.0, (note - 69.0)/12.0) * tuning


def ftoincr(f, sr=44100, max=0xFFFF):
    return f / sr * max


def create_c_array(name, list_):
    template = "const uint16_t {name}[{len}] = {{{values}}};"
    values = ", ".join(str(value) for value in list_)
    return template.format(name=name, len=len(list_), values=values) + "\n"


lut_mtoincr = [round(ftoincr(mtof(note))) for note in range(128)]


header_template = """
#pragma once
#include <stdint.h>

namespace LUT {{

{content}
}}
""".strip()

content = create_c_array("mtoincr", lut_mtoincr)
print(header_template.format(content=content))
