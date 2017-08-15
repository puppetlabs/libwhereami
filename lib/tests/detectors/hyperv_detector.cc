#include <catch.hpp>
#include <internal/detectors/hyperv_detector.hpp>
#include "../fixtures/cpuid_fixtures.hpp"
#include "../fixtures/dmi_fixtures.hpp"

using namespace std;
using namespace whereami::detectors;
using namespace whereami::sources;
using namespace whereami::testing::dmi;
using namespace whereami::testing::cpuid;

SCENARIO("Using the Hyper-V detector") {
    cpuid_fixture_values cpuid_empty({
        {VENDOR_LEAF,        register_fixtures::VENDOR_NONE},
        {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT}
    });
    cpuid_fixture_values cpuid_source({
        {VENDOR_LEAF,        register_fixtures::VENDOR_Microsoft_Hv},
        {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT},
    });

    dmi_fixture_values dmi_source({
        "",
        "Microsoft Corporation",
        "Microsoft Corporation",
        "Virtual Machine",
        "Microsoft Corporation",
        "Virtual Machine", {
            "[MS_VM_CERT/SHA1/9b80ca0d5dd061ec9da4e494f4c3fd1196270c22]",
            "00000000000000000000000000000000",
            "To be filled by OEM"},
    });

    WHEN("running on a Hyper-V guest and relying on CPUID") {
        auto res = hyperv(cpuid_source, dmi_source);

        THEN("Hyper-V is detected") {
            REQUIRE(res.valid());
        }
    }

    WHEN("running on a Hyper-V guest and relying on DMI") {
        auto res = hyperv(cpuid_empty, dmi_source);

        THEN("Hyper-V is detected") {
            REQUIRE(res.valid());
        }
    }
}
