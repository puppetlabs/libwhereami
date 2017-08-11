#pragma once

#include <string>

namespace whereami { namespace sources {

    /**
     * Register values returned by CPUID
     */
    struct cpuid_registers
    {
        /**
         * Value from eax register
         */
        unsigned int eax;
        /**
         * Value from ebx register
         */
        unsigned int ebx;
        /**
         * Value from ecx register
         */
        unsigned int ecx;
        /**
         * Value from edx register
         */
        unsigned int edx;
    };

    /**
     * Base cpuid data source
     */
    class cpuid_base
    {
    public:
        /**
         * Call the cpuid instruction
         * @param leaf The value to pass into CPUID via eax; Determines the type of information returned
         * @param subleaf The value to pass into CPUID via ecx; Used for additional options
         * @return Register object with results of the CPUID function
         */
        virtual cpuid_registers read_cpuid(unsigned int leaf, unsigned int subleaf = 0) const;
        /**
         * Determine whether CPUID reports that this system is running on a hypervisor (Calls CPUID with eax = 1)
         * @return whether CPUID reports a hypervisor
         */
        bool has_hypervisor() const;
        /**
         * Retrieve the vendor ID (Calls CPUID with eax = VENDOR_LEAF)
         * @param subleaf An optional subleaf value to pass through to read_cpuid
         * @return the vendor ID string
         */
        std::string vendor(unsigned int subleaf = 0) const;
        /**
         * Most hypervisors store vendor information in this leaf
         * When this value is passed to CPUID, ebx, ecx, and edx report a vendor ID
         */
        static const unsigned int VENDOR_LEAF {0x40000000};
        /**
         * When CPUID is passed a 1, bit 31 of ecx reports whether the machine is running on a hypervisor
         */
        static const unsigned int HYPERVISOR_PRESENT = 1;
    };

    /**
     * Default CPUID data source; Requires no extra functionality beyond the base.
     */
    using cpuid = cpuid_base;

}}  // namespace whereami::sources
