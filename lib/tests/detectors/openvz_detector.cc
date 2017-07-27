#include <catch.hpp>
#include <internal/detectors/openvz_detector.hpp>
#include <boost/filesystem.hpp>
#include "../fixtures.hpp"

using namespace std;
using namespace whereami::detectors;
using namespace whereami::testing;
using namespace boost::filesystem;

SCENARIO("Using the OpenVZ detector") {
    WHEN("Running in an OpenVZ container") {
        auto res = openvz(fixture_full_path("filesystem/openvz_detector/container_root/"));
        THEN("the result is positive") {
            REQUIRE(res.valid());
        }
        THEN("cloudlinux is not detected") {
            REQUIRE_FALSE(res.get<bool>("cloudlinux"));
        }
        THEN("it collects the ID") {
            REQUIRE(res.get<int>("id") == 3549);
        }
        THEN("it is not reported as a host") {
            REQUIRE_FALSE(res.get<bool>("host"));
        }
    }

    WHEN("Running on an OpenVZ host") {
        auto res = openvz(fixture_full_path("filesystem/openvz_detector/host_root/"));
        THEN("the result is positive") {
            REQUIRE(res.valid());
        }
        THEN("cloudlinux is not detected") {
            REQUIRE_FALSE(res.get<bool>("cloudlinux"));
        }
        THEN("it collects the ID") {
            REQUIRE(res.get<int>("id") == 0);
        }
        THEN("it is reported as a host") {
            REQUIRE(res.get<bool>("host"));
        }
    }

    WHEN("Running on a Cloudlinux host") {
        auto res = openvz(fixture_full_path("filesystem/openvz_detector/cloudlinux_root/"));
        THEN("the result is positive") {
            REQUIRE(res.valid());
        }
        THEN("cloudlinux is detected") {
            REQUIRE(res.get<bool>("cloudlinux"));
        }
    }
}
