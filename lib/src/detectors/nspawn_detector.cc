#include <internal/detectors/nspawn_detector.hpp>
#include <internal/vm.hpp>
#include <leatherman/logging/logging.hpp>
#include <leatherman/util/regex.hpp>

using namespace leatherman::util;
using namespace std;
using namespace whereami;

namespace whereami { namespace detectors {

    result nspawn(sources::cgroup_base& cgroup_source)
    {
        static const boost::regex nspawn_pattern {R"(machine\.slice\/machine-(.+)\.scope$)"};

        result res { vm::systemd_nspawn };
        string container_name;

        for (auto const& path : cgroup_source.paths()) {
            if (re_search(path, nspawn_pattern, &container_name)) {
                res.validate();
                res.set("name", container_name);
                return res;
            }
        }

        return res;
    }

}}
