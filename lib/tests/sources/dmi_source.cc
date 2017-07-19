#include <catch.hpp>
#include <internal/sources/dmi_source.hpp>
#include <leatherman/file_util/file.hpp>
#include <leatherman/util/strings.hpp>
#include <boost/filesystem.hpp>
#include "../fixtures/dmi_fixtures.hpp"

using namespace std;
using namespace leatherman::util;
using namespace whereami::sources;
using namespace whereami::testing::dmi;


SCENARIO("Using the DMI data source") {
    WHEN("DMI data is read from /sys/class/dmi/id/") {
        dmi_fixture dmi_source {
            dmi_fixtures::DMIDECODE_NONE,
            dmi_fixtures::SYS_VIRTUALBOX
        };
        THEN("accessible string fields are populated via /sys/") {
            REQUIRE(dmi_source.bios_vendor() == "innotek GmbH");
            REQUIRE(dmi_source.board_manufacturer() == "Oracle Corporation");
            REQUIRE(dmi_source.board_product_name() == "VirtualBox");
            REQUIRE(dmi_source.manufacturer() == "innotek GmbH");
            REQUIRE(dmi_source.product_name() == "VirtualBox");
        }
        THEN("privileged data is unavailable without dmidecode") {
            REQUIRE(dmi_source.bios_address().empty());
            REQUIRE(dmi_source.oem_strings().size() == 0);
        }
    }

    WHEN("DMI data is read from dmidecode") {
        AND_WHEN("output exists but there is no data available") {
            dmi_fixture dmi_source {
                dmi_fixtures::DMIDECODE_NONE,
                dmi_fixtures::SYS_NONE
            };
            THEN("nothing is found") {
                REQUIRE(dmi_source.bios_address().empty());
                REQUIRE(dmi_source.bios_vendor().empty());
                REQUIRE(dmi_source.board_manufacturer().empty());
                REQUIRE(dmi_source.board_product_name().empty());
                REQUIRE(dmi_source.manufacturer().empty());
                REQUIRE(dmi_source.product_name().empty());
                REQUIRE(dmi_source.oem_strings().size() == 0);
            }
        }

        AND_WHEN("output exists and data is available") {
            dmi_fixture dmi_source {
                dmi_fixtures::DMIDECODE_VIRTUALBOX,
                dmi_fixtures::SYS_NONE
            };
            THEN("all fields are populated via dmidecode") {
                REQUIRE(dmi_source.bios_address() == "0xE0000");
                REQUIRE(dmi_source.bios_vendor() == "innotek GmbH");
                REQUIRE(dmi_source.board_manufacturer() == "Oracle Corporation");
                REQUIRE(dmi_source.board_product_name() == "VirtualBox");
                REQUIRE(dmi_source.manufacturer() == "innotek GmbH");
                REQUIRE(dmi_source.product_name() == "VirtualBox");
                REQUIRE(dmi_source.oem_strings().size() == 2);
                REQUIRE(dmi_source.oem_strings()[0] == "vboxVer_5.1.22");
                REQUIRE(dmi_source.oem_strings()[1] == "vboxRev_115126");
            }
        }
    }
}
