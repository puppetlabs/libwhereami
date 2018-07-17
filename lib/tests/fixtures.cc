#include "fixtures.hpp"
#include <boost/filesystem.hpp>
#include <boost/nowide/fstream.hpp>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace boost::filesystem;

namespace whereami { namespace testing {

    bool load_fixture(string const& base_path, string& data)
    {
        auto path = fixture_full_path(base_path);
        boost::nowide::ifstream in(path.c_str(), ios_base::in | ios_base::binary);
        if (!in) {
            return false;
        }
        ostringstream buffer;
        buffer << in.rdbuf();
        data = buffer.str();
        return true;
    }

    std::string fixture_full_path(std::string const& base_path)
    {
        return string {LIBWHEREAMI_TESTS_DIRECTORY} + "/fixtures/" + base_path;
    }

}}  // namespace whereami::testing
