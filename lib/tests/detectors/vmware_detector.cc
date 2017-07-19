#include <catch.hpp>
#include <internal/detectors/vmware_detector.hpp>
#include "../fixtures/cpuid_fixtures.hpp"
#include "../fixtures/dmi_fixtures.hpp"

using namespace std;
using namespace whereami::detectors;
using namespace whereami::sources;
using namespace whereami::testing::cpuid;
using namespace whereami::testing::dmi;

SCENARIO("Using the VMware detector") {
    WHEN("running as root on a Linux VMware guest") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_VMwareVMware},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT},
        });
        dmi_fixture_values dmi_source({
            "0xea580",
            "Phoenix Technologies LTD",
            "Intel Corporation",
            "440BX Desktop Reference Platform",
            "VMware, Inc.",
            "VMware Virtual Platform",
            {
                "[MS_VM_CERT/SHA1/27d66596a61c48dd3dc7216fd715126e33f59ae7]",
                "Welcome to the Virtual Machine",
            }});
        THEN("the result should be valid") {
            auto res = vmware(cpuid_source, dmi_source);
            REQUIRE(res.valid());
        }
        THEN("the result should contain version metdata") {
            auto res = vmware(cpuid_source, dmi_source);
            REQUIRE(res.get<string>("version") == "ESXi 6.5");
        }
    }

    WHEN("running as a normal user on a Linux VMware guest") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_VMwareVMware},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT},
        });
        dmi_fixture_values dmi_source({
            "",
            "Phoenix Technologies LTD",
            "Intel Corporation",
            "440BX Desktop Reference Platform",
            "VMware, Inc.",
            "VMware Virtual Platform",
            {}});
        THEN("it should return true") {
            auto res = vmware(cpuid_source, dmi_source);
            REQUIRE(res.valid());
        }
        THEN("it should not contain version metdata") {
            auto res = vmware(cpuid_source, dmi_source);
            REQUIRE(res.get<string>("version") == "");
        }
    }

    WHEN("running in a Windows VMware guest") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_VMwareVMware},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT},
        });
        dmi_fixture_empty dmi_source;
        THEN("it should return true") {
            REQUIRE(vmware(cpuid_source, dmi_source).valid());
        }
    }

    WHEN("running outside of VMware") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF, register_fixtures::VENDOR_KVMKVMKVM},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT},
        });
        dmi_fixture_values dmi_source({
            "Other",
            "Other",
            "Other",
            "Other",
            "Other",
            "Other",
            {}});
        THEN("it should return false") {
            REQUIRE_FALSE(vmware(cpuid_source, dmi_source).valid());
        }
    }
}
