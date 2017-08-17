#include <internal/sources/system_profiler_source.hpp>
#include <leatherman/execution/execution.hpp>
#include <leatherman/logging/logging.hpp>
#include <leatherman/util/regex.hpp>
#include <leatherman/util/strings.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace leatherman::util;

namespace lth_exe = leatherman::execution;

namespace whereami { namespace sources {

    std::string system_profiler::boot_rom_version()
    {
        return data()->boot_rom_version;
    }

    std::string system_profiler::model_identifier()
    {
        return data()->model_identifier;
    }

    std::string system_profiler::system_serial_number()
    {
        return data()->system_serial_number;
    }

    system_profiler_data const* system_profiler::data()
    {
        if (!data_) {
            collect_data();
        }

        return data_.get();
    }

    std::string system_profiler::read_system_profiler_output(const std::vector<std::string>& args)
    {
        string exec_path = lth_exe::which("system_profiler");

        if (exec_path.empty()) {
            return {};
        }

        auto res = lth_exe::execute(exec_path, args);

        if (res.exit_code != 0) {
            return {};
        }

        return res.output;
    }

    void system_profiler::collect_data()
    {
        if (!data_) {
            data_.reset(new system_profiler_data);
        }

        auto output = read_system_profiler_output({hardware_data_type_});

        static const boost::regex boot_rom_version_pattern {"^Boot ROM Version: (.+)$"};
        static const boost::regex model_identifier_pattern {"^Model Identifier: (.+)$"};
        static const boost::regex system_serial_number_pattern {"^Serial Number \\(system\\): (.+)$"};

        string value;
        each_line(output, [&](string& line) {
            boost::trim(line);

            if (re_search(line, boot_rom_version_pattern, &value)) {
                data_->boot_rom_version = move(value);
            } else if (re_search(line, model_identifier_pattern, &value)) {
                data_->model_identifier = move(value);
            } else if (re_search(line, system_serial_number_pattern, &value)) {
                data_->system_serial_number = move(value);
            }
            return true;
        });
    }

}}  // namespace whereami::sources
