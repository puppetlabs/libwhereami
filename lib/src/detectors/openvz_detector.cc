#include <internal/detectors/openvz_detector.hpp>
#include <internal/vm.hpp>
#include <leatherman/file_util/file.hpp>
#include <leatherman/logging/logging.hpp>
#include <leatherman/util/regex.hpp>
#include <boost/filesystem.hpp>

using namespace boost::filesystem;
using namespace leatherman::util;
using namespace std;
using namespace whereami;

namespace lth_file = leatherman::file_util;

namespace whereami { namespace detectors {

    result openvz(const string& root)
    {
        result res {vm::openvz};
        path vz_path = root + "proc/vz";

        // /proc/vz exists on both nodes and containers
        if (!is_directory(vz_path)) {
            return res;
        }

        res.validate();

        // For cloudlinux_root, /proc/lve/list is present, and/or /proc/vz is empty
        res.set(
            "cloudlinux",
            is_regular_file(root + "proc/lve/list") ||
            boost::filesystem::is_empty(vz_path));

        string status_path {root + "proc/1/status"};
        string status_contents;

        if (!lth_file::read(status_path, status_contents)) {
            LOG_DEBUG("{1}: file could not be read.", status_path);
            return res;
        }

        // Collect the container ID
        static boost::regex env_id_pattern {"envID:\\s+(\\d+)"};
        string env_id;

        if (re_search(status_contents, env_id_pattern, &env_id)) {
            auto id = stoi(env_id);
            res.set("id", id);
            // ID will be 0 if this is the host node
            res.set("host", id == 0);
        }

        return res;
    }

}}
