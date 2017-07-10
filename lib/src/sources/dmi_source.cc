#include <internal/sources/dmi_source.hpp>
#include <leatherman/util/regex.hpp>
#include <leatherman/logging/logging.hpp>
#include <leatherman/file_util/file.hpp>
#include <leatherman/execution/execution.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::filesystem;
namespace bs = boost::system;
namespace lth_file = leatherman::file_util;
using namespace leatherman::util;

namespace whereami { namespace sources {

    std::string dmi_base::bios_vendor() const
    {
        return data_ ? data_->bios_vendor : "";
    }

    std::string dmi_base::board_manufacturer() const
    {
        return data_ ? data_->board_manufacturer : "";
    }

    std::string dmi_base::board_product_name() const
    {
        return data_ ? data_->board_product_name : "";
    }

    std::string dmi_base::product_name() const
    {
        return data_ ? data_->product_name : "";
    }

    std::string dmi_base::manufacturer() const
    {
        return data_ ? data_->manufacturer : "";
    }

    dmi::dmi()
    {
        collect_data();
    }

    void dmi::collect_data()
    {
        collect_data_from_sys();
        if (data_.get() == nullptr) {
            collect_data_from_dmidecode();
        }
    }

    string dmi::sys_path(string const& filename) const
    {
        return SYS_PATH + filename;
    }

    void dmi::collect_data_from_sys()
    {
        // Check that /sys/class/dmi exists
        bs::error_code ec;
        if (is_directory(sys_path(), ec)) {
            data_.reset(new dmi_data);
            data_->bios_vendor = read_file(sys_path("bios_vendor"));
            data_->board_manufacturer = read_file(sys_path("board_vendor"));
            data_->board_product_name = read_file(sys_path("board_name"));
            data_->manufacturer = read_file(sys_path("sys_vendor"));
            data_->product_name = read_file(sys_path("product_name"));
        } else {
            LOG_DEBUG(sys_path() + " cannot be accessed.");
        }
    }

    void dmi::collect_data_from_dmidecode()
    {
        LOG_DEBUG("Using dmidecode to query DMI information.");

        string dmidecode = leatherman::execution::which("dmidecode");

        if (dmidecode.empty()) {
            LOG_DEBUG("dmidecode executable not found");
        } else {
            int dmi_type {-1};
            leatherman::execution::each_line(dmidecode, [&](string& line) {
                parse_dmidecode_line(line, dmi_type);
                return true;
            });
        }
    }

    // Read a single file in the DMI directory
    string dmi::read_file(string const& path)
    {
        bs::error_code ec;
        if (!is_regular_file(path, ec)) {
            LOG_DEBUG("{1}: {2}.", path, ec.message());
            return {};
        }

        string value;
        if (!lth_file::read(path, value)) {
            LOG_DEBUG("{1}: file could not be read.", path);
            return {};
        }

        boost::trim(value);

        // Replace any non-printable ASCII characters with '.'
        // This mimics the behavior of dmidecode
        for (auto& c : value) {
            if (c < 32 || c == 127) {
                c = '.';
            }
        }
        return value;
    }

    void dmi::parse_dmidecode_line(string& line, int& dmi_type)
    {
        static const boost::regex dmi_section_pattern{"^Handle 0x.{4}, DMI type (\\d{1,3})"};

        // Stores the relevant sections; this is in order based on DMI type ID
        // Ensure there's a trailing semicolon on each entry and keep in sync with the switch statement below
        static const vector<vector<string>> sections{
            {   // BIOS (0)
                "vendor:",
            },
            {   // System (1)
                "manufacturer:",
                "product name:",
            },
            {   // Base Board (2)
                "manufacturer:",
                "product name:",
            }
        };

        // Check for a section header
        if (re_search(line, dmi_section_pattern, &dmi_type)) {
            return;
        }

        // Check that we're in a relevant section
        if (dmi_type < 0 || static_cast<size_t>(dmi_type) >= sections.size()) {
            return;
        }

        // Trim leading whitespace
        boost::trim_left(line);

        // Find a matching header
        auto const& headers = sections[dmi_type];
        auto it = find_if(headers.begin(), headers.end(), [&](string const& header) {
            return boost::istarts_with(line, header);
        });
        if (it == headers.end()) {
            return;
        }

        // Get the value and trim it
        string value{line.substr(it->size())};
        boost::trim(value);

        // Calculate the index into the header vector
        auto index = it - headers.begin();

        // Assign to the appropriate member
        string* member{nullptr};
        switch (dmi_type) {
            case 0: {  // BIOS information
                if (index == 0) {
                    member = &data_->bios_vendor;
                }
                break;
            }

            case 1: {  // System information
                if (index == 0) {
                    member = &data_->manufacturer;
                } else if (index == 1 || index == 2) {
                    member = &data_->product_name;
                }
                break;
            }

            case 2: {  // Base board information
                if (index == 0) {
                    member = &data_->board_manufacturer;
                } else if (index == 1 || index == 2) {
                    member = &data_->board_product_name;
                }
                break;
            }

            default:
                break;
        }

        if (member) {
            *member = std::move(value);
        }
    }

}};  // namespace whereami::sources
