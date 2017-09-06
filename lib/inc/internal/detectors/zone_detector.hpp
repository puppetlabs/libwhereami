#pragma once

#include <whereami/result.hpp>

namespace whereami { namespace detectors {

    /**
     * Solaris zone detector function
     * @return The zone detection result
     */
    result zone();

    /**
     * Parse information from `zoneadm list -p` and fill in extra metadata on the given result
     * @param res A result object
     * @param res The output of `zoneadm list -p`
     */
    void parse_zoneadm_output(result& res, std::string const& zoneadm_output);

}}  // namespace whereami::detectors
