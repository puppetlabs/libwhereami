#pragma once

#include <memory>
#include <string>
#include <vector>

namespace whereami { namespace sources {

    /**
     * Stores information collected via SMBIOS
     */
    struct smbios_data
    {
        /**
         * The BIOS address
         * Only available via dmidecode section 0 (requires root)
         */
        std::string bios_address;
        /**
         * The name of the BIOS vendor
         * via /sys/class/dmi/id/bios_vendor, dmidecode section 0 vendor, or WMI's bios manufacturer
         */
        std::string bios_vendor;
        /**
         * The board manufacturer
         * via /sys/class/dmi/id/board_vendor, dmidecode section 2 manufacturer, or WMI's base board manufacturer
         */
        std::string board_manufacturer;
        /**
         * The board product name
         * via /sys/class/dmi/id/board_name, dmidecode section 2 product name, or WMI's base board product
         */
        std::string board_product_name;
        /**
         * The system manufacturer (via /sys/class/dmi/id/sys_vendor)
         * via /sys/class/dmi/id/sys_vendor, dmidecode section 1 manufacturer, or WMI's computer system manufacturer
         */
        std::string manufacturer;
        /**
         * The product name
         * via /sys/class/dmi/id/product_name, dmidecode section 1 product name, or WMI's computer system product name
         */
        std::string product_name;
        /**
         * OEM strings
         * via dmidecode section 11 (requires root), or WMI's computer system OEM string array
         */
        std::vector<std::string> oem_strings;
    };

    /**
     * Base SMBIOS data source
     */
    class smbios_base
    {
    public:
        /**
         * Retrieve the BIOS address
         * @return The BIOS address
         */
        std::string bios_address();
        /**
         * Retrieve the BIOS vendor
         * @return The BIOS vendor's name
         */
        std::string bios_vendor();
        /**
         * Retrieve the board manufacturer
         * @return The board manufacturer's name
         */
        std::string board_manufacturer();
        /**
         * Retrieve the board product name
         * @return The board product name
         */
        std::string board_product_name();
        /**
         * Retrieve the system manufacturer
         * @return The system manufacturer
         */
        std::string manufacturer();
        /**
         * Retrieve the product name
         * @return The product name
         */
        std::string product_name();
        /**
         * Retrieve any OEM strings
         * @return A vector of OEM strings
         */
        std::vector<std::string> oem_strings();

    protected:
        /**
         * Collected data for this machine based on SMBIOS information
         */
        std::unique_ptr<smbios_data> data_;
        /**
         * Collect data if it hasn't been collected yet, and return a pointer to the SMBIOS data object
         * @return A pointer to the collected SMBIOS data
         */
        virtual smbios_data const* data() = 0;
    };

}}  // namespace whereami::sources
