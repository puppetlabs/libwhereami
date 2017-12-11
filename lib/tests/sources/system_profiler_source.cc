#include <catch.hpp>
#include <iostream>
#include <internal/sources/system_profiler_source.hpp>
#include "../fixtures/system_profiler_fixtures.hpp"

using namespace std;
using namespace whereami::sources;
using namespace whereami::testing;
using namespace whereami::testing::system_profiler;

SCENARIO("Using the system profiler data source") {
    WHEN("system_profiler is available") {
        system_profiler_fixture system_profiler_source(system_profiler_fixture::SYSTEM_PROFILER_PHYSICAL);
        THEN("the values are successfully collected") {
            REQUIRE(system_profiler_source.boot_rom_version() == "MBP101.00EE.B18");
            REQUIRE(system_profiler_source.model_identifier() == "MacBookPro10,1");
            REQUIRE(system_profiler_source.system_serial_number() == "C02L92KLFFT1");
        }
    }

    WHEN("system_profiler is not available") {
        system_profiler_fixture system_profiler_source({});
        THEN("no information is collected") {
            REQUIRE(system_profiler_source.boot_rom_version() == "");
            REQUIRE(system_profiler_source.model_identifier() == "");
            REQUIRE(system_profiler_source.system_serial_number() == "");
        }
    }
}
