#include <internal/detectors/wpar_detector.hpp>
#include <internal/vm.hpp>

using namespace std;
using namespace whereami;

namespace whereami { namespace detectors {

    result wpar(sources::lparstat& lparstat_source)
    {
        result res {vm::wpar};

        int wpar_key = lparstat_source.wpar_key();

        if (wpar_key > 0) {
            res.validate();
            res.set("key", wpar_key);
            res.set("configured_id", lparstat_source.wpar_configured_id());
        }

        return res;
    }

}}  // namespace whereami::detectors
