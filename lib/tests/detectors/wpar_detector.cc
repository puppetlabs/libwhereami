#include <catch.hpp>
#include <internal/detectors/wpar_detector.hpp>
#include "../fixtures/lparstat_fixtures.hpp"

using namespace whereami::detectors;
using namespace whereami::sources;
using namespace whereami::testing;
using namespace whereami::testing::lparstat;
using namespace std;

SCENARIO("Using the WPAR detector") {
    WHEN("Running on AIX") {
        WHEN("Running inside a WPAR") {
            lparstat_fixture lparstat_source {"7.1.0.0", "output/lparstat/wpar.txt"};
            auto res = wpar(lparstat_source);
            THEN("the result is valid") {
                REQUIRE(res.valid());
            }
            THEN("the result has the expected metadata") {
                REQUIRE(res.get<int>("key") == 1);
                REQUIRE(res.get<int>("configured_id") == 1);
            }
        }
        WHEN("Not running inside a WPAR") {
            lparstat_fixture lparstat_source {"7.1.0.0", "output/lparstat/lpar.txt"};
            auto res = wpar(lparstat_source);
            THEN("The result is not valid") {
                REQUIRE_FALSE(res.valid());
            }
            THEN("The data is still correctly initialized") {
                REQUIRE(res.get<int>("key") == 0);
                REQUIRE(res.get<int>("configured_id") == 0);
            }
        }
    }

    WHEN("Running outside of AIX") {
        lparstat_fixture lparstat_source {"oslevel: command not found", "output/lparstat/kvm_power8.txt"};
        auto res = wpar(lparstat_source);
        THEN("The result is not valid") {
            REQUIRE_FALSE(res.valid());
        }
        THEN("The data is still correctly initialized") {
            REQUIRE(res.get<int>("key") == 0);
            REQUIRE(res.get<int>("configured_id") == 0);
        }
    }
}
