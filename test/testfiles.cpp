#include "catch.hpp"

// personal
#include "../params.hpp"
#include "../bin2hpp.hpp"

// std
#include <iostream>
#include <cassert>
#include <sstream>      // std::stringstream
#include <stdexcept>

using namespace params;

////////////////////////////////////////////////////////////////////////
// constspec
TEST_CASE("testfiledoesnotexist", "[]"){
    std::ifstream input(""); // hopefully does not exist
    std::stringstream output;
    bin2hpp::lang_options_c langop;
    REQUIRE_THROWS_AS(bin2hpp::create_file(input, langop, "", output), std::runtime_error);
}

