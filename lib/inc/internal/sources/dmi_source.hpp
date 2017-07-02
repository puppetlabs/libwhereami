#pragma once

#include <memory>
#include <string>

namespace whereami { namespace sources {

    /**
     * Stores information collected via DMI
     */
    struct dmi_data
    {
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
    };

    /**
     * Base DMI data source
     */
    class dmi_base
    {
    public:
        dmi_base() {}
        virtual ~dmi_base() {}
        /**
         * Retrieve the BIOS vendor
         * @return The BIOS vendor's name
         */
        std::string bios_vendor() const;
        /**
         * Retrieve the board manufacturer
         * @return The board manufacturer's name
         */
        std::string board_manufacturer() const;
        /**
         * Retrieve the board product name
         * @return The board product name
         */
        std::string board_product_name() const;
        /**
         * Retrieve the system manufacturer
         * @return The system manufacturer
         */
        std::string manufacturer() const;
        /**
         * Retrieve the product name
         * @return The product name
         */
        std::string product_name() const;
    protected:
        /**
         * Collected data for this machine based on DMI information
         */
        std::unique_ptr<dmi_data> data_;
    };

    /**
     * Default DMI data source
     */
    class dmi : public dmi_base
    {
     public:
        dmi();
        virtual ~dmi() {}
     protected:
        /**
         * /sys path to user-accessible DMI files on *nix systems
         */
        constexpr static char const* SYS_PATH = "/sys/class/dmi/id/";
        /**
         * Attempt to collect virtualization data using DMI
         */
        virtual void collect_data();
        /**
         * Attempt to collect data from files in /sys/class/dmi/id/
         */
        virtual void collect_data_from_sys();
        /**
         * Attempt to collect data from dmidecode executable (requires root)
         */
        virtual void collect_data_from_dmidecode();
        /**
         * Construct a full pathname for files in /sys/class/dmi/id/
         * @param filename The name of the file expected to exist in /sys/class/dmi/id/, e.g. "bios_vendor"
         * @return The full path to the file
         */
        virtual std::string sys_path(std::string const& filename = "") const;
        /**
         * Read a single DMI file
         * @param path The path to the file
         * @return The contents of the file
         */
        std::string read_file(std::string const& path);
        /**
         * Examine a line of dmidecode output for useful information
         * @param line The contents of the line
         * @param dmi_type Initial dmi_type value, e.g. -1
         */
        void parse_dmidecode_line(std::string& line, int& dmi_type);
    };

}}  // namespace whereami::sources
