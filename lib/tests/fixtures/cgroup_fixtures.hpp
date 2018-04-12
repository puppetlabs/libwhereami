#include "../fixtures.hpp"
#include <internal/sources/cgroup_source.hpp>
#include <unordered_map>

namespace whereami { namespace testing { namespace cgroup {

    /**
     * cgroup data source returning no usable information
     */
    class cgroup_fixture_empty : public sources::cgroup_base
    {
    public:
        void collect_data() override
        {
            paths_.reset(new std::vector<std::string>);
        }
    };

    /**
     * cgroup data source with predefined cgroup path results
     */
    class cgroup_fixture_values : public sources::cgroup_base
    {
    public:
        explicit cgroup_fixture_values(std::vector<std::string> paths)
        {
            paths_.reset(new std::vector<std::string>(move(paths)));
        }
        void collect_data() override { }
    };

    /**
     * cgroup data source with cgroup file fixture
     */
    class cgroup_fixture_path : public sources::cgroup_base
    {
    public:
        // cppcheck-suppress passedByValue
        explicit cgroup_fixture_path(std::string fixture_path)
            : fixture_path_(fixture_full_path(std::move(fixture_path))) { }
        std::string cgroup_path() const override { return fixture_path_; }
    protected:
        std::string fixture_path_;
    };

}}};  // namespace whereami::testing::cgroup
