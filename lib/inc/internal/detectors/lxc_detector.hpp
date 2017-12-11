#pragma once

#include <whereami/result.hpp>
#include <internal/sources/cgroup_source.hpp>

namespace whereami { namespace detectors {

    /**
     * LXC detector function
     * @param cgroup_source A cgroup data source
     * @return the LXC result
     */
    result lxc(sources::cgroup_base& cgroup_source);

}}  // namespace whereami::detectors
