#include <catch.hpp>
#include <internal/detectors/lpar_detector.hpp>
#include "../fixtures/lparstat_fixtures.hpp"

using namespace whereami::detectors;
using namespace whereami::sources;
using namespace whereami::testing;
using namespace whereami::testing::lparstat;
using namespace std;

SCENARIO("Using the LPAR detector") {
    WHEN("Running inside a LPAR") {
        lparstat_fixture lparstat_source{"output/lparstat/lpar.txt"};
        auto res = lpar(lparstat_source);
        THEN("the result is valid") {
            REQUIRE(res.valid());
        }
        THEN("the result has the expected metadata") {
            REQUIRE(res.get<string>("partition_name") == "aix-71-agent3");
            REQUIRE(res.get<int>("partition_number") == 16);
        }
    }
}
