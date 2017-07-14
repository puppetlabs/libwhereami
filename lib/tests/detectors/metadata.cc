#include <catch.hpp>
#include <internal/detectors/metadata.hpp>

using namespace std;
using namespace whereami;
using namespace whereami::detectors;

SCENARIO("Using a metadata object") {
    WHEN("a string literal metadata value is added") {
        metadata data;
        data.set("foo", "bar");
        THEN("it is retrievable as a string") {
            REQUIRE(data.get<string>("foo") == "bar");
        }
        THEN("it is not retrievable as another data type") {
            REQUIRE_THROWS_AS(data.get<bool>("foo"), boost::bad_get);
        }
    }

    WHEN("a string metadata value is added") {
        metadata data;
        string bar {"bar"};
        data.set("foo", bar);
        THEN("it is retrievable as a string") {
            REQUIRE(data.get<string>("foo") == "bar");
        }
        THEN("it is not retrievable as another data type") {
            REQUIRE_THROWS_AS(data.get<bool>("foo"), boost::bad_get);
        }
    }

    WHEN("a boolean metadata value is added") {
        metadata data;
        data.set("foo", true);
        THEN("it is retrievable as a boolean") {
            REQUIRE(data.get<bool>("foo"));
        }
        THEN("it is not retrievable as another data type") {
            REQUIRE_THROWS_AS(data.get<string>("foo"), boost::bad_get);
        }
    }
}
