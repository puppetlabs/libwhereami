#include "../fixtures.hpp"
#include <internal/sources/dmi_source.hpp>
#include <leatherman/util/strings.hpp>
#include <string>
#include <sstream>

namespace whereami { namespace testing { namespace dmi {

    using dmi_fixture_empty = sources::dmi_base;

    /**
     * Common fixture paths within the fixture base path
     */
    namespace dmi_fixtures {
        static const std::string SYS_NONE = "<none>";
        static const std::string SYS_VIRTUALBOX = "sys/dmi/virtualbox/";
        static const std::string DMIDECODE_NONE = "dmidecode/none.txt";
        static const std::string DMIDECODE_VIRTUALBOX = "dmidecode/virtualbox.txt";
    }

    /**
     * DMI data source relying on fixtures for dmidecode output and /sys/class/dmi/id/ files
     */
    class dmi_fixture : public sources::dmi {
    public:
        dmi_fixture(std::string dmidecode_path = dmi_fixtures::DMIDECODE_NONE,
                    std::string sys_path       = dmi_fixtures::SYS_NONE);
    protected:
        /**
         * Read /sys/ data from a fixture base path (instead of from /sys/)
         * @return
         */
        std::string sys_path(std::string const&) const override;
        /**
         * Read dmidecode data from a fixture file (instead of the dmidecode executable output)
         * @return
         */
        void collect_data_from_dmidecode() override;
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
        dmi_fixture_values(sources::dmi_data&& data);
        ~dmi_fixture_values() {}
    };

}}}  // namespace whereami::testing::dmi
