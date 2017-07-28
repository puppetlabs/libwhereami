#include <catch.hpp>
#include <internal/detectors/docker_detector.hpp>
#include "../fixtures/cgroup_fixtures.hpp"

using namespace std;
using namespace whereami::detectors;
using namespace whereami::sources;
using namespace whereami::testing::cgroup;

SCENARIO("Using the Docker detector") {
    WHEN("running in a docker container") {
        cgroup_fixture_values cgroup_source({ "/docker/<hash>", "/docker" });
        auto res = docker(cgroup_source);
        THEN("docker is detected") {
            REQUIRE(res.valid());
        }
        THEN("the container ID is collected") {
            REQUIRE(res.get<std::string>("id") == "<hash>");
        }
    }

    WHEN("running where /proc/1/cgroup is unavailable") {
        cgroup_fixture_empty cgroup_source;
        auto res = docker(cgroup_source);
        THEN("docker is not detected") {
            REQUIRE_FALSE(res.valid());
        }
    }

    WHEN("running in another type of container") {
        cgroup_fixture_values cgroup_source({ "/machine.slice/machine-name.scope", "/" });
        auto res = docker(cgroup_source);
        THEN("docker is not detected") {
            REQUIRE_FALSE(res.valid());
        }
    }
}
