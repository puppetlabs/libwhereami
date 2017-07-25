#pragma once

#include <memory>
#include <string>
#include <vector>

namespace whereami { namespace sources {

    /**
     * Collects and stores the unique path names of systemd cgroups for PID 1.
     * This information is used in detecting several types of containers.
     */
    class cgroup_base
    {
    public:
        /**
         * Read the contents of /proc/1/cgroup (if uninitialized); Collect PID 1's unique cgroup paths
         * @return Returns unique cgroup paths of PID 1
         */
        std::vector<std::string> paths();
    protected:
        /**
         * Get the name of PID 1's cgroup file in /proc
         * @return Returns the path of PID 1's cgroup file in /proc
         */
        virtual std::string cgroup_path() const { return "/proc/1/cgroup"; }
        /**
         * Read PID 1's cgroup file and collect path names
         */
        virtual void collect_data();
        /**
         * Collected cgroup path names
         */
        std::unique_ptr<std::vector<std::string>> paths_;
    };

    /**
     * Default cgroup data source; Requires no extra functionality beyond the base.
     */
    using cgroup = cgroup_base;

}}  // namespace whereami::sources
