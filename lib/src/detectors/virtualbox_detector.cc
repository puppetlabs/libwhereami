#include <internal/detectors/virtualbox_detector.hpp>
#include <leatherman/util/regex.hpp>
#include <internal/vm.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace whereami;
using namespace leatherman::util;

namespace whereami { namespace detectors {

    result virtualbox(const sources::cpuid_base& cpuid_source,
                      sources::smbios_base& smbios_source,
                      sources::system_profiler& system_profiler_source) {
        result res {vm::virtualbox};

        if (cpuid_source.vendor() == "VBoxVBoxVBox" ||
            smbios_source.product_name() == "VirtualBox" ||
            system_profiler_source.boot_rom_version() == "VirtualBox") {
            res.validate();

            // Look for VirtualBox version and revision in DMI OEM strings
            auto oem_strings = smbios_source.oem_strings();

            for (auto const& oem_string : oem_strings) {
                if (boost::istarts_with(oem_string, "vboxVer_")) {
                    auto version = oem_string.substr(8, string::npos);
                    res.set("version", version);
                } else if (boost::istarts_with(oem_string, "vboxRev_")) {
                    auto revision = oem_string.substr(8, string::npos);
                    res.set("revision", revision);
                }
            }
        }

        return res;
    }

}}  // namespace whereami::detectors
