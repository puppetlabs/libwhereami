#include <internal/detectors/lxc_detector.hpp>
#include <internal/vm.hpp>
#include <leatherman/util/regex.hpp>

using namespace leatherman::util;
using namespace std;
using namespace whereami;

namespace whereami { namespace detectors {

    result lxc(sources::cgroup_base& cgroup_source)
    {
        static const boost::regex lxc_pattern { R"(^\/lxc\/([^/]+))" };

        result res {vm::lxc};
        string container_name;

        for (auto const& path : cgroup_source.paths()) {
            if (re_search(path, lxc_pattern, &container_name)) {
                res.validate();
                res.set("name", container_name);
                return res;
            }
        }

        return res;
    }

}}  // namespace whereami::detectors
