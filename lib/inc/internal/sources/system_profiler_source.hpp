#pragma once

#include <memory>
#include <string>
#include <vector>

namespace whereami { namespace sources {

    /**
     * Stores information collected from the system profiler on MacOS
     */
    struct system_profiler_data
    {
        /**
         * The Boot ROM Version, via SPHardwareDataType
         */
        std::string boot_rom_version;

        /**
         * The Model Identifier, via SPHardwareDataType
         */
        std::string model_identifier;

        /**
         * The serial number (system), via SPHardwareDataType
         */
        std::string system_serial_number;
    };

    /**
     * System Profiler data source for MacOS
     */
    class system_profiler
    {
    public:
        /**
         * Retrieve the hardware model identifier
         * @return The model identifier string
         */
        std::string model_identifier();

        /**
         * Retrieve the boot ROM version string
         * @return the boot ROM version string
         */
        std::string boot_rom_version();

        /**
         * Retrieve the system serial number string
         * @return the system serial number string
         */
        std::string system_serial_number();

    protected:
        /**
         * Collected system profiler data values
         */
        std::unique_ptr<system_profiler_data> data_;

        /**
         * Hardware data type argument for the system_profiler executable
         */
        constexpr static char const* hardware_data_type_ = "SPHardwareDataType";

        /**
         * Collect data from system_profiler
         */
        virtual void collect_data();

        /**
         * Collect data if it hasn't been collected yet, and return a pointer to the data object
         * @return A pointer to a populated `system_profiler_data` instance
         */
        virtual system_profiler_data const* data();

        /**
         * Call the system profile executable and return the output
         * @param args Arguments to pass to system_profiler
         * @return The output of system_profiler given the supplied arguments
         */
        virtual std::string read_system_profiler_output(const std::vector<std::string>& args);
    };

}}  // namespace whereami::sources
