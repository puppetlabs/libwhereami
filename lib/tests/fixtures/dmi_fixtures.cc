#include "./dmi_fixtures.hpp"

using namespace whereami::testing;
using namespace whereami::sources;
using namespace std;

namespace whereami { namespace testing { namespace dmi {

    dmi_fixture::dmi_fixture(std::string const& dmidecode_path, std::string const& sys_path)
        : dmidecode_fixture_path_(dmidecode_path), sys_fixture_path_(sys_path)
    {
        data_.reset(nullptr);
        collect_data();
    }

    std::string dmi_fixture::sys_path(std::string const& filename = "") const
    {
        return fixture_root + sys_fixture_path_ + filename;
    }

    void dmi_fixture::collect_data_from_dmidecode()
    {
        int dmi_type = -1;
        std::string dmidecode_output;
        if (!load_fixture(dmidecode_fixture_path_, dmidecode_output)) return;
        leatherman::util::each_line(dmidecode_output, [&](string& line) {
            parse_dmidecode_line(line, dmi_type);
            return true;
        });
    }

    dmi_fixture_values::dmi_fixture_values(sources::dmi_data&& data)
    {
        data_.reset(new dmi_data(move(data)));
    }

}}}  // namespace whereami::testing::dmi
