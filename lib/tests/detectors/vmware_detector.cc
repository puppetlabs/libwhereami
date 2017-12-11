#include <catch.hpp>
#include <internal/detectors/vmware_detector.hpp>
#include "../fixtures/cpuid_fixtures.hpp"
#include "../fixtures/dmi_fixtures.hpp"
#include "../fixtures/system_profiler_fixtures.hpp"

using namespace std;
using namespace whereami::detectors;
using namespace whereami::sources;
using namespace whereami::testing::cpuid;
using namespace whereami::testing::dmi;
using namespace whereami::testing::system_profiler;

SCENARIO("Using the VMware detector") {
    WHEN("running as root on a Linux VMware guest") {
        leaf_register_map values {
            {VENDOR_LEAF, {
                {0, register_fixtures::VENDOR_VMwareVMware}}},
            {HYPERVISOR_PRESENT_LEAF, {
                {0, register_fixtures::HYPERVISOR_PRESENT}}}};
        cpuid_fixture cpuid_source {values};
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
        system_profiler_fixture system_profiler_source({});
        THEN("the result is valid") {
            auto res = vmware(cpuid_source, dmi_source, system_profiler_source);
            REQUIRE(res.valid());
        }
        THEN("the result contains version metdata") {
            auto res = vmware(cpuid_source, dmi_source, system_profiler_source);
            REQUIRE(res.get<string>("version") == "ESXi 6.5");
        }
    }

    WHEN("running as a normal user on a Linux VMware guest") {
        leaf_register_map values {
            {VENDOR_LEAF, {
                {0, register_fixtures::VENDOR_VMwareVMware}}},
            {HYPERVISOR_PRESENT_LEAF, {
                {0, register_fixtures::HYPERVISOR_PRESENT}}}};
        cpuid_fixture cpuid_source {values};
        dmi_fixture_values dmi_source({
            "",
            "Phoenix Technologies LTD",
            "Intel Corporation",
            "440BX Desktop Reference Platform",
            "VMware, Inc.",
            "VMware Virtual Platform",
            {}});
        system_profiler_fixture system_profiler_source({});
        THEN("the result is valid") {
            auto res = vmware(cpuid_source, dmi_source, system_profiler_source);
            REQUIRE(res.valid());
        }
        THEN("the result does not contain version metdata") {
            auto res = vmware(cpuid_source, dmi_source, system_profiler_source);
            REQUIRE(res.get<string>("version") == "");
        }
    }

    WHEN("running in a Windows VMware guest") {
        leaf_register_map values {
            {VENDOR_LEAF, {
                {0, register_fixtures::VENDOR_VMwareVMware}}},
            {HYPERVISOR_PRESENT_LEAF, {
                {0, register_fixtures::HYPERVISOR_PRESENT}}}};
        cpuid_fixture cpuid_source {values};
        dmi_fixture_empty dmi_source;
        system_profiler_fixture system_profiler_source({});
        THEN("the result is valid") {
            REQUIRE(vmware(cpuid_source, dmi_source, system_profiler_source).valid());
        }
    }

    WHEN("running in a MacOS VMware guest") {
        leaf_register_map values {
            {VENDOR_LEAF, {
                {0, register_fixtures::VENDOR_NONE}}},
            {HYPERVISOR_PRESENT_LEAF, {
                {0, register_fixtures::HYPERVISOR_ABSENT}}}};
        cpuid_fixture cpuid_source {values};
        dmi_fixture_empty dmi_source;
        system_profiler_fixture system_profiler_source(system_profiler_fixture::SYSTEM_PROFILER_VMWARE);
        THEN("the result is valid") {
            auto res = vmware(cpuid_source, dmi_source, system_profiler_source);
            REQUIRE(res.valid());
        }
    }

    WHEN("running outside of VMware") {
        leaf_register_map values {
            {VENDOR_LEAF, {
                {0, register_fixtures::VENDOR_KVMKVMKVM}}},
            {HYPERVISOR_PRESENT_LEAF, {
                {0, register_fixtures::HYPERVISOR_PRESENT}}}};
        cpuid_fixture cpuid_source {values};
        dmi_fixture_values dmi_source({
            "Other",
            "Other",
            "Other",
            "Other",
            "Other",
            "Other",
            {}});
        system_profiler_fixture system_profiler_source({});
        THEN("the result is not valid") {
            auto res = vmware(cpuid_source, dmi_source, system_profiler_source);
            REQUIRE_FALSE(res.valid());
        }
    }
}
