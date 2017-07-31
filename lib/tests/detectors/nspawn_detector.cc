#include <catch.hpp>
#include <internal/detectors/nspawn_detector.hpp>
#include "../fixtures/cgroup_fixtures.hpp"

using namespace std;
using namespace whereami::detectors;
using namespace whereami::sources;
using namespace whereami::testing::cgroup;

SCENARIO("Using the systemd-nspawn detector") {
    WHEN("running in an nspawn container") {
        cgroup_fixture_values cgroup_source({ "/machine.slice/machine-fedora.scope", "/" });
        auto res = nspawn(cgroup_source);
        THEN("nspawn is detected") {
            REQUIRE(res.valid());
        }
        THEN("the machine's name is collected") {
            REQUIRE(res.get<string>("name") == "fedora");
        }
    }

    WHEN("running where /proc/1/cgroup is unavailable") {
        cgroup_fixture_empty cgroup_source;
        auto res = nspawn(cgroup_source);
        THEN("nspawn is not detected") {
            REQUIRE_FALSE(res.valid());
        }
    }

    WHEN("running in another type of container") {
        cgroup_fixture_values cgroup_source({ "/docker/abcdef", "/docker" });
        auto res = nspawn(cgroup_source);
        THEN("nspawn is not detected") {
            REQUIRE_FALSE(res.valid());
        }
    }
}
