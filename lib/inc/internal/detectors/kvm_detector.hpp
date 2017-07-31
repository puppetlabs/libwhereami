#pragma once

#include <internal/detectors/result.hpp>
#include <internal/sources/cpuid_source.hpp>
#include <internal/sources/dmi_source.hpp>

namespace whereami { namespace detectors {

    /**
     * KVM detector function
     * @param cpuid_source A CPUID data source
     * @param dmi_source A DMI data source
     * @return the KVM result
     */
    result kvm(const sources::cpuid_base& cpuid_source,
               sources::dmi_base& dmi_source);

}}  // namespace whereami::detectors
