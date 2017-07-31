#include <internal/sources/dmi_source.hpp>
#include <leatherman/execution/execution.hpp>
#include <leatherman/file_util/file.hpp>
#include <leatherman/logging/logging.hpp>
#include <leatherman/util/regex.hpp>
#include <leatherman/util/strings.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <unordered_map>

using namespace boost::filesystem;
using namespace leatherman::util;
using namespace std;

namespace bs = boost::system;
namespace lth_file = leatherman::file_util;
namespace lth_exe = leatherman::execution;

namespace whereami { namespace sources {

    std::string dmi_base::bios_address()
    {
        return data()->bios_address;
    }

    std::string dmi_base::bios_vendor()
    {
        return data()->bios_vendor;
    }

    std::string dmi_base::board_manufacturer()
    {
        return data()->board_manufacturer;
    }

    std::string dmi_base::board_product_name()
    {
        return data()->board_product_name;
    }

    std::string dmi_base::product_name()
    {
        return data()->product_name;
    }

    std::string dmi_base::manufacturer()
    {
        return data()->manufacturer;
    }

    std::vector<std::string> dmi_base::oem_strings()
    {
        return data()->oem_strings;
    }

    dmi_data const* dmi_base::data()
    {
        if (!data_) {
            // Attempt to use dmidecode first, because it yields extra metadata (requires root)
            if (!collect_data_from_dmidecode()) {
                // Otherwise, collect most of dmidecode's data from user-accessible files in /sys/
                if (!collect_data_from_sys()) {
                    // If both methods failed, the result should be empty
                    data_.reset(new dmi_data);
                }
            }
        }
        return data_.get();
    }

    string dmi_base::sys_path(string const& filename) const
    {
        return SYS_PATH + filename;
    }

    bool dmi_base::collect_data_from_sys()
    {
        if (!is_directory(sys_path())) {
            LOG_DEBUG(sys_path() + " not found.");
            return false;
        }

        if (!data_) {
            data_.reset(new dmi_data);
        }

        data_->bios_vendor = read_file(sys_path("bios_vendor"));
        data_->board_manufacturer = read_file(sys_path("board_vendor"));
        data_->board_product_name = read_file(sys_path("board_name"));
        data_->manufacturer = read_file(sys_path("sys_vendor"));
        data_->product_name = read_file(sys_path("product_name"));

        return true;
    }

    bool dmi_base::collect_data_from_dmidecode()
    {
        LOG_DEBUG("Using dmidecode to query DMI information.");

        string exec_path = lth_exe::which("dmidecode");

        if (exec_path.empty()) {
            LOG_DEBUG("dmidecode executable not found");
            return false;
        }

        auto res = lth_exe::execute(exec_path);

        if (res.exit_code != 0) {
            LOG_DEBUG("Error while running dmidecode ({1})", res.exit_code);
            return false;
        }

        int dmi_type {-1};
        each_line(res.output, [&](string& line) {
            parse_dmidecode_line(line, dmi_type);
            return true;
        });

        return data_.get() == nullptr;
    }

    string dmi_base::read_file(string const& path)
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

    void dmi_base::parse_dmidecode_line(string& line, int& dmi_type)
    {
        static const boost::regex dmi_section_pattern {"^Handle 0x.{4}, DMI type (\\d{1,3})"};

        // Stores the relevant DMI section titles
        static const unordered_map<int, vector<string>> sections {
            { 0, {  // BIOS
                "vendor:",
                "address:",
            }},
            { 1, {  // System
                "manufacturer:",
                "product name:",
            }},
            { 2, {  // Base Board
               "manufacturer:",
               "product name:",
            }},
            { 11, {  // OEM Strings
                "string 1:",
                "string 2:",
                "string 3:",
            }}
        };

        // Check whether this line contains a section header
        if (re_search(line, dmi_section_pattern, &dmi_type)) {
            return;
        }

        // Check that it's a relevant section
        auto const& section_it = sections.find(dmi_type);
        if (section_it == sections.end()) {
            return;
        }

        // Trim leading whitespace
        boost::trim_left(line);

        // Find a matching header
        auto const& headers = (*section_it).second;
        auto it = find_if(headers.begin(), headers.end(), [&](string const& header) {
            return boost::istarts_with(line, header);
        });
        if (it == headers.end()) {
            return;
        }

        // Get the value and trim it
        string value {line.substr(it->size())};
        boost::trim(value);

        // Calculate the index into the header vector
        auto index = it - headers.begin();

        if (!data_) {
            data_.reset(new dmi_data);
        }

        // Assign to the appropriate member
        switch (dmi_type) {
            case 0: {  // BIOS information
                if (index == 0) {
                    data_->bios_vendor = move(value);
                } else if (index == 1) {
                    data_->bios_address = move(value);
                }
                break;
            }

            case 1: {  // System information
                if (index == 0) {
                    data_->manufacturer = move(value);
                } else if (index == 1 || index == 2) {
                    data_->product_name = move(value);
                }
                break;
            }

            case 2: {  // Base board information
                if (index == 0) {
                    data_->board_manufacturer = move(value);
                } else if (index == 1 || index == 2) {
                    data_->board_product_name = move(value);
                }
                break;
            }

            case 11: {  // OEM strings
                data_->oem_strings.emplace_back(move(value));
                break;
            }

            default:
                break;
        }
    }

}};  // namespace whereami::sources
