#include <whereami/whereami.hpp>
#include <whereami/version.h>
#include <internal/vm.hpp>
#include <internal/sources/dmi_source.hpp>
#include <internal/sources/cpuid_source.hpp>
#include <internal/detectors/virtualbox_detector.hpp>
#include <leatherman/logging/logging.hpp>

using namespace std;
using namespace whereami;

namespace whereami {

    string version()
    {
        LOG_DEBUG("whereami version is {1}", WHEREAMI_VERSION_WITH_COMMIT);
        return WHEREAMI_VERSION_WITH_COMMIT;
    }

    vector<string> hypervisors()
    {
        vector<string> result;
        sources::dmi dmi_source;
        sources::cpuid cpuid_source;

        auto virtualbox_result = detectors::virtualbox(cpuid_source, dmi_source);

        if (virtualbox_result) {
            result.emplace_back(vm::virtualbox);
        }

        return result;
    }
}  // namespace whereami
