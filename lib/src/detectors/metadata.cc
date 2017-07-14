#include <internal/detectors/metadata.hpp>

using namespace std;

namespace whereami { namespace detectors {

    void metadata::set(string const& key, bool value)
    {
        data_.emplace(key, value);
    }

    void metadata::set(string const& key, const char* value)
    {
        data_.emplace(key, string {value});
    }

    void metadata::set(string const& key, string const& value)
    {
        data_.emplace(key, value);
    }

}}  // namespace whereami::detectors
