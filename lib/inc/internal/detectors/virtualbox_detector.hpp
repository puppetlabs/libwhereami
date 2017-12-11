#pragma once

#include <whereami/result.hpp>
#include <internal/sources/cpuid_source.hpp>
#include <internal/sources/smbios_base.hpp>
#include <internal/sources/system_profiler_source.hpp>

namespace whereami { namespace detectors {

    /**
     * VirtualBox detector function
     * @param cpuid_source An instance of a CPUID data source
     * @param smbios_source An instance of an SMBIOS data source
     * @param system_profiler_source An instance of a system_profiler data source
     * @return Whether this machine is a VirtualBox guest
     */
    result virtualbox(const sources::cpuid_base& cpuid_source,
                      sources::smbios_base& smbios_source,
                      sources::system_profiler& system_profiler_source);

}}  // namespace whereami::detectors
