#include <internal/detectors/virtualbox_detector.hpp>
#include <leatherman/util/regex.hpp>

using namespace std;
using namespace whereami;
using namespace leatherman::util;

namespace whereami { namespace detectors {

    bool virtualbox(const sources::cpuid_base& cpuid_source,
                    const sources::dmi_base& dmi_source) {
        static const boost::regex re_virtualbox{"[Vv]irtual[Bb]ox"};

        return cpuid_source.vendor() == "VBoxVBoxVBox" ||
            re_search(dmi_source.product_name(), re_virtualbox);
    }

}}  // namespace whereami::detectors
