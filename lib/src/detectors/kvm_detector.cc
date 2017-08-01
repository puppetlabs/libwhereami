#include <internal/detectors/kvm_detector.hpp>
#include <internal/vm.hpp>
#include <leatherman/util/regex.hpp>

using namespace leatherman::util;

namespace whereami { namespace detectors {

    static const boost::regex parallels_pattern {"^Parallels"};

    result kvm(const sources::cpuid_base& cpuid_source,
               sources::dmi_base& dmi_source)
    {
        result res {vm::kvm};

        // dmidecode under KVM typically reports QEMU, but CPUID does report KVM.
        // VirtualBox and Parallels will also report KVM in CPUID, though, so make sure they're not here.
        if (cpuid_source.vendor() == "KVMKVMKVM"
            && dmi_source.product_name() != "VirtualBox"
            && !re_search(dmi_source.product_name(), parallels_pattern)) {
            res.validate();

            if (dmi_source.bios_vendor() == "Google") {
                res.set("google", true);
            }
        }

        return res;
    }

}}  // namespace whereami::detectors
