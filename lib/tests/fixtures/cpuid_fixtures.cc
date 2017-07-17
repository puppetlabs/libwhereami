#include "./cpuid_fixtures.hpp"

using namespace whereami::testing;
using namespace whereami::sources;
using namespace std;

namespace whereami { namespace testing { namespace cpuid {

    cpuid_registers cpuid_fixture_empty::read_cpuid(unsigned int leaf) const
    {
        return {};
    }

    cpuid_fixture_values::cpuid_fixture_values(std::unordered_map<unsigned int, sources::cpuid_registers> values)
        : register_values_(std::move(values))
    {
    }

    cpuid_registers cpuid_fixture_values::read_cpuid(unsigned int leaf) const
    {
        auto it = register_values_.find(leaf);
        if (it == register_values_.end()) {
            return {};
        }
        return it->second;
    }

}}}  // namespace whereami::testing::cpuid
