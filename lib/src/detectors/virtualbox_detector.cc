#include <internal/detectors/virtualbox_detector.hpp>
#include <leatherman/logging/logging.hpp>
#include <leatherman/execution/execution.hpp>
#include <leatherman/util/regex.hpp>

using namespace std;
using namespace whereami;
using namespace leatherman::execution;
using namespace leatherman::util;

namespace whereami { namespace detectors {

    bool virtualbox(const sources::dmi_base& dmi_source) {
        static const boost::regex re_virtualbox{"[Vv]irtual[Bb]ox"};

        return re_search(
            dmi_source.product_name(),
            re_virtualbox);
    }

}}  // namespace whereami::detectors
