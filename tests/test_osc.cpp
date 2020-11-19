#include "catch.hpp"
#include "osc.h"

TEST_CASE( "OSC", "[factorial]" ) {
    auto saw = OSC::Saw();
    REQUIRE( saw.sample() == 0 );
    REQUIRE( saw.sample() == 0 );
}
