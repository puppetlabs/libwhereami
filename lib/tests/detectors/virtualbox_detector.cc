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
    WHEN("running on a Linux VirtualBox guest with root") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_KVMKVMKVM},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT},
        });
        dmi_fixture_values dmi_source({
            "VirtualBox",
            "VirtualBox",
            "Oracle Corporation",
            "innotek GmbH",
            "VirtualBox",
            {
                "vboxVer_5.1.22",
                "vboxRev_115126",
            }});
        auto res = virtualbox(cpuid_source, dmi_source);
        THEN("the result should be valid") {
            REQUIRE(res.valid());
        }
        AND_THEN("the result should contain privileged VirtualBox metadata") {
            REQUIRE(res.get<string>("version") == "5.1.22");
            REQUIRE(res.get<string>("revision") == "115126");
        }
    }

    WHEN("running on a Linux VirtualBox guest without root") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_KVMKVMKVM},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT},
        });
        dmi_fixture_values dmi_source({
            "VirtualBox",
            "VirtualBox",
            "Oracle Corporation",
            "innotek GmbH",
            "VirtualBox",
            {}});
        auto const& res = virtualbox(cpuid_source, dmi_source);
        THEN("the result should be valid") {
            REQUIRE(res.valid());
        }
        AND_THEN("the result should not contain privileged VirtualBox metadata") {
            REQUIRE(res.get<string>("version") == "");
            REQUIRE(res.get<string>("revision") == "");
        }
    }

    WHEN("running on a Windows VirtualBox guest") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_VBoxVBoxVBox},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT}
        });
        dmi_fixture_empty dmi_source;
        THEN("the result should be valid") {
            auto res = virtualbox(cpuid_source, dmi_source);
            REQUIRE(res.valid());
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
            "Other",
            {}});
        THEN("the result should not be valid") {
            auto res = virtualbox(cpuid_source, dmi_source);
            REQUIRE_FALSE(res.valid());
        }
    }
}
