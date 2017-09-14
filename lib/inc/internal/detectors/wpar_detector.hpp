#pragma once

#include <internal/sources/lparstat_source.hpp>
#include <whereami/result.hpp>

namespace whereami { namespace detectors {

    /**
     * WPAR detector function
     * @return the WPAR result
     */
    result wpar(sources::lparstat& lparstat_source);

}}  // namespace whereami::detectors
