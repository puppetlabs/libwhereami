#include <internal/vm.hpp>
#include <internal/detectors/xen_detector.hpp>
#include <leatherman/file_util/file.hpp>
#include <leatherman/logging/logging.hpp>
#include <leatherman/util/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/trim.hpp>

using namespace whereami::sources;
using namespace leatherman::util;
using namespace leatherman::file_util;
using namespace boost::filesystem;
using namespace std;

namespace lth_file = leatherman::file_util;

namespace whereami { namespace detectors {

    bool has_xen_path() {
        return exists(xen_path);
    }

    bool is_xen_privileged(string root) {
        // dom0 and domU should both have a /proc/xen directory, but only hvm will have a capabilities file there
        path capabilities_path {root + xen_path + "/capabilities"};
        if (!is_regular_file(capabilities_path)) {
            return false;
        }

        // The capabilities file contains "control_d" on dom0
        std::string contents;
        if (lth_file::read(capabilities_path.string(), contents)) {
            boost::trim(contents);
            return contents == "control_d";
        }
        return false;
    }

    result xen(const cpuid& cpuid_source) {
        result res {vm::xen};

        // The Xen CPUID vendor string will only show up on HVM
        auto is_hvm = cpuid_source.has_vendor("XenVMMXenVMM");

        if (!is_hvm && !has_xen_path()) {
            return res;
        }

        res.validate();
        res.set("context", is_hvm ? "hvm" : "pv");

        // Determine whether this is dom0 or domU
        res.set("privileged", is_xen_privileged());

        return res;
    }

}}  // namespace whereami::detectors
