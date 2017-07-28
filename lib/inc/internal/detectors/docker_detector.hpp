#pragma once

#include <internal/detectors/result.hpp>
#include <internal/sources/cgroup_source.hpp>

namespace whereami { namespace detectors {
    /**
     * Docker detector function
     * @param cgroup_source A cgroup data source
     * @return the docker result
     */
    result docker(sources::cgroup_base& cgroup_source);
}}
