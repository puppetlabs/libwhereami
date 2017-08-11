#include <internal/sources/cpuid_source.hpp>
#include "../fixtures.hpp"
#include <unordered_map>

namespace whereami { namespace testing { namespace cpuid {

    /**
     * Mapping of CPUID leaf and subleaf values to returned register values
     */
    using leaf_register_map = std::unordered_map<unsigned int, std::unordered_map<unsigned int, sources::cpuid_registers>>;

    class cpuid_register_fixtures {
    public:
        /**
         * @param values
         */
        cpuid_register_fixtures(leaf_register_map values) : register_values_(std::move(values)) {}
        /**
         * @param leaf
         * @param subleaf
         * @return
         */
        sources::cpuid_registers lookup(unsigned int leaf, unsigned int subleaf) const;
    protected:
        leaf_register_map register_values_;
    };

    /**
     * CPUID data source with predefined register results
     */
    class cpuid_fixture : public sources::cpuid_base {
    public:
        cpuid_fixture(cpuid_register_fixtures values) : register_values_(std::move(values)) {};
        sources::cpuid_registers read_cpuid(unsigned int leaf, unsigned int subleaf = 0) const override {
            return register_values_.lookup(leaf, subleaf);
        }
    protected:
        cpuid_register_fixtures register_values_;
    };

    protected:
        std::unordered_map<unsigned int, sources::cpuid_registers> register_values_;
    };

    /**
     * Expected raw register values
     */
    namespace register_fixtures {
        static const sources::cpuid_registers HYPERVISOR_ABSENT {0, 0, 0, 0};
        static const sources::cpuid_registers HYPERVISOR_PRESENT {0, 0, 3736609283, 0};
        static const sources::cpuid_registers VENDOR_NONE {0, 0, 0, 0};
        static const sources::cpuid_registers VENDOR_AuthenticAMD {13, 1752462657, 1769238117, 1145913699};
        static const sources::cpuid_registers VENDOR_KVMKVMKVM {0, 1263359563, 1447775574, 77};
        static const sources::cpuid_registers VENDOR_VBoxVBoxVBox {0, 2020557398, 2020557398, 2020557398};
        static const sources::cpuid_registers VENDOR_VMwareVMware {1073741840, 1635208534, 1297507698, 1701994871};
        static const sources::cpuid_registers VENDOR_XenVMMXenVMM {1073741828, 1450075480, 1700285773, 1296914030};
        static const sources::cpuid_registers VERSION_XEN_48 {262152, 0, 0, 0};
        static const sources::cpuid_registers XEN_INVALID {7, 832, 832, 0};
    }

    /**
     * Aliased here to allow use in cpuid fixture initialization lists
     */
    static const unsigned int VENDOR_LEAF {sources::cpuid_base::VENDOR_LEAF};
    static const unsigned int HYPERVISOR_PRESENT_LEAF {sources::cpuid_base::HYPERVISOR_PRESENT};
    static const unsigned int XEN_VERSION_LEAF {sources::cpuid_xen::VERSION_LEAF};

}}};  // namespace whereami::testing::cpuid
