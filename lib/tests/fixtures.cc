#include "fixtures.hpp"
#include <boost/filesystem.hpp>
#include <boost/nowide/fstream.hpp>
#include <iostream>
#include <sstream>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#include <boost/thread/thread.hpp>
#include <boost/chrono/duration.hpp>
#pragma GCC diagnostic pop

using namespace std;
using namespace boost::filesystem;

namespace whereami { namespace testing {

    bool load_fixture(string const& name, string& data)
    {
        string path {string {LIBWHEREAMI_TESTS_DIRECTORY} + "/fixtures/" + name};
        boost::nowide::ifstream in(path.c_str(), ios_base::in | ios_base::binary);
        if (!in) {
            return false;
        }
        ostringstream buffer;
        buffer << in.rdbuf();
        data = buffer.str();
        return true;
    }

}}  // namespace whereami::testing
