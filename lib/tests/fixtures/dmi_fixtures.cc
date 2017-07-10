#include "./dmi_fixtures.hpp"

using namespace whereami::testing;
using namespace whereami::sources;
using namespace std;

namespace whereami { namespace testing { namespace dmi {

    dmi_fixture_sys::dmi_fixture_sys(const char* base_directory)
        : base_directory_(base_directory)
    {
        collect_data_from_sys();
    }

    std::string dmi_fixture_sys::sys_path(std::string const& filename) const
    {
        return fixture_root + base_directory_ + filename;
    }

    dmi_fixture_dmidecode::dmi_fixture_dmidecode(const char* dmidecode_fixture_path)
        : dmidecode_fixture_path_(dmidecode_fixture_path)
    {
        collect_data_from_dmidecode();
    }
    void dmi_fixture_dmidecode::collect_data_from_dmidecode()
    {
        int dmi_type = -1;
        std::string dmidecode_output;
        if (!load_fixture(dmidecode_fixture_path_, dmidecode_output)) return;
        data_.reset(new dmi_data);
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
