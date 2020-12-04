#include "catch.hpp"
#include "osc.h"

TEST_CASE("Sampler", "[osc]") {
    uint16_t sample[2] = {0, 0xFF};
    auto sampler = osc::Sampler(sample, 2);

    SECTION("return samples") {
        sampler.on(0);
        REQUIRE(sampler.sample() == 0);
        REQUIRE(sampler.sample() == 0xFF);
    }

    SECTION("no return when not played") {
        REQUIRE(sampler.sample() == osc::ZERO);
        REQUIRE(sampler.sample() == osc::ZERO);
    }

    SECTION("using reference of sample") {
        sample[0] = 123;
        sampler.on(0);
        REQUIRE(sampler.sample() == 123);
        REQUIRE(sampler.sample() == 0xFF);
    }


}

TEST_CASE("Sampler volume", "[osc]") {
    uint16_t sample[1] = {0xFFFF};
    auto sampler = osc::Sampler(sample, 1, 1.f);

    SECTION("velocity") {
        sampler.on(0, 127);
        REQUIRE(sampler.sample() == 0xFFFF);

        sampler.on(0, 0);
        REQUIRE(sampler.sample() == 0x7FFF); // "zero" is at 1/2 of 0xFFFF

        sampler.on(0, 127 >> 1);
        REQUIRE(sampler.sample() == 0xBF7D); // 63/127 * 0x7FFF + 0x7FFF
    }
}
