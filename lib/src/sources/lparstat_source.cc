#include <internal/sources/lparstat_source.hpp>
#include <leatherman/execution/execution.hpp>
#include <leatherman/logging/logging.hpp>
#include <leatherman/util/regex.hpp>
#include <leatherman/util/strings.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace leatherman::util;
namespace lth_exe = leatherman::execution;

namespace whereami { namespace sources {

    string lparstat::partition_name()
    {
        return data()->partition_name;
    }

    int lparstat::partition_number()
    {
        return data()->partition_number;
    }

    int lparstat::wpar_key()
    {
        return data()->wpar_key;
    }

    int lparstat::wpar_configured_id()
    {
        return data()->wpar_configured_id;
    }

    bool lparstat::supports_wpar() const
    {
        // AIX >= 6.1 supports WPARs
        return (version_.first > 6 || (version_.first == 6 && version_.second > 0));
    }

    lparstat_data const* lparstat::data()
    {
        if (!data_) {
            data_.reset(new lparstat_data);

            if (collect_aix_version_from_oslevel()) {
                // If we're able to collect the AIX version, try to get the lparstat output
                collect_data_from_lparstat();
            }
        }
        return data_.get();
    }

    bool lparstat::collect_aix_version_from_oslevel()
    {
        string oslevel_path = lth_exe::which("oslevel");

        if (oslevel_path.empty()) {
            LOG_DEBUG("oslevel executable not found");
            return false;
        }
        auto oslevel_result = lth_exe::execute(oslevel_path);

        if (!oslevel_result.success) {
            return false;
        }

        parse_oslevel_output(oslevel_result.output);

        return true;
    }

    void lparstat::parse_oslevel_output(std::string const& oslevel_output)
    {
        static const boost::regex oslevel_pattern {R"(^(\d)\.(\d))"};
        int version_major = 0, version_minor = 0;
        if (re_search(oslevel_output, oslevel_pattern, &version_major, &version_minor)) {
            version_ = {version_major, version_minor};
        }
    }

    bool lparstat::collect_data_from_lparstat()
    {
        string lparstat_path = lth_exe::which("lparstat");

        if (lparstat_path.empty()) {
            LOG_DEBUG("lparstat executable not found");
            return false;
        }

        vector<string> lparstat_flags {"-i"};

        // If WPARs are supported, we can use the -W flag on `lparstat` to get WPAR information:
        if (supports_wpar()) {
            lparstat_flags.emplace_back("-W");
        }

        auto lparstat_result = lth_exe::execute(lparstat_path, lparstat_flags);

        if (!lparstat_result.success) {
            LOG_DEBUG("Error while running lparstat ({1})", lparstat_result.exit_code);
            return false;
        }

        parse_lparstat_output(lparstat_result.output);

        return true;
    }

    void lparstat::parse_lparstat_output(std::string const& lparstat_output)
    {
        each_line(lparstat_output, [&](string& line) {
            vector<string> items;
            boost::split(items, line, boost::is_any_of(":"));

            if (items.size() != 2) {
                return true;
            }

            string key = move(items[0]);
            string value = move(items[1]);

            boost::trim(key);
            boost::trim(value);

            if (key == "Partition Name") {
                data_->partition_name = move(value);
                return true;
            } else if (key == "Partition Number") {
                try {
                    data_->partition_number = stoi(value);
                    // Collection should continue if we're looking for WPAR information, otherwise this is the end
                    if (supports_wpar()) {
                        return true;
                    } else {
                        data_->wpar_configured_id = 0;
                        data_->wpar_key = 0;
                        return false;
                    }
                } catch (exception& e) {
                    return false;
                }
            } else if (key == "WPAR Key") {
                try {
                    data_->wpar_key = stoi(value);
                } catch (exception& e) {
                    return false;
                }
            } else if (key == "WPAR Configured ID") {
                try {
                    data_->wpar_configured_id = stoi(value);
                } catch (exception& e) {
                    return false;
                }
            }
            return true;
        });
    }

}}
