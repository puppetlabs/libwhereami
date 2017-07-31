#include "../fixtures.hpp"
#include <internal/sources/cpuid_source.hpp>
#include <unordered_map>

namespace whereami { namespace testing { namespace cpuid {

    /**
     * CPUID data source returning no usable information
     */
    class cpuid_fixture_empty : public sources::cpuid_base {
    public:
        sources::cpuid_registers read_cpuid(unsigned int leaf) const override;
    };

    /**
     * CPUID data source with predefined register results
     */
    class cpuid_fixture_values : public sources::cpuid_base {
    public:
        cpuid_fixture_values(std::unordered_map<unsigned int, sources::cpuid_registers> values);
        sources::cpuid_registers read_cpuid(unsigned int leaf) const override;

    protected:
        std::unordered_map<unsigned int, sources::cpuid_registers> register_values_;
    };

    /**
     * Expected raw register values
     */
    namespace register_fixtures {
        static const sources::cpuid_registers HYPERVISOR_ABSENT{0, 0, 0, 0};
        static const sources::cpuid_registers HYPERVISOR_PRESENT{0, 0, 3736609283, 0};
        static const sources::cpuid_registers VENDOR_NONE{0, 0, 0, 0};
        static const sources::cpuid_registers VENDOR_AUTHENTICAMD{13, 1752462657, 1145913699, 1769238117};
        static const sources::cpuid_registers VENDOR_KVMKVMKVM{0, 1263359563, 1447775574, 77};
        static const sources::cpuid_registers VENDOR_VBoxVBoxVBox{0, 2020557398, 2020557398, 2020557398};
        static const sources::cpuid_registers VENDOR_VMwareVMware{1073741840, 1635208534, 1297507698, 1701994871};
    }

    /**
     * Aliased here to allow use in cpuid fixture initialization lists
     */
    static const unsigned int VENDOR_LEAF = sources::cpuid_base::VENDOR_LEAF;
    static const unsigned int HYPERVISOR_PRESENT = sources::cpuid_base::HYPERVISOR_PRESENT;

}}};  // namespace whereami::testing::cpuid
