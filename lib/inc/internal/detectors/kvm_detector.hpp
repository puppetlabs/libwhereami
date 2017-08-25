#pragma once

#include <internal/detectors/result.hpp>
#include <internal/sources/cpuid_source.hpp>
#include <internal/sources/smbios_base.hpp>

namespace whereami { namespace detectors {

    /**
     * KVM detector function
     * @param cpuid_source A CPUID data source
     * @param smbios_source An SMBIOS data source
     * @return the KVM result
     */
    result kvm(const sources::cpuid_base& cpuid_source,
               sources::smbios_base& smbios_source);

}}  // namespace whereami::detectors
