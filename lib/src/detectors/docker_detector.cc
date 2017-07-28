#include <internal/detectors/docker_detector.hpp>
#include <internal/vm.hpp>
#include <leatherman/logging/logging.hpp>
#include <leatherman/util/regex.hpp>

using namespace leatherman::util;
using namespace std;
using namespace whereami;

namespace whereami { namespace detectors {
    result docker(sources::cgroup_base& cgroup_source)
    {
        static const boost::regex docker_pattern { R"(docker\/(.+))" };

        result res { vm::docker };
        string container_id;

        for (auto const& path : cgroup_source.paths()) {
            if (re_search(path, docker_pattern, &container_id)) {
                res.validate();
                res.set("id", container_id);
                return res;
            }
        }

        return res;
    }
}}  // namespace whereami::detectors
