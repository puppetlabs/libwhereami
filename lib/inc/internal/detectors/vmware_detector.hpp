#pragma once

#include <internal/detectors/result.hpp>
#include <internal/sources/cpuid_source.hpp>
#include <internal/sources/dmi_source.hpp>
#include <string>

namespace whereami { namespace detectors {

    /**
     * VMware detector function
     * @param cpuid_source An instance of a CPUID data source
     * @param dmi_source An instance of a DMI data source
     * @return The VMware detection result
     */
    result vmware(const sources::cpuid_base& cpuid_source,
                  sources::dmi_base& dmi_source);

}}  // namespace whereami::detectors
