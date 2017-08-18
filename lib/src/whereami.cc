#include <whereami/whereami.hpp>
#include <whereami/version.h>
#include <internal/vm.hpp>
#include <internal/sources/cgroup_source.hpp>
#include <internal/sources/cpuid_source.hpp>
#include <internal/detectors/docker_detector.hpp>
#include <internal/detectors/hyperv_detector.hpp>
#include <internal/detectors/kvm_detector.hpp>
#include <internal/detectors/lxc_detector.hpp>
#include <internal/detectors/openvz_detector.hpp>
#include <internal/detectors/virtualbox_detector.hpp>
#include <internal/detectors/vmware_detector.hpp>
#include <leatherman/logging/logging.hpp>

#if defined(_WIN32)
#include <internal/sources/wmi_source.hpp>
#else
#include <internal/sources/dmi_source.hpp>
#include <internal/sources/system_profiler_source.hpp>
#endif

using namespace std;
using namespace whereami;
using namespace whereami::detectors;

namespace whereami {

    string version()
    {
        LOG_DEBUG("whereami version is {1}", WHEREAMI_VERSION_WITH_COMMIT);
        return WHEREAMI_VERSION_WITH_COMMIT;
    }

    vector<result> hypervisors()
    {
        vector<result> results;

#if defined(_WIN32)
        sources::wmi smbios_source;
#else
        sources::dmi smbios_source;
#endif

        sources::cpuid cpuid_source;
        sources::cgroup cgroup_source;
        sources::system_profiler system_profiler_source;

        auto virtualbox_result = detectors::virtualbox(cpuid_source, smbios_source);

        if (virtualbox_result.valid()) {
            results.emplace_back(virtualbox_result);
        }

        auto vmware_result = detectors::vmware(cpuid_source, smbios_source, system_profiler_source);

        if (vmware_result.valid()) {
            results.emplace_back(vmware_result);
        }

        auto docker_result = detectors::docker(cgroup_source);

        if (docker_result.valid()) {
            results.emplace_back(docker_result);
        }

        auto lxc_result = detectors::lxc(cgroup_source);

        if (lxc_result.valid()) {
            results.emplace_back(lxc_result);
        }

        auto openvz_result = detectors::openvz();

        if (openvz_result.valid()) {
            results.emplace_back(openvz_result);
        }

        auto kvm_result = detectors::kvm(cpuid_source, smbios_source);

        if (kvm_result.valid()) {
            results.emplace_back(kvm_result);
        }

        auto hyperv_result = detectors::hyperv(cpuid_source, smbios_source);

        if (hyperv_result.valid()) {
            results.emplace_back(hyperv_result);
        }

        return results;
    }

}  // namespace whereami
