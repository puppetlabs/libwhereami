#include "../fixtures.hpp"
#include <internal/sources/dmi_source.hpp>
#include <leatherman/util/strings.hpp>
#include <string>
#include <sstream>

namespace whereami { namespace testing { namespace dmi {

    /**
     * DMI data source returning no usable information
     */
    using dmi_fixture_empty = whereami::sources::dmi_base;

    /**
     * DMI data source relying on a fixture directory for /sys/class/dmi/id/
     */
    class dmi_fixture_sys : public sources::dmi {
    public:
        /**
         * Constructor setting the fixture base directory
         * @param base_directory within lib/tests/fixtures/
         */
        dmi_fixture_sys(const char* base_directory);
        ~dmi_fixture_sys() {}
    protected:
        /**
         * Base fixture directory containing dmi files for the current test
         */
        std::string base_directory_;
        /**
         * Override sys_path to construct file paths based on a fixture directory instead of /sys/class/dmi/id/
         * @param filename The name of a file to read
         * @return The contents of the file
         */
        std::string sys_path(std::string const&) const override;
    };

    /**
     * DMI data source relying on dmidecode output
     */
    class dmi_fixture_dmidecode : public sources::dmi {
    public:
        /**
         * Constructor specifying the location of the dmidecode output fixture (within lib/tests/fixtures/)
         * @param dmidecode_fixture_path Path to a fixture containing dmidecode output
         */
        dmi_fixture_dmidecode(const char* dmidecode_fixture_path = "");
        ~dmi_fixture_dmidecode() {}
    protected:
        /**
         * The fixture file path
         */
        std::string dmidecode_fixture_path_;
        /**
         * /sys/class/dmi/id/ data collection (noop)
         * @return
         */
        void collect_data_from_sys() override {}
        /**
         * Load data from the fixture file (instead of the dmidecode executable output)
         * @return
         */
        void collect_data_from_dmidecode() override;
    };

    /**
     * DMI data source relying on explicitly specified values
     */
    class dmi_fixture_values : public sources::dmi_base {
    public:
        dmi_fixture_values(sources::dmi_data&& data);
        ~dmi_fixture_values() {}
    };

}}}  // namespace whereami::testing::dmi
