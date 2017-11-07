#include <internal/sources/cgroup_source.hpp>
#include <leatherman/file_util/file.hpp>
#include <leatherman/util/regex.hpp>
#include <leatherman/util/strings.hpp>
#include <leatherman/logging/logging.hpp>

using namespace leatherman::util;
namespace lth_file = leatherman::file_util;
using namespace std;

namespace whereami { namespace sources {
    vector<string> cgroup_base::paths()
    {
        if (!paths_) {
            collect_data();
        }
        return *(paths_.get());
    }

    void cgroup_base::collect_data()
    {
        static const boost::regex path_pattern {R"(\d\:.*:(\/.*))"};
        auto file_path = cgroup_path();
        paths_.reset(new vector<string>);
        string contents;

        if (!lth_file::read(file_path, contents)) {
            LOG_DEBUG("File {1} could not be read", file_path);
            return;
        }

        each_line(contents, [&] (const string& line) {
            string path;
            if (re_search(line, path_pattern, &path) &&
                find(paths_->begin(), paths_->end(), path) == paths_->end()) {
                paths_->emplace_back(path);
            }
            return true;
        });
    }
}}  // namespace whereami::sources
