#include <catch.hpp>
#include "../fixtures/cpuid_fixtures.hpp"

using namespace whereami::sources;
using namespace whereami::testing::cpuid;
using namespace std;

SCENARIO("No cpuid information is available") {
    leaf_register_map values {
        {VENDOR_LEAF, {
            {0, register_fixtures::VENDOR_NONE}}},
        {HYPERVISOR_PRESENT_LEAF, {
            {0, register_fixtures::HYPERVISOR_ABSENT}}}};
    cpuid_fixture cpuid_source {values};
    WHEN("attempting to call cpuid") {
        THEN("no information is found") {
            REQUIRE(cpuid_source.vendor().empty());
            REQUIRE_FALSE(cpuid_source.has_hypervisor());
        }
    }
}

SCENARIO("Using the cpuid data source on a virtual machine") {
    leaf_register_map values {
        {VENDOR_LEAF, {
            {0, register_fixtures::VENDOR_VBoxVBoxVBox}}},
        {HYPERVISOR_PRESENT_LEAF, {
            {0, register_fixtures::HYPERVISOR_PRESENT}}}};
    cpuid_fixture cpuid_source {values};
    WHEN("looking for a hypervisor") {
        THEN("a hypervisor is detected") {
            REQUIRE(cpuid_source.has_hypervisor());
        }
        THEN("a vendor ID is found") {
            REQUIRE(cpuid_source.vendor() == "VBoxVBoxVBox");
        }
    }
}

SCENARIO("Using the cpuid data source on a physical machine") {
    leaf_register_map values {
        {VENDOR_LEAF, {
            {0, register_fixtures::VENDOR_AuthenticAMD}}},
        {HYPERVISOR_PRESENT_LEAF, {
            {0, register_fixtures::HYPERVISOR_ABSENT}}}};
    cpuid_fixture cpuid_source {values};
    WHEN("looking for a hypervisor") {
        THEN("no hypervisor is detected") {
            REQUIRE_FALSE(cpuid_source.has_hypervisor());
        }
        THEN("a vendor ID is still reported") {
            REQUIRE(cpuid_source.vendor() == "AuthenticAMD");
        }
    }
}

SCENARIO("Specifying a subleaf value") {
    leaf_register_map values {
        {VENDOR_LEAF, {
            {0, register_fixtures::XEN_INVALID},
            {1, register_fixtures::VENDOR_XenVMMXenVMM}}}};
    cpuid_fixture cpuid_source {values};
    WHEN("calling CPUID with a nondefault subleaf") {
        THEN("the correct values are returned") {
            REQUIRE(cpuid_source.vendor(1) == "XenVMMXenVMM");
        }
    }
}

SCENARIO("Searching for a vendor ID at an offset leaf") {
    WHEN("the desired ID sits at a higher leaf than the base") {
        leaf_register_map values {
            {VENDOR_LEAF, {
                {0, register_fixtures::XEN_OFFSET}}},
            {VENDOR_LEAF + 0x100, {
                {0, register_fixtures::XEN_INVALID}}},
            {VENDOR_LEAF + 0x200, {
                {0, register_fixtures::VENDOR_XenVMMXenVMM}}}};
        cpuid_fixture cpuid_source {values};
        WHEN("the ID should be found") {
            REQUIRE(cpuid_source.has_vendor("XenVMMXenVMM"));
        }
    }
    WHEN("a higher-offset vendor ID exists but it does not match the desired ID") {
        leaf_register_map values {
            {VENDOR_LEAF, {
                {0, register_fixtures::XEN_OFFSET}}}};
        cpuid_fixture cpuid_source {values};
        THEN("the ID should not be found") {
            REQUIRE_FALSE(cpuid_source.has_vendor("XenVMMXenVMM"));
        }
    }
}
