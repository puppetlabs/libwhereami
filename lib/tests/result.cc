#include <catch.hpp>
#include <whereami/result.hpp>
#include <internal/vm.hpp>

using namespace std;
using namespace whereami;

SCENARIO("Using a detector result") {
    WHEN("it is newly created") {
        result res {vm::kvm};
        THEN("it is not valid") {
            REQUIRE_FALSE(res.valid());
        }
        THEN("the name can be retrieved") {
            REQUIRE(res.name() == vm::kvm);
        }
        AND_WHEN("it is validated") {
            res.validate();
            THEN("it is valid") {
                REQUIRE(res.valid());
            }
        }
    }

    WHEN("working with metadata") {
        result res {vm::kvm};
        THEN("values can be set") {
            REQUIRE_NOTHROW(res.set("foo", "bar"));
            REQUIRE_NOTHROW(res.set("baz", "zot"));
            AND_THEN("they can be retrieved") {
                REQUIRE(res.get<string>("foo") == "bar");
            }
            AND_THEN("all metadata can be retrieved at once") {
                REQUIRE(res.metadata().size() == 2);
            }
        }
    }
}
