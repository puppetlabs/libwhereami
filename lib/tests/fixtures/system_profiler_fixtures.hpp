#pragma once

#include "../fixtures.hpp"
#include <internal/sources/system_profiler_source.hpp>
#include <leatherman/file_util/file.hpp>

namespace lth_file = leatherman::file_util;

namespace whereami { namespace testing { namespace system_profiler {

    class system_profiler_fixture : public sources::system_profiler
    {
    public:
        /**
         * Common fixture paths within the fixture base path
         */
        constexpr static char const* SYSTEM_PROFILER_PHYSICAL {"output/system_profiler/physical.txt"};
        constexpr static char const* SYSTEM_PROFILER_VMWARE {"output/system_profiler/vmware.txt"};

        /**
         * Constructor specifying a path to the system_profiler output fixture
         */
        explicit system_profiler_fixture(std::string const& fixture_path)
            : system_profiler_fixture_path_(fixture_path) { };

    protected:
        /**
         * The path to the desired system_profiler output
         */
        std::string system_profiler_fixture_path_;

        /**
         * Read system_profiler output from a fixture instead of stdout
         */
        virtual std::string read_system_profiler_output(const std::vector<std::string>& args) override {
            return lth_file::read(fixture_full_path(system_profiler_fixture_path_));
        }
    };

}}}  // namespace whereami::testing::system_profiler
