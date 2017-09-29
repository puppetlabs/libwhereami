#include <catch.hpp>
#include <internal/detectors/ldom_detector.hpp>
#include <internal/vm.hpp>
#include "../fixtures.hpp"

using namespace whereami::detectors;
using namespace whereami::testing;
using namespace std;

SCENARIO("Using the Solaris LDom detector") {
    WHEN("gathering metadata from `virtinfo -a -p` inside an LDom guest") {
        string virtinfo_output;
        load_fixture("output/virtinfo/guest.txt", virtinfo_output);
        whereami::result res {whereami::vm::ldom};
        parse_virtinfo_output(res, virtinfo_output);

        THEN("the result is valid") {
            REQUIRE(res.valid());
        }

        THEN("the data is collected and set") {
            REQUIRE_FALSE(res.get<bool>("role_control"));
            REQUIRE_FALSE(res.get<bool>("role_io"));
            REQUIRE_FALSE(res.get<bool>("role_service"));
            REQUIRE_FALSE(res.get<bool>("role_root"));
            REQUIRE(res.get<string>("domain_name") == "sol10-2");
            REQUIRE(res.get<string>("domain_uuid") == "ddfb4bdc-29f7-4b44-8d62-d3b0eaafd966");
            REQUIRE(res.get<string>("control_domain") == "opdx-a0-sun2");
            REQUIRE(res.get<string>("chassis_serial") == "AK00358110");
        }
    }

    WHEN("gathering metadata from `virtinfo -a -p` inside an LDom host") {
        string virtinfo_output;
        load_fixture("output/virtinfo/host.txt", virtinfo_output);
        whereami::result res {whereami::vm::ldom};
        parse_virtinfo_output(res, virtinfo_output);

        THEN("the result is valid") {
            REQUIRE(res.valid());
        }

        THEN("the data is collected and set") {
            REQUIRE(res.get<bool>("role_control"));
            REQUIRE(res.get<bool>("role_io"));
            REQUIRE(res.get<bool>("role_service"));
            REQUIRE(res.get<bool>("role_root"));
            REQUIRE(res.get<string>("domain_name") == "primary");
            REQUIRE(res.get<string>("domain_uuid") == "b7e5fa70-bc64-458f-a4b4-c8dc9213fa3b");
            REQUIRE(res.get<string>("control_domain") == "opdx-a0-sun-01");
            REQUIRE(res.get<string>("chassis_serial") == "AK00214288");
        }
    }
}
