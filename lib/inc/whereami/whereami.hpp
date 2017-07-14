#pragma once

#include <internal/detectors/result.hpp>
#include <vector>
#include "export.h"

namespace whereami {

    /**
     * Query the library version.
     * @return A version string with \<major>.\<minor>.\<patch>
     */
    std::string LIBWHEREAMI_EXPORT version();

    /**
     * Try to detect whether this machine is a guest on any hypervisors
     * @return A vector of detected hypervisor names
     */
    std::vector<detectors::result> LIBWHEREAMI_EXPORT hypervisors();

}  // namespace whereami
