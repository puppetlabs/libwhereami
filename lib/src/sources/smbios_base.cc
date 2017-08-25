#include <internal/sources/smbios_base.hpp>

namespace whereami { namespace sources {

    std::string smbios_base::bios_address()
    {
        return data()->bios_address;
    }

    std::string smbios_base::bios_vendor()
    {
        return data()->bios_vendor;
    }

    std::string smbios_base::board_manufacturer()
    {
        return data()->board_manufacturer;
    }

    std::string smbios_base::board_product_name()
    {
        return data()->board_product_name;
    }

    std::string smbios_base::product_name()
    {
        return data()->product_name;
    }

    std::string smbios_base::manufacturer()
    {
        return data()->manufacturer;
    }

    std::vector<std::string> smbios_base::oem_strings()
    {
        return data()->oem_strings;
    }

}}  // namespace whereami::sources
