#include <catch.hpp>
#include <internal/detectors/kvm_detector.hpp>
#include "../fixtures/cpuid_fixtures.hpp"
#include "../fixtures/dmi_fixtures.hpp"

using namespace std;
using namespace whereami::detectors;
using namespace whereami::sources;
using namespace whereami::testing::dmi;
using namespace whereami::testing::cpuid;

SCENARIO("Using the KVM detector") {
    WHEN("running on a KVM guest") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_KVMKVMKVM},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT},
        });
        dmi_fixture_values dmi_source({
            "0xe8000",
            "SeaBIOS",
            "",
            "",
            "QEMU",
            "Standard PC (i440FX + PIIX, 1996)",
            {},
        });
        auto res = kvm(cpuid_source, dmi_source);
        THEN("KVM is detected") {
            REQUIRE(res.valid());
        }
    }

    WHEN("running on a VirtualBox guest") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_KVMKVMKVM},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT},
        });
        dmi_fixture_values dmi_source({
            "0x30000",
            "VirtualBox",
            "VirtualBox",
            "Oracle Corporation",
            "innotek GmbH",
            "VirtualBox",
            {
                "vboxVer_5.1.22",
                "vboxRev_115126",
            },
        });
        auto res = kvm(cpuid_source, dmi_source);
        THEN("KVM is not detected") {
            REQUIRE_FALSE(res.valid());
        }
    }

    WHEN("running on QEMU without KVM") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_AUTHENTICAMD},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT},
        });
        dmi_fixture_values dmi_source({
            "0xe8000",
            "SeaBIOS",
            "",
            "",
            "QEMU",
            "Standard PC (i440FX + PIIX, 1996)",
            {},
        });
        auto res = kvm(cpuid_source, dmi_source);
        THEN("KVM is not detected") {
            REQUIRE_FALSE(res.valid());
        }
    }

    WHEN("running on a Parallels guest") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_KVMKVMKVM},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT},
        });
        dmi_fixture_values dmi_source({
            "",
            "Parallels Software International Inc.",
            "Parallels Software International Inc.",
            "Parallels Virtual Platform",
            "Parallels Software International Inc.",
            "Parallels Virtual Platform",
            {},
        });
        auto res = kvm(cpuid_source, dmi_source);
        THEN("KVM is not detected") {
            REQUIRE_FALSE(res.valid());
        }
    }

    WHEN("Running on Google Compute Engine") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_KVMKVMKVM},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT},
        });
        dmi_fixture_values dmi_source({
            "0xe8000",
            "Google",
            "Google",
            "Google Compute Engine",
            "Google",
            "Google Compute Engine",
            {},
        });
        auto res = kvm(cpuid_source, dmi_source);
        THEN("KVM is detected") {
            REQUIRE(res.valid());
        }
        THEN("Google Compute Engine is detected") {
            REQUIRE(res.get<bool>("google"));
        }
    }

    WHEN("Running on OpenStack") {
        cpuid_fixture_values cpuid_source({
            {VENDOR_LEAF,        register_fixtures::VENDOR_KVMKVMKVM},
            {HYPERVISOR_PRESENT, register_fixtures::HYPERVISOR_PRESENT},
        });
        dmi_fixture_values dmi_source({
            "0xE8000",
            "SeaBIOS",
            "",
            "",
            "Fedora Project",
            "OpenStack Nova",
            {},
        });
        auto res = kvm(cpuid_source, dmi_source);
        THEN("KVM is detected") {
            REQUIRE(res.valid());
        }
        THEN("OpenStack is detected") {
            REQUIRE(res.get<bool>("openstack"));
        }
    }
}
