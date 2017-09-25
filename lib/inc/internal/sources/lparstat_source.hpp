#pragma once

#include <string>
#include <memory>
#include "./lparstat_source.hpp"

namespace whereami { namespace sources {

    /**
     * Stores information collected from `lparstat`
     */
    struct lparstat_data
    {
        /**
         * The partition name
         */
        std::string partition_name;

        /**
         * The partition number
         */
        int partition_number;

        /**
         * WPAR static identifier; 0 for global
         */
        int wpar_key;

        /**
         * WPAR configured identifier; 0 for global
         */
        int wpar_configured_id;
    };

    /**
     * lparstat source for AIX
     */
    class lparstat
    {
    public:
        /**
         * Retrieve the partition name
         * @return The partition name
         */
        std::string partition_name();

        /**
         * Retrieve the partition number
         * @return The partition number
         */
        int partition_number();

        /**
         * Retrieve the WPAR static identifier key
         * @return The key value
         */
        int wpar_key();

        /**
         * Return the WPAR configured identifier
         * @return The ID number
         */
        int wpar_configured_id();

    protected:
        /**
         * The AIX major and minor version
         */
        std::pair<int, int> version_;

        /**
         * Collected lparstat data for this machine
         */
        std::unique_ptr<lparstat_data> data_;

        /**
         * Reports whether the version is sufficient to support WPARs (i.e. AIX 6.1+)
         * @return Whether WPAR is supported
         */
        bool supports_wpar() const;

        /**
         * Collect data if it hasn't been collected yet, and return a pointer to the lparstat data object
         * @return A pointer to the collected lparstat data
         */
        virtual lparstat_data const* data();

        /**
         * Collect and set the AIX version from the output of `oslevel`
         * @return Whether the version was set successfully
         */
        virtual bool collect_aix_version_from_oslevel();

        /**
         * Collect information from lparstat. Calls `lparstat -iW` on AIX 6.1+, which includes WPAR information. Calls `lparstat -i` on <6.1.
         * @return Whether any data was collected
         */
        virtual bool collect_data_from_lparstat();

        /**
         * Set the AIX version based on the output of `oslevel`
         * @param oslevel_output The output of `oslevel`
         */
        void parse_oslevel_output(std::string const& oslevel_output);

        /**
         * Collect information from `lparstat` or `lparstat -iW`
         * @param lparstat_output  The output of `lparstat`
         */
        void parse_lparstat_output(std::string const& lparstat_output);
    };

}}  // namespace whereami::sources
