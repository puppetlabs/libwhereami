#pragma once

#include <internal/detectors/result.hpp>
#include <internal/sources/cgroup_source.hpp>

namespace whereami { namespace detectors {

    /**
     * systemd-nspawn detector function
     * @param cgroup_source A cgroup data source
     * @return The systemd-nspawn detection result
     */
    result nspawn(sources::cgroup_base& cgroup_source);

}}  // namespace whereami::detectors
