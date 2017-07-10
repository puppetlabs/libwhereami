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
    WHEN("DMI is not available") {
        dmi_fixture_empty dmi_source;
        THEN("nothing should be found") {
            REQUIRE(dmi_source.bios_vendor().empty());
            REQUIRE(dmi_source.board_manufacturer().empty());
            REQUIRE(dmi_source.board_product_name().empty());
            REQUIRE(dmi_source.manufacturer().empty());
            REQUIRE(dmi_source.product_name().empty());
        }
    }

    WHEN("DMI data is available in /sys/class/dmi/id/") {
        dmi_fixture_sys dmi_source("/sys/dmi/virtualbox/");
        THEN("all fields should be populated via /sys/") {
            REQUIRE(dmi_source.bios_vendor() == "innotek GmbH");
            REQUIRE(dmi_source.board_manufacturer() == "Oracle Corporation");
            REQUIRE(dmi_source.board_product_name() == "VirtualBox");
            REQUIRE(dmi_source.manufacturer() == "innotek GmbH");
            REQUIRE(dmi_source.product_name() == "VirtualBox");
        }
    }

    WHEN("Using dmidecode when data is not available") {
        dmi_fixture_dmidecode dmi_source{"dmidecode/none.txt"};
        THEN("nothing should be found") {
            REQUIRE(dmi_source.bios_vendor().empty());
            REQUIRE(dmi_source.board_manufacturer().empty());
            REQUIRE(dmi_source.board_product_name().empty());
            REQUIRE(dmi_source.manufacturer().empty());
            REQUIRE(dmi_source.product_name().empty());
        }
    }

    WHEN("Using dmidecode when data is available") {
        dmi_fixture_dmidecode dmi_source{"dmidecode/virtualbox.txt"};
        THEN("all fields should be populated via dmidecode") {
            REQUIRE(dmi_source.bios_vendor() == "innotek GmbH");
            REQUIRE(dmi_source.board_manufacturer() == "Oracle Corporation");
            REQUIRE(dmi_source.board_product_name() == "VirtualBox");
            REQUIRE(dmi_source.manufacturer() == "innotek GmbH");
            REQUIRE(dmi_source.product_name() == "VirtualBox");
        }
    }
}
