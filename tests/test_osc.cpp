#include "catch.hpp"
#include "osc.h"

TEST_CASE("Saw", "[osc]") {
    auto saw = osc::Saw();
    REQUIRE(saw.sample() == 0);
    REQUIRE(saw.sample() > 0);
}
