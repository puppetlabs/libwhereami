#include <internal/detectors/ldom_detector.hpp>
#include <leatherman/execution/execution.hpp>
#include <leatherman/logging/logging.hpp>
#include <leatherman/util/regex.hpp>
#include <leatherman/util/strings.hpp>
#include <boost/algorithm/string.hpp>
#include <internal/vm.hpp>

using namespace std;
using namespace leatherman::util;
namespace lth_exe = leatherman::execution;

namespace whereami { namespace detectors {

    void parse_virtinfo_output(result& res, string const& virtinfo_output)
    {
        /*
          // Example `virtinfo -a -p` output:
          VERSION 1.0
          DOMAINROLE|impl=LDoms|control=true|io=true|service=true|root=true
          DOMAINNAME|name=primary
          DOMAINUUID|uuid=8e0d6ec5-cd55-e57f-ae9f-b4cc050999a4
          DOMAINCONTROL|name=san-t2k-6
          DOMAINCHASSIS|serialno=0704RB0280
        */

        each_line(virtinfo_output, [&] (string& line) {
            if (!re_search(line, boost::regex("^DOMAIN"))) {
                return true;
            }

            vector<string> items;
            boost::split(items, line, boost::is_any_of("|"));

            if (items.empty()) {
                return true;
            }

            if (items[0] == "DOMAINROLE") {
                // e.g items = ["DOMAINROLE", "impl=LDoms", "control=false", ... ]
                unordered_map<string, string> role_data;
                for (auto const& item : items) {
                    auto pos = item.find('=');
                    if (pos != string::npos) {
                        role_data[item.substr(0, pos)] = item.substr(pos + 1);
                    }
                }

                if (role_data["impl"] == "LDoms") {
                    res.validate();
                } else {
                    return false;
                }

                res.set("role_control", (role_data["control"] == "true"));
                res.set("role_io",      (role_data["io"] == "true"));
                res.set("role_service", (role_data["service"] == "true"));
                res.set("role_root",    (role_data["root"] == "true"));
                return true;
            }

            if (items.size() == 2) {
                // e.g. items = ["DOMAINNAME", "name=sol10-2"]
                auto pos = items[1].find('=');
                if (pos == string::npos) {
                    return true;
                }
                string value = items[1].substr(pos + 1);

                if (items[0] == "DOMAINNAME") {
                    res.set("domain_name", move(value));
                } else if (items[0] == "DOMAINUUID") {
                    res.set("domain_uuid", move(value));
                } else if (items[0] == "DOMAINCONTROL") {
                    res.set("control_domain", move(value));
                } else if (items[0] == "DOMAINCHASSIS") {
                    res.set("chassis_serial", move(value));
                }
            }

            return true;
        });
    }

    result ldom()
    {
        result res {vm::ldom};

        string virtinfo_path = lth_exe::which("virtinfo");

        if (virtinfo_path.empty()) {
            LOG_DEBUG("virtinfo executable not found");
            return res;
        }

        auto virtinfo_result = lth_exe::execute(virtinfo_path, vector<string> {"-a", "-p"});

        if (!virtinfo_result.success) {
            LOG_DEBUG("Error while running virtinfo -a -p ({1})");
            return res;
        }

        parse_virtinfo_output(res, virtinfo_result.output);

        return res;
    }

}}  // namespace whereami::detectors
