#include "./dmi_fixtures.hpp"

using namespace whereami::testing;
using namespace whereami::sources;
using namespace std;

namespace whereami { namespace testing { namespace dmi {

    std::string dmi_fixture::sys_path(std::string const& filename) const
    {
        return fixture_root + sys_fixture_path_ + filename;
    }

    bool dmi_fixture::collect_data_from_dmidecode()
    {
        std::string dmidecode_output;

        if (!load_fixture(dmidecode_fixture_path_, dmidecode_output)) {
            return false;
        }

        int dmi_type {-1};

        leatherman::util::each_line(dmidecode_output, [&](string& line) {
            parse_dmidecode_line(line, dmi_type);
            return true;
        });

        return data_.get() != nullptr;
    }

    dmi_fixture_values::dmi_fixture_values(sources::dmi_data&& data)
    {
        data_.reset(new dmi_data(move(data)));
    }

    dmi_data const* dmi_fixture_empty::data()
    {
        if (!data_) {
            data_.reset(new dmi_data);
        }
        return data_.get();
    }

}}}  // namespace whereami::testing::dmi
