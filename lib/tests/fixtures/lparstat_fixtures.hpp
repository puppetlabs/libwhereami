#pragma once

#include "../fixtures.hpp"
#include <internal/sources/lparstat_source.hpp>

namespace whereami { namespace testing { namespace lparstat {

    class lparstat_fixture : public sources::lparstat
    {
    public:
        /**
         * Constructor taking an AIX version string and a path to an lparstat fixture file
         * @param aix_version_string
         * @param lparstat_fixture_path
         */
        explicit lparstat_fixture(std::string aix_version_string, std::string lparstat_fixture_path)
        : version_string_(move(aix_version_string)), lparstat_fixture_path_(move(lparstat_fixture_path)) { }

    protected:
        /**
         * Fill in version from the version string
         * @return
         */
        bool collect_aix_version_from_oslevel() override {
            parse_oslevel_output(version_string_);
            return this->version_.first > 0;
        }

        /**
         * Fill in data from the lparstat output fixture file
         * @return
         */
        bool collect_data_from_lparstat() override {
            std::string lparstat_output;
            load_fixture(lparstat_fixture_path_, lparstat_output);
            parse_lparstat_output(lparstat_output);
            return true;
        }

        /**
         * Output of oslevel, e.g. 6.1.0.0
         */
        std::string version_string_;

        /**
         * Path to an lparstat output fixture
         */
        std::string lparstat_fixture_path_;
    };

}}}  // namespace whereami::testing::lparstat
