#include <internal/detectors/vmware_detector.hpp>
#include <internal/vm.hpp>
#include <leatherman/execution/execution.hpp>
#include <leatherman/util/regex.hpp>

using namespace whereami;
using namespace leatherman::util;
using namespace std;

/**
 * Retrieve the VMware version based on a DMI BIOS address result, if possible
 * @param address The value of the BIOS address from DMI
 * @return The VMware version
 */
static string vmware_bios_address_to_version(int address)
{
    const std::unordered_map<int, std::string> version_map {
        { 0xe8480, "ESXi 2.5" },
        { 0xe7c70, "ESXi 3.0" },
        { 0xe66c0, "ESXi 3.5" },
        { 0xe7910, "ESXi 3.5" },
        { 0xea550, "ESXi 4.0" },
        { 0xea6c0, "ESXi 4.0" },
        { 0xea2e0, "ESXi 4.1" },
        { 0xe72c0, "ESXi 5.0" },
        { 0xea0c0, "ESXi 5.1" },
        { 0xea050, "ESXi 5.5" },
        { 0xe99e0, "ESXi 6.0" },
        { 0xea580, "ESXi 6.5" },
        { 0xea5e0, "Fusion 8.5" },
    };

    auto it = version_map.find(address);

    if (it != version_map.end()) {
        return it->second;
    }
    return {};
}

namespace whereami { namespace detectors {

    result vmware(const sources::cpuid_base& cpuid_source,
                  sources::smbios_base& smbios_source)
    {
        result res {vm::vmware};

        if (smbios_source.manufacturer() == "VMware, Inc." ||
            cpuid_source.vendor() == "VMwareVMware") {
            res.validate();

            auto bios_address = smbios_source.bios_address();
            if (!bios_address.empty()) {
                auto value = stoi(bios_address, nullptr, 16);
                res.set("version", vmware_bios_address_to_version(value));
            }
        }

        return res;
    }

}}  // namespace whereami::detectors
