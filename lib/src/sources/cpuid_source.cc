#include <internal/sources/cpuid_source.hpp>

using namespace std;
using namespace whereami::sources;

namespace whereami { namespace sources {

#if defined(__x86_64__) || defined(__i386__)
    cpuid_registers cpuid_base::read_cpuid(unsigned int leaf) const {
        cpuid_registers result;
        asm volatile(
            "xchgl %%ebx,%1; xor %%ebx,%%ebx; cpuid; xchgl %%ebx,%1"
            : "=a" (result.eax), "=b" (result.ebx), "=c" (result.ecx), "=d" (result.edx)
            : "a" (leaf), "c" (0));
        return result;
    }
#else
    cpuid_registers cpuid_base::read_cpuid(unsigned int leaf) const {
        return {};
    }
#endif

    bool cpuid_base::has_hypervisor() const
    {
        auto regs = read_cpuid(HYPERVISOR_PRESENT);
        return static_cast<bool>(regs.ecx & (1 << 31));
    }

    string cpuid_base::vendor() const
    {
        auto regs = read_cpuid(VENDOR_LEAF);
        unsigned int result[4] = {regs.ebx, regs.ecx, regs.edx, 0};
        return string{reinterpret_cast<char*>(result)};
    }

}}
