#include <catch.hpp>
#include <internal/detectors/lpar_detector.hpp>
#include "../fixtures/lparstat_fixtures.hpp"

using namespace whereami::detectors;
using namespace whereami::sources;
using namespace whereami::testing;
using namespace whereami::testing::lparstat;
using namespace std;

SCENARIO("Using the LPAR detector") {
    WHEN("Running on AIX") {
        WHEN("Running inside an LPAR") {
            lparstat_fixture lparstat_source {"5.3.0.0", "output/lparstat/lpar.txt"};
            auto res = lpar(lparstat_source);
            THEN("The result is valid") {
                REQUIRE(res.valid());
            }
            THEN("The result has the expected metadata") {
                REQUIRE(res.get<string>("partition_name") == "aix-71-agent3");
                REQUIRE(res.get<int>("partition_number") == 16);
            }
        }
        WHEN("`oslevel` suggests AIX but lparstat output is unusable for some reason") {
            lparstat_fixture lparstat_source {"7.1.0.0", "output/lparstat/kvm_power8.txt"};
            auto res = lpar(lparstat_source);
            THEN("The result is not valid") {
                REQUIRE_FALSE(res.valid());
            }
            THEN("The data is still correctly initialized") {
                REQUIRE(res.get<string>("partition_name").empty());
                REQUIRE(res.get<int>("partition_number") == 0);
            }
        }
    }

    WHEN("Running outside of AIX") {
        lparstat_fixture lparstat_source {"oslevel: command not found", "output/lparstat/kvm_power8.txt"};
        auto res = lpar(lparstat_source);
        THEN("The result is not valid") {
            REQUIRE_FALSE(res.valid());
        }
        THEN("The data is still correctly initialized") {
            REQUIRE(res.get<string>("partition_name").empty());
            REQUIRE(res.get<int>("partition_number") == 0);
        }
    }
}
