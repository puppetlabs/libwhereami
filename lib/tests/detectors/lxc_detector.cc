#include <catch.hpp>
#include <internal/detectors/lxc_detector.hpp>
#include "../fixtures/cgroup_fixtures.hpp"

using namespace std;
using namespace whereami::detectors;
using namespace whereami::sources;
using namespace whereami::testing::cgroup;

SCENARIO("Using the LXC detector") {
    WHEN("running in an LXC container") {
        cgroup_fixture_values cgroup_source({ "/lxc/name/init.scope" });
        auto res = lxc(cgroup_source);
        THEN("LXC is detected") {
            REQUIRE(res.valid());
        }
        THEN("the container's name is collected") {
            REQUIRE(res.get<std::string>("name") == "name");
        }
    }

    WHEN("running where /proc/1/cgroup is unavailable") {
        cgroup_fixture_empty cgroup_source;
        auto res = lxc(cgroup_source);
        THEN("LXC is not detected") {
            REQUIRE_FALSE(res.valid());
        }
    }

    WHEN("running in another type of container") {
        cgroup_fixture_values cgroup_source({ "/machine.slice/machine-name.scope", "/" });
        auto res = lxc(cgroup_source);
        THEN("LXC is not detected") {
            REQUIRE_FALSE(res.valid());
        }
    }
}
