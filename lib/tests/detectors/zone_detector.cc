#include <catch.hpp>
#include <internal/detectors/zone_detector.hpp>
#include <internal/vm.hpp>
#include "../fixtures.hpp"

using namespace whereami::detectors;
using namespace whereami::testing;
using namespace std;

SCENARIO("Using the Solaris zone detector") {
    WHEN("gathering metadata from `zoneadm list -p` inside a zone") {
        string zoneadm_output;
        load_fixture("output/zoneadm/nonglobal.txt", zoneadm_output);

        whereami::result res {whereami::vm::zone};
        res.validate();
        res.set("name", "testzone");

        THEN("the metadata is collected and set") {
            parse_zoneadm_output(res, zoneadm_output);
            REQUIRE(res.get<int>("id") == 1);
            REQUIRE(res.get<string>("uuid") == "ff48fbe7-dcab-691b-c72b-e8f7ace3b975");
            REQUIRE(res.get<string>("brand") == "solaris");
            REQUIRE(res.get<string>("ip_type") == "excl");
        }
    }

    WHEN("gathering metadata from `zoneadm list -p` on a global zone") {
        string zoneadm_output;
        load_fixture("output/zoneadm/global.txt", zoneadm_output);

        whereami::result res {whereami::vm::zone};
        res.validate();
        res.set("name", "global");

        THEN("the metadata is collected and set") {
            parse_zoneadm_output(res, zoneadm_output);
            REQUIRE(res.get<int>("id") == 0);
            REQUIRE(res.get<string>("uuid") == "");
            REQUIRE(res.get<string>("brand") == "solaris");
            REQUIRE(res.get<string>("ip_type") == "shared");
        }
    }
}
