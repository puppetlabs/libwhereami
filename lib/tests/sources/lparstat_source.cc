#include <catch.hpp>
#include <internal/sources/lparstat_source.hpp>
#include "../fixtures/lparstat_fixtures.hpp"

using namespace std;
using namespace whereami::sources;
using namespace whereami::testing::lparstat;

SCENARIO("Using the lparstat data source") {
    WHEN("Running on AIX") {
        WHEN("LPAR information is available") {
            WHEN("WPAR information is available") {
                THEN("LPAR and WPAR fields are filled") {
                    lparstat_fixture lparstat_source {"7.1.0.0", "output/lparstat/wpar.txt"};
                    REQUIRE(lparstat_source.partition_number() == 16);
                    REQUIRE(lparstat_source.partition_name() == "aix-71-agent3");
                    REQUIRE(lparstat_source.wpar_key() == 1);
                    REQUIRE(lparstat_source.wpar_configured_id() == 1);
                }
            }

            WHEN("WPAR INFORMATION is not available") {
                THEN("LPAR fields are filled and WPAR fields are empty") {
                    lparstat_fixture lparstat_source {"5.3.0.0", "output/lparstat/lpar.txt"};
                    REQUIRE(lparstat_source.partition_number() == 16);
                    REQUIRE(lparstat_source.partition_name() == "aix-71-agent3");
                    REQUIRE(lparstat_source.wpar_key() == 0);
                    REQUIRE(lparstat_source.wpar_configured_id() == 0);
                }
            }
        }
    }

    WHEN("Running outside of AIX") {
        WHEN("An lparstat executable is available but this is not an AIX machine") {
            THEN("the source does not attempt to collect any data and empty values are correctly initialized") {
                lparstat_fixture lparstat_source {"0.0", "output/lparstat/kvm_power8.txt"};
                REQUIRE(lparstat_source.partition_number() == 0);
                REQUIRE(lparstat_source.partition_name().empty());
                REQUIRE(lparstat_source.wpar_key() == 0);
                REQUIRE(lparstat_source.wpar_configured_id() == 0);
            }
        }
    }
}
