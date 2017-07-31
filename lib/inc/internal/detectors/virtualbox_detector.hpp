#pragma once

#include <internal/detectors/result.hpp>
#include <internal/sources/dmi_source.hpp>
#include <internal/sources/cpuid_source.hpp>

namespace whereami { namespace detectors {

    /**
     * VirtualBox detector function
     * @param cpuid_source An instance of a CPUID data source
     * @param dmi_source An instance of a DMI data source
     * @return Whether this machine is a VirtualBox guest
     */
    result virtualbox(const sources::cpuid_base& cpuid_source,
                      sources::dmi_base& dmi_source);

}}  // namespace whereami::detectors
