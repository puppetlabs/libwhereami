#pragma once

#include <internal/detectors/result.hpp>
#include <internal/sources/cpuid_source.hpp>
#include <internal/sources/smbios_base.hpp>

namespace whereami { namespace detectors {

    /**
     * Hyper-V detector function
     * @param cpuid_source An instance of a CPUID data source
     * @param smbios_source An instance of an SMBIOS data source
     * @return The Hyper-V detection result
     */
    result hyperv(const sources::cpuid_base& cpuid_source, sources::smbios_base& smbios_source);

}}  // namespace whereami::detectors
