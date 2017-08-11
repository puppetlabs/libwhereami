#include "./cpuid_fixtures.hpp"

using namespace whereami::testing;
using namespace whereami::sources;
using namespace std;

namespace whereami { namespace testing { namespace cpuid {

    cpuid_registers cpuid_register_fixtures::lookup(unsigned int leaf, unsigned int subleaf) const
    {
        auto it_leaf = register_values_.find(leaf);
        if (it_leaf == register_values_.end()) {
            return {};
        }
        auto it_subleaf = it_leaf->second.find(subleaf);
        if (it_subleaf == it_leaf->second.end()) {
            return {};
        }
        return it_subleaf->second;
    }

}}}  // namespace whereami::testing::cpuid
