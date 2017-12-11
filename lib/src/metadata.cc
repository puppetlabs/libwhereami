#include <whereami/metadata.hpp>

using namespace std;

namespace whereami {

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

    void metadata::set(string const& key, int value)
    {
        data_.emplace(key, value);
    }

    unordered_map<string, metadata_value> metadata::get_all() const
    {
        return data_;
    }

}  // namespace whereami
