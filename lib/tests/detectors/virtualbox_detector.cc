#include <catch.hpp>
#include <internal/sources/dmi_source.hpp>
#include <internal/detectors/virtualbox_detector.hpp>
#include "../fixtures/dmi_fixtures.hpp"

using namespace std;
using namespace whereami::detectors;
using namespace whereami::sources;
using namespace whereami::testing::dmi;

SCENARIO("Using the VirtualBox detector") {
    WHEN("running in a VirtualBox VM") {
        dmi_fixture_values dmi_virtualbox({
            "VirtualBox",
            "VirtualBox",
            "Oracle Corporation",
            "innotek GmbH",
            "VirtualBox" });
        THEN("it should return true") {
            REQUIRE(virtualbox(dmi_virtualbox));
        }
    }

    WHEN("running elsewhere") {
        dmi_fixture_empty dmi_empty;
        THEN("it should return false") {
            REQUIRE_FALSE(virtualbox(dmi_empty));
        }
    }
}
