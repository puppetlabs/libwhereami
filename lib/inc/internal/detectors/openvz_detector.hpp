#pragma once

#include <whereami/result.hpp>
#include <string>

namespace whereami { namespace detectors {

    /**
     * OpenVZ detector function
     * @param root The root of the filesystem (intended for testing purposes)
     * @return The OpenVZ detection result
     */
    result openvz(const std::string& root = "/");

}}  // namespace whereami::detectors
