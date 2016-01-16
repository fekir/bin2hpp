#include "catch.hpp"

#include "../params.hpp"


using namespace params;

TEST_CASE("help1", "[]"){
	std::vector<std::string> cmdline = { options::help};
	std::fstream empty;
	REQUIRE(params::askedforhelp(cmdline, empty));
}