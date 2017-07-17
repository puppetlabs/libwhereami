#include <catch.hpp>
#include <internal/sources/dmi_source.hpp>
#include <internal/detectors/virtualbox_detector.hpp>
#include "../fixtures/dmi_fixtures.hpp"
#include "../fixtures/cpuid_fixtures.hpp"

using namespace std;
using namespace whereami::detectors;
using namespace whereami::sources;
using namespace whereami::testing::dmi;
using namespace whereami::testing::cpuid;

SCENARIO("Using the VirtualBox detector") {
    WHEN("running on a Linux VirtualBox guest") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_KVMKVMKVM},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT},
        });
        dmi_fixture_values dmi_source({
            "VirtualBox",
            "VirtualBox",
            "Oracle Corporation",
            "innotek GmbH",
            "VirtualBox", });
        THEN("it should return true") {
            REQUIRE(virtualbox(cpuid_source, dmi_source));
        }
    }

    WHEN("running on a Windows VirtualBox guest") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_VBoxVBoxVBox},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT}
        });
        dmi_fixture_empty dmi_source;
        THEN("it should return true") {
            REQUIRE(virtualbox(cpuid_source, dmi_source));
        }
    }

    WHEN("running outside of VirtualBox") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_KVMKVMKVM},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT}
        });
        dmi_fixture_values dmi_source({
            "Other",
            "Other",
            "Other",
            "Other",
            "Other", });
        THEN("it should return false") {
            REQUIRE_FALSE(virtualbox(cpuid_source, dmi_source));
        }
    }
}
