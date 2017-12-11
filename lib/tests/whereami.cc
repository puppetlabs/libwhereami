#include <catch.hpp>
#include <whereami/version.h>
#include <whereami/whereami.hpp>

SCENARIO("version() returns the version") {
    REQUIRE(whereami::version() == WHEREAMI_VERSION_WITH_COMMIT);
}

SCENARIO("Checking for hypervisors doesn't throw") {
    REQUIRE_NOTHROW(whereami::hypervisors());
}
