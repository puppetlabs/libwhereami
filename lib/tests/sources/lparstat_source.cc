#include <catch.hpp>
#include <internal/sources/lparstat_source.hpp>
#include "../fixtures/lparstat_fixtures.hpp"

using namespace std;
using namespace whereami::sources;
using namespace whereami::testing::lparstat;

SCENARIO("Using the lparstat data source") {

    WHEN("WPAR information is not available") {
        lparstat_fixture lparstat_source {"5.3.0.0", "output/lparstat/lpar.txt"};
        REQUIRE(lparstat_source.partition_number() == 16);
        REQUIRE(lparstat_source.partition_name() == "aix-71-agent3");
        REQUIRE(lparstat_source.wpar_key() == 0);
        REQUIRE(lparstat_source.wpar_configured_id() == 0);
    }

    WHEN("WPAR information is available") {
        lparstat_fixture lparstat_source {"7.1.0.0", "output/lparstat/wpar.txt"};
        REQUIRE(lparstat_source.partition_number() == 16);
        REQUIRE(lparstat_source.partition_name() == "aix-71-agent3");
        REQUIRE(lparstat_source.wpar_key() == 1);
        REQUIRE(lparstat_source.wpar_configured_id() == 1);
    }
}
