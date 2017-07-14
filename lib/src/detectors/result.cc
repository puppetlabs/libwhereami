#include <internal/detectors/result.hpp>

using namespace std;

namespace whereami { namespace detectors {

    bool result::valid() const
    {
        return valid_;
    }

    void result::validate()
    {
        valid_ = true;
    }

    std::string result::name() const
    {
        return name_;
    }
}}  // namespace whereami::detectors
