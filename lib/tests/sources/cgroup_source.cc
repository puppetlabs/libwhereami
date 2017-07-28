#include <catch.hpp>
#include "../fixtures/cgroup_fixtures.hpp"

using namespace std;
using namespace whereami::sources;
using namespace whereami::testing::cgroup;

SCENARIO("Using the cgroup data source where the cgroup file is not available") {
    cgroup_fixture_empty cgroup_source;
    WHEN("collecting cgroup data") {
        THEN("nothing is found") {
            auto paths = cgroup_source.paths();
            REQUIRE(paths.empty());
        }
    }
}

SCENARIO("Using the cgroup data source where the cgroup file is available") {
    WHEN("collecting cgroup data") {
        cgroup_fixture_path cgroup_source { "cgroup/docker.txt" };
        THEN("only unique paths are collected") {
            auto paths = cgroup_source.paths();
            REQUIRE(paths.size() == 2);
            REQUIRE(paths[0] == "/docker/7a9e0b86b9ede34478c2d4189c61e513c98b5c0215aa36464f1810b5e3c7865c");
            REQUIRE(paths[1] == "/docker");
        }
    }
    WHEN("root paths and paths with multiple controllers paths are present") {
        cgroup_fixture_path cgroup_source { "cgroup/nspawn.txt" };
        THEN("values are still collected successfully") {
            auto paths = cgroup_source.paths();
            REQUIRE(paths.size() == 2);
            REQUIRE(paths[0] == "/machine.slice/machine-name.scope");
            REQUIRE(paths[1] == "/");
        }
    }
    WHEN("the file uses the cgroup v2 format") {
        cgroup_fixture_path cgroup_source { "cgroup/mixed_v1_v2.txt" };
        THEN("values are still collected successfully") {
            auto paths = cgroup_source.paths();
            REQUIRE(paths.size() == 2);
            REQUIRE(paths[0] == "/init.scope");
            REQUIRE(paths[1] == "/");
        }
    }
}

