#include <internal/detectors/lpar_detector.hpp>
#include <internal/vm.hpp>

using namespace std;
using namespace whereami;

namespace whereami { namespace detectors {

    result lpar(sources::lparstat& lparstat_source)
    {
        result res {vm::lpar};

        int partition_number = lparstat_source.partition_number();

        if (partition_number > 0) {
            res.validate();
            res.set("partition_number", partition_number);
            res.set("partition_name", lparstat_source.partition_name());
        }

        return res;
    }

}}  // namespace whereami::detectors
