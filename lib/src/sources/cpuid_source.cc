#include <internal/sources/cpuid_source.hpp>

using namespace whereami::sources;
using namespace std;

namespace whereami { namespace sources {

    cpuid_registers cpuid_base::read_cpuid(unsigned int leaf, unsigned int subleaf) const {
        cpuid_registers result;
#ifdef __APPLE__
        asm volatile(
            "xchgq %%rbx, %q1; cpuid; xchgq %%rbx, %q1"
            : "=a" (result.eax), "=&r" (result.ebx), "=c" (result.ecx), "=d" (result.edx)
            : "a" (leaf), "c" (subleaf));
#elif defined(__x86_64__) || defined(__i386__)
        // ebx is the PIC register in 32-bit environments; Don't clobber it
        asm volatile(
            "xchgl %%ebx,%k1; xor %%ebx,%%ebx; cpuid; xchgl %%ebx,%k1"
            : "=a" (result.eax), "=&r" (result.ebx), "=c" (result.ecx), "=d" (result.edx)
            : "a" (leaf), "c" (subleaf));
#endif
        return result;
    }

    bool cpuid_base::has_hypervisor() const
    {
        auto regs = read_cpuid(HYPERVISOR_PRESENT);
        return static_cast<bool>(regs.ecx & (1 << 31));
    }

    string cpuid_base::interpret_vendor_registers(cpuid_registers const& regs) const
    {
        unsigned int result[4] = {regs.ebx, regs.ecx, regs.edx, 0};
        return string {reinterpret_cast<char*>(result)};
    }

    string cpuid_base::vendor(unsigned int subleaf) const
    {
        auto regs = read_cpuid(VENDOR_LEAF, subleaf);
        return interpret_vendor_registers(regs);
    }

    bool cpuid_base::has_vendor(string const& vendor_search) const
    {
        auto regs = read_cpuid(VENDOR_LEAF);
        // CPUID returns the maximum queryable leaf value in eax
        unsigned int max_entries = regs.eax;

        // These bounds are the minimum and maximum sane results for Xen offsets
        if (max_entries < 4 || max_entries >= 0x10000) {
            return (interpret_vendor_registers(regs) == vendor_search);
        }

        // Look through valid offsets until the desired vendor is found or we run out
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
