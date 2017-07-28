#pragma once

#include "../fixtures.hpp"
#include <internal/sources/dmi_source.hpp>
#include <leatherman/util/strings.hpp>
#include <string>
#include <sstream>

namespace whereami { namespace testing { namespace dmi {

    /**
     * DMI data source relying on fixtures for dmidecode output and /sys/class/dmi/id/ files
     */
    class dmi_fixture : public sources::dmi_base {
    public:
        /**
         * Common fixture paths within the fixture base path
         */
        constexpr static char const* SYS_NONE  {"<none>"};
        constexpr static char const* SYS_VIRTUALBOX {"sys/dmi/virtualbox/"};
        constexpr static char const* DMIDECODE_NONE {"dmidecode/none.txt"};
        constexpr static char const* DMIDECODE_VIRTUALBOX {"dmidecode/virtualbox.txt"};
        /**
         * Constructor specifying paths to fixture for /sys files and dmi output
         * @param dmidecode_path
         * @param sys_path
         */
        explicit dmi_fixture(std::string dmidecode_path = DMIDECODE_NONE,
                             std::string sys_path       = SYS_NONE)
            : dmidecode_fixture_path_(std::move(dmidecode_path)),
              sys_fixture_path_(std::move(sys_path)) { }

    protected:
        /**
         * Read /sys/ data from a fixture base path (instead of from /sys/)
         * @return
         */
        std::string sys_path(std::string const& filename = "") const override;
        /**
         * Read dmidecode output data from a fixture file
         * @return
         */
        bool collect_data_from_dmidecode() override;
        /**
         * The dmidecode fixture file path
         */
        std::string dmidecode_fixture_path_;
        /**
         * The /sys/ fixture directory path
         */
        std::string sys_fixture_path_;
    };

    /**
     * DMI data source relying on explicitly specified values
     */
    class dmi_fixture_values : public sources::dmi_base {
    public:
        explicit dmi_fixture_values(sources::dmi_data&& data);
    };

    class dmi_fixture_empty : public sources::dmi_base {
    protected:
        sources::dmi_data const* data() override;
    };

}}}  // namespace whereami::testing::dmi
