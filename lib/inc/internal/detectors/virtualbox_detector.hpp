#pragma once

#include <internal/sources/dmi_source.hpp>

namespace whereami { namespace detectors {

    /**
     * VirtualBox detector function
     * @param dmi_source An instance of a DMI data source
     * @return Whether this machine is a VirtualBox guest
     */
    bool virtualbox(const sources::dmi_base& dmi_source);

}}  // namespace whereami::detectors
