#include "catch.hpp"
#include "dsp.h"


TEST_CASE("volume", "[dsp]") {
    REQUIRE(dsp::volume(0x0000, 0.f) == 0x7FFF);
    REQUIRE(dsp::volume(0xFFFF, 0.f) == 0x7FFF);
    REQUIRE(dsp::volume(0x7FFF, 0.f) == 0x7FFF);

    REQUIRE(dsp::volume(0x0000, 1.f) == 0x0000);
    REQUIRE(dsp::volume(0xFFFF, 1.f) == 0xFFFF);
    REQUIRE(dsp::volume(0x7FFF, 1.f) == 0x7FFF);

}

