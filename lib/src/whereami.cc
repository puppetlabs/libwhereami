#include <whereami/version.h>
#include <whereami/whereami.hpp>

#include <leatherman/logging/logging.hpp>

namespace whereami {

    using namespace std;

    string version()
    {
        LOG_DEBUG("whereami version is {1}", WHEREAMI_VERSION_WITH_COMMIT);
        return WHEREAMI_VERSION_WITH_COMMIT;
    }

}  // whereami
