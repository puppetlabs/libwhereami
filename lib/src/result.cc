#include <whereami/result.hpp>

using namespace std;

namespace whereami {

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

    unordered_map<string, metadata_value> result::metadata() const
    {
        return metadata_.get_all();
    }

}  // namespace whereami
