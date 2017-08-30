#pragma once

#include <internal/detectors/result.hpp>
#include <internal/sources/cpuid_source.hpp>
#include <internal/sources/smbios_base.hpp>
#include <internal/sources/system_profiler_source.hpp>

namespace whereami { namespace detectors {

    /**
     * VMware detector function
     * @param cpuid_source An instance of a CPUID data source
     * @param smbios_source An instance of an SMBIOS data source
     * @param system_profiler_source An instance of a system_profiler data source
     * @return The VMware detection result
     */
    result vmware(const sources::cpuid_base& cpuid_source,
                  sources::smbios_base& smbios_source,
                  sources::system_profiler& system_profiler_source);

}}  // namespace whereami::detectors
