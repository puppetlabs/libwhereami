#pragma once

#include "./smbios_base.hpp"

namespace whereami { namespace sources {

    /**
     * DMI source for Linux variants
     */
    class dmi : public smbios_base
    {
    protected:
        /**
         * Collect data if it hasn't been collected yet, and return a pointer to the DMI data object
         * @return A pointer to the collected DMI data
         */
        virtual smbios_data const* data();
        /**
         * Attempt to collect data from files in /sys/class/dmi/id/
         * @return Whether data was collected
         */
        virtual bool collect_data_from_sys();
        /**
         * Attempt to collect data from dmidecode executable output (requires root)
         * @param output The output of the dmidecode executable
         * @return Whether data was collected
         */
        virtual bool collect_data_from_dmidecode(std::string const& output);
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
        /**
         * /sys path to user-accessible DMI files on *nix systems
         */
        constexpr static char const* SYS_PATH {"/sys/class/dmi/id/"};
    };

}}  // namespace whereami::sources
