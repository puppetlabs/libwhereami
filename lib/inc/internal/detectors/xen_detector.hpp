#pragma once

#include <whereami/result.hpp>
#include <internal/sources/cpuid_source.hpp>
#include <internal/sources/dmi_source.hpp>
#include <string>

namespace whereami { namespace detectors {

    /**
     * Xen detector function
     * @param cpuid_source An instance of a CPUID data source
     * @return The Xen detection result
     */
    result xen(const sources::cpuid& cpuid_source);

    /**
     * Path to the directory holding Xen's capabilities file.
     * /proc/xen/capabilities contains the string "control_d" on dom0, and is absent on domU.
     */
    static const std::string xen_path {"proc/xen"};

    /**
     * Determine whether the current domain has a /proc/xen directory. This should be present on both PV and HVM.
     * @return Whether /proc/xen is a directory
     */
    bool has_xen_path();

    /**
     * Determine whether the current domain is dom0 based on the presence of a /proc/xen/capabilities file
     * @param root The root of the file system
     * @return Whether the Xen capabilities file indicates dom0
     */
    bool is_xen_privileged(std::string root = "/");

}}  // namespace whereami::detectors
