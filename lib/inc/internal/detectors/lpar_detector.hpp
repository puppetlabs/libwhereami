#pragma once

#include <internal/sources/lparstat_source.hpp>
#include <whereami/result.hpp>

using namespace std;

namespace whereami { namespace detectors {

    /**
     * LPAR detector function
     * @return the LPAR result
     */
    result lpar(sources::lparstat& lparstat_source);

}}  // namespace whereami::detectors
