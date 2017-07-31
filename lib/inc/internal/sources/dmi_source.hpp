#pragma once

#include <memory>
#include <string>
#include <vector>

namespace whereami { namespace sources {

    /**
     * Stores information collected via DMI
     */
    struct dmi_data
    {
        /**
         * The BIOS address
         * Only available via dmidecode section 0 (requires root)
         */
        std::string bios_address;
        /**
         * The name of the BIOS vendor
         * via /sys/class/dmi/id/bios_vendor or dmidecode section 0 vendor
         */
        std::string bios_vendor;
        /**
         * The board manufacturer
         * via /sys/class/dmi/id/board_vendor or dmidecode section 2 manufacturer
         */
        std::string board_manufacturer;
        /**
         * The board product name
         * via /sys/class/dmi/id/board_name or dmidecode section 2 product name
         */
        std::string board_product_name;
        /**
         * The system manufacturer (via /sys/class/dmi/id/sys_vendor)
         * via /sys/class/dmi/id/sys_vendor or dmidecode section 1 manufacturer
         */
        std::string manufacturer;
        /**
         * The product name
         * via /sys/class/dmi/id/product_name or dmidecode section 1 product name
         */
        std::string product_name;
        /**
         * OEM strings
         * Only available via dmidecode section 11 (requires root)
         */
        std::vector<std::string> oem_strings;
    };

    /**
     * Base DMI data source
     */
    class dmi_base
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
         * /sys path to user-accessible DMI files on *nix systems
         */
        constexpr static char const* SYS_PATH {"/sys/class/dmi/id/"};
        /**
         * Collected data for this machine based on DMI information
         */
        std::unique_ptr<dmi_data> data_;
        /**
         * Collect data if it hasn't been collected yet, and return a pointer to the DMI data object
         * @return A pointer to the collected DMI data
         */
        virtual dmi_data const* data();
        /**
         * Attempt to collect data from files in /sys/class/dmi/id/
         * @return Whether data was collected
         */
        virtual bool collect_data_from_sys();
        /**
         * Attempt to collect data from dmidecode executable (requires root)
         * @return Whether data was collected
         */
        virtual bool collect_data_from_dmidecode();
        /**
         * Examine a line of dmidecode output for useful information
         * @param line The contents of the line
         * @param dmi_type Initial dmi_type value, e.g. -1
         */
        void parse_dmidecode_line(std::string& line, int& dmi_type);
        /**
         * Construct a full pathname for files in /sys/class/dmi/id/
         * @param filename The name of the file expected to exist in /sys/class/dmi/id/, e.g. "bios_vendor"
         * @return The full path to the file
         */
        virtual std::string sys_path(std::string const& filename = "") const;
        /**
         * Read a single DMI file from SYS_PATH
         * @param path The path to the file
         * @return The contents of the file
         */
        std::string read_file(std::string const& path);
    };

    /**
     * Default DMI source; Requires nothing beyond the base.
     */
    using dmi = dmi_base;

}}  // namespace whereami::sources
