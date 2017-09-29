#pragma once

#include <whereami/result.hpp>

namespace whereami { namespace detectors {

    /**
     * Solaris ldom detector function
     * @return the ldom result
     */
    result ldom();

    /**
     * Collect metadata from the output of virtinfo -a -p
     * @param res An ldom result object
     * @param virtinfo_output The output of `virtinfo -a -p`
     */
    void parse_virtinfo_output(result& res, std::string const& virtinfo_output);

}}  // namespace whereami::detectors
