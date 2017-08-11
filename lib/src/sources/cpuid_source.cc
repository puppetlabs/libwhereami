#include <internal/sources/cpuid_source.hpp>

using namespace whereami::sources;
using namespace std;

namespace whereami { namespace sources {

    cpuid_registers cpuid_base::read_cpuid(unsigned int leaf, unsigned int subleaf) const {
        cpuid_registers result;
#if defined(__x86_64__) || defined(__i386__)
        // ebx is the PIC register in 32-bit environments; Don't clobber it
        asm volatile(
            "xchgl %%ebx,%1; xor %%ebx,%%ebx; cpuid; xchgl %%ebx,%1"
            : "=a" (result.eax), "=b" (result.ebx), "=c" (result.ecx), "=d" (result.edx)
            : "a" (leaf), "c" (subleaf));
#endif
        return result;
    }

    bool cpuid_base::has_hypervisor() const
    {
        auto regs = read_cpuid(HYPERVISOR_PRESENT);
        return static_cast<bool>(regs.ecx & (1 << 31));
    }

    string cpuid_base::vendor() const
    {
        auto regs = read_cpuid(VENDOR_LEAF);
        // CPUID returns the maximum useful leaf value in eax by default
        unsigned int max_entries = regs.eax;

        if (max_entries < 4 || max_entries >= 0x10000) {
            return (interpret_vendor_registers(regs) == vendor_search);
        }

        for (unsigned int leaf = VENDOR_LEAF + 0x100;
             leaf <= VENDOR_LEAF + max_entries;
             leaf += 0x100) {
            if (interpret_vendor_registers(read_cpuid(leaf)) == vendor_search) {
                return true;
            }
        }

        return false;
    }

}}
