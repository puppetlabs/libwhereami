#include <catch.hpp>
#include <iostream>
#include "../fixtures/cpuid_fixtures.hpp"

using namespace std;
using namespace whereami::sources;
using namespace whereami::testing::cpuid;

SCENARIO("No cpuid information is available") {
    cpuid_fixture_empty cpuid_source;
    WHEN("attempting to call cpuid") {
        THEN("no information is found") {
            REQUIRE(cpuid_source.vendor().empty());
            REQUIRE_FALSE(cpuid_source.has_hypervisor());
        }
    }
}

SCENARIO("Using the cpuid data source on a virtual machine") {
    WHEN("looking for a hypervisor") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_VBoxVBoxVBox},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT},
        });
        THEN("a hypervisor is detected") {
            REQUIRE(cpuid_source.has_hypervisor());
        }
        THEN("a vendor ID is found") {
            REQUIRE(cpuid_source.vendor() == "VBoxVBoxVBox");
        }
    }
}

SCENARIO("Using the cpuid data source on a physical machine") {
    WHEN("looking for a hypervisor") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_NONE},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_ABSENT},
        });
        THEN("no hypervisor is detected") {
            REQUIRE_FALSE(cpuid_source.has_hypervisor());
        }
        THEN("no vendor ID is found") {
            REQUIRE(cpuid_source.vendor() == "");
        }
    }
}
