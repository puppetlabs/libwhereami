#include <catch.hpp>
#include <internal/detectors/xen_detector.hpp>
#include "../fixtures/cpuid_fixtures.hpp"

using namespace whereami::detectors;
using namespace whereami::sources;
using namespace whereami::testing;
using namespace whereami::testing::cpuid;
using namespace std;

SCENARIO("Using the Xen detector") {
    WHEN("Checking for dom0 privileges") {
        THEN("a host with capabilities of 'control_d' is reported as privileged") {
            REQUIRE(is_xen_privileged(fixture_full_path("filesystem/xen_detector/dom0_root/")));
        }
        THEN("a host without capabilities of 'control_d' is reported as unprivileged") {
            REQUIRE_FALSE(is_xen_privileged(fixture_full_path("filesystem/xen_detector/domU_root/")));
        }
    }
}
