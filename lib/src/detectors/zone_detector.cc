#include <internal/detectors/zone_detector.hpp>
#include <internal/vm.hpp>
#include <leatherman/execution/execution.hpp>
#include <leatherman/logging/logging.hpp>
#include <leatherman/util/regex.hpp>
#include <leatherman/util/strings.hpp>

using namespace leatherman::util;
using namespace std;
using namespace whereami;

namespace lth_exe = leatherman::execution;

namespace whereami { namespace detectors {

    result zone()
    {
        result res {vm::zone};

        string zonename_path = lth_exe::which("zonename");
        if (zonename_path.empty()) {
            LOG_DEBUG("zonename executable not found");
            return res;
        }

        auto zonename_result = lth_exe::execute(zonename_path);

        if (!zonename_result.success) {
            LOG_DEBUG("Error while running zonename ({1})", zonename_result.exit_code);
            return res;
        }
        string zonename = zonename_result.output;

        res.validate();
        res.set("name", zonename);

        string zoneadm_path = lth_exe::which("zoneadm");

        if (zoneadm_path.empty()) {
            LOG_DEBUG("zoneadm executable not found");
            return res;
        }

        auto zoneadm_result = lth_exe::execute(zoneadm_path, vector<string>({"list", "-p"}));

        if (!zoneadm_result.success) {
            LOG_DEBUG("Error while running `zoneadm list -p` ({1})", zoneadm_result.exit_code);
            return res;
        }

        parse_zoneadm_output(res, zoneadm_result.output);

        return res;
    }

    void parse_zoneadm_output(result& res, string const& zoneadm_output)
    {
        // The output of `zoneadm list -p` takes this format:
        //     zoneid:zonename:state:zonepath:uuid:brand:ip-type:r/w:file-mac-profile
        static boost::regex zone_pattern("(\\d+|-):([^:]*):[^:]*:[^:]*:([^:]*):([^:]*):([^:]*)");

        string current_zone_name = res.get<string>("name");

        // We need to know the current zone name to match it to useful pieces of zoneadm output; Fail if it's empty.
        if (current_zone_name.empty()) {
            return;
        }

        string zone_name, zone_id, zone_uuid, zone_brand, zone_ip_type;

        each_line(zoneadm_output, [&](string& line) {
            if (re_search(line, zone_pattern, &zone_id, &zone_name, &zone_uuid, &zone_brand, &zone_ip_type) &&
                zone_name == current_zone_name) {
                int id {-1};
                try {
                    id = stoi(zone_id);
                } catch (exception& e) {
                    // The zone ID should be easily converted to a number, but abort if not.
                    return false;
                }
                res.set("id", id);
                res.set("uuid", zone_uuid);
                res.set("brand", zone_brand);
                res.set("ip_type", zone_ip_type);
                return false;
            }
            return true;
        });
    }

}}  // namespace whereami::detectors
