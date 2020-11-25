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
