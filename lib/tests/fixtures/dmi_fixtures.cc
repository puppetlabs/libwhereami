#include "./dmi_fixtures.hpp"

using namespace whereami::testing;
using namespace whereami::sources;
using namespace std;

namespace whereami { namespace testing { namespace dmi {

    std::string dmi_fixture::sys_path(std::string const& filename) const
    {
        return fixture_root + sys_fixture_path_ + filename;
    }

    smbios_data const* dmi_fixture::data()
    {
        if (!data_) {
            string dmidecode_output;
            load_fixture(dmidecode_fixture_path_, dmidecode_output);

            collect_data_from_dmidecode(dmidecode_output);

            if (data_ == nullptr) {
                if (!collect_data_from_sys()) {
                    data_.reset(new smbios_data);
                }
            }
        }
        return data_.get();
    }

    dmi_fixture_values::dmi_fixture_values(sources::smbios_data&& data)
    {
        data_.reset(new smbios_data(move(data)));
    }

    smbios_data const* dmi_fixture_empty::data()
    {
        if (!data_) {
            data_.reset(new smbios_data);
        }
        return data_.get();
    }

}}}  // namespace whereami::testing::dmi
