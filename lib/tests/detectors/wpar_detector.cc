#include <catch.hpp>
#include <internal/detectors/wpar_detector.hpp>
#include "../fixtures/lparstat_fixtures.hpp"

using namespace whereami::detectors;
using namespace whereami::sources;
using namespace whereami::testing;
using namespace whereami::testing::lparstat;
using namespace std;

SCENARIO("Using the WPAR detector") {
    WHEN("Running inside a WPAR") {
        lparstat_fixture lparstat_source{"output/lparstat/wpar.txt"};
        auto res = wpar(lparstat_source);
        THEN("the result is valid") {
            REQUIRE(res.valid());
        }
        THEN("the result has the expected metadata") {
            REQUIRE(res.get<int>("key") == 1);
            REQUIRE(res.get<int>("configured_id") == 1);
        }
    }
}
