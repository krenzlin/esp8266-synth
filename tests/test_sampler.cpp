#include "catch.hpp"
#include "osc.h"

TEST_CASE("Sampler", "[osc]") {
    int16_t sample[2] = {0, 0xFF};
    auto sampler = osc::Sampler(sample, 2);

    SECTION("return samples") {
        sampler.on(0);
        REQUIRE(sampler.sample() == 0);
        REQUIRE(sampler.sample() == 0xFF);
    }

    SECTION("no return when not played") {
        REQUIRE(sampler.sample() == 0);
        REQUIRE(sampler.sample() == 0);
    }

    SECTION("using reference of sample") {
        sample[0] = 123;
        sampler.on(0);
        REQUIRE(sampler.sample() == 123);
        REQUIRE(sampler.sample() == 0xFF);
    }


}

TEST_CASE("Sampler volume", "[osc]") {
    int16_t sample[1] = {0x7FFF};
    auto sampler = osc::Sampler(sample, 1, 1.f);

    SECTION("velocity") {
        sampler.on(0, 127);
        REQUIRE(sampler.sample() == 0x7FFF);

        sampler.on(0, 0);
        REQUIRE(sampler.sample() == 0);

        sampler.on(0, 63);
        REQUIRE(sampler.sample() == 0x3F7E); // 63 -> 0.49606
    }
}
