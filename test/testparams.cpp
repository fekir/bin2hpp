#include "catch.hpp"

// personal
#include "../params.hpp"

// std
#include <iostream>
#include <cassert>
#include <sstream>      // std::stringstream
#include <stdexcept>

using namespace params;

////////////////////////////////////////////////////////////////////////
// constspec
TEST_CASE("getconstgeneric1", "[const][array][size][parameters]"){
	std::vector<std::string> cmdline = { options::standard+rev::cpp03, options::constspec+bin2hpp::constid::_constexpr};
	auto lang = params::getlanguage(cmdline);

	bin2hpp::lang_options_cpp langopt;

	REQUIRE_THROWS_AS(overwriteconstspec(cmdline, lang, langopt.const_arr, langopt.const_size), std::runtime_error);
}

TEST_CASE("getconstgeneric2", "[const][array][size][parameters]"){
	std::vector<std::string> cmdline = { options::standard+rev::c11, options::constspec+bin2hpp::constid::_constexpr};
	auto lang = params::getlanguage(cmdline);

	bin2hpp::lang_options_c langopt;

	REQUIRE_THROWS_AS(overwriteconstspec(cmdline, lang, langopt.const_arr, langopt.const_size), std::runtime_error);
}

TEST_CASE("getconstgeneric3", "[const][array][size][parameters]"){
	std::vector<std::string> cmdline = { options::standard+rev::c11, options::constspec+bin2hpp::constid::_const};
	auto lang = params::getlanguage(cmdline);

	bin2hpp::lang_options_c langopt;

	overwriteconstspec(cmdline, lang, langopt.const_arr, langopt.const_size);

	REQUIRE(langopt.const_arr == bin2hpp::constid_array::_const);
}

////////////////////////////////////////////////////////////////////////
// std=c++
TEST_CASE("getlanguage1", "[language][parameters]"){
	std::vector<std::string> cmdline = { };
	auto lang = params::getlanguage(cmdline);
	REQUIRE(lang.id == bin2hpp::lang_id::cpp);
	REQUIRE(lang._cpprev == bin2hpp::cpprev::cpp17);
}

TEST_CASE("getlanguage2", "[language][parameters]"){
	std::vector<std::string> cmdline = { options::standard+rev::cpp};
	auto lang = params::getlanguage(cmdline);
	REQUIRE(lang.id == bin2hpp::lang_id::cpp);
	REQUIRE(lang._cpprev == bin2hpp::cpprev::cpp17);
}

TEST_CASE("getlanguage3", "[language][parameters]"){
	std::vector<std::string> cmdline = { options::standard+rev::cpp98};
	auto lang = params::getlanguage(cmdline);
	REQUIRE(lang.id == bin2hpp::lang_id::cpp);
	REQUIRE(lang._cpprev == bin2hpp::cpprev::cpp98);
}

TEST_CASE("getlanguage4", "[language][parameters]"){
	std::vector<std::string> cmdline = { options::standard+rev::c};
	auto lang = params::getlanguage(cmdline);
	REQUIRE(lang.id == bin2hpp::lang_id::c);
	REQUIRE(lang._crev == bin2hpp::crev::c11);
}

TEST_CASE("getlanguage5", "[language][parameters]"){
	std::vector<std::string> cmdline = { options::standard+rev::c89};
	auto lang = params::getlanguage(cmdline);
	REQUIRE(lang.id == bin2hpp::lang_id::c);
	REQUIRE(lang._crev == bin2hpp::crev::c89);
}

////////////////////////////////////////////////////////////////////////
// namespace
TEST_CASE("getnamespace", "[namespace][parameters]"){
	std::vector<std::string> p = { options::ns+"myres"};
	auto ns = getnamespace(p);
	REQUIRE(ns == "myres");
	REQUIRE(p.empty());
}

TEST_CASE("getnamespace2", "[namespace][parameters]"){
	std::vector<std::string> p = { options::ns+"myres", "c"};
	auto ns = getnamespace(p);
	REQUIRE(ns == "myres");
	REQUIRE(p.size()==1);
}

TEST_CASE("getnamespace4", "[namespace][parameters][invalid]"){
	std::vector<std::string> p = {options::ns, "c"};
	auto ns = getnamespace(p);
	REQUIRE(ns.empty());
	REQUIRE(p.size() == 1);
}

TEST_CASE("getnamespace5", "[namespace][parameters][invalid]"){
	std::vector<std::string> p = {};
	auto ns = getnamespace(p);
	REQUIRE(ns == bin2hpp::defaultnamespace);
	REQUIRE(p.empty());
}

////////////////////////////////////////////////////////////////////////
// input files
TEST_CASE("getinfiles", "[inputfiles][parameters]"){
	std::vector<std::string> p = {options::in, "filea.o", "fileb.o"};
	auto in = getinfiles(p);
	REQUIRE(in.size() == 2);
	REQUIRE(p.empty());
}

TEST_CASE("getinfiles2", "[inputfiles][parameters]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o"};
	auto in = getinfiles(p);
	REQUIRE(in.size() == 2);
	REQUIRE(p.size() == 1);
}

TEST_CASE("getinfiles3", "[inputfiles][parameters]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", options::out};
	auto in = getinfiles(p);
	REQUIRE(in.size() == 2);
	REQUIRE(p.size() == 2);
}

TEST_CASE("getinfiles4", "[inputfiles][parameters]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", options::names};
	auto in = getinfiles(p);
	REQUIRE(in.size() == 2);
	REQUIRE(p.size() == 2);
}

TEST_CASE("getinfiles5", "[inputfiles][parameters]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", options::ns};
	auto in = getinfiles(p);
	REQUIRE(in.size() == 3);
	REQUIRE(p.size() == 1);
}

TEST_CASE("getinfiles6", "[inputfiles][parameters][invalid]"){
	std::vector<std::string> p = {"a", options::in};
	REQUIRE_THROWS_AS(getinfiles(p), std::runtime_error);
	REQUIRE(p.size() == 2);
}

////////////////////////////////////////////////////////////////////////
// output files
TEST_CASE("getoutfiles", "[outputfiles][parameters]"){
	std::vector<std::string> p = {options::in, "filea.o", "fileb.o", options::out, "filea.hpp", "fileb.hpp"};
	auto in = getinfiles(p);
	auto out = getoutfiles(in, p);
	REQUIRE(out.size() == 2);
	REQUIRE(p.empty());
}

TEST_CASE("getoutfiles2", "[outputfiles][parameters]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", options::out, "filea.hpp", "fileb.hpp"};
	auto in = getinfiles(p);
	auto out = getoutfiles(in, p);
	REQUIRE(out.size() == 2);
	REQUIRE(p.size() == 1);
}

TEST_CASE("getoutfiles3", "[outputfiles][parameters]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o"};
	auto in = getinfiles(p);
	auto out = getoutfiles(in, p);
	REQUIRE(out.size() == 2);
	REQUIRE(p.size() == 1);
}

TEST_CASE("getoutfiles4", "[outputfiles][parameters]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", options::out, "file.hpp"};
	auto in = getinfiles(p);
	auto out = getoutfiles(in, p);
	REQUIRE(out.size() == 1);
	REQUIRE(p.size() == 1);
}

TEST_CASE("getoutfiles5", "[outputfiles][parameters]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", options::out, options::in};
	auto in = getinfiles(p);
	auto out = getoutfiles(in, p);
	REQUIRE(out.size() == 1);
	REQUIRE(p.size() == 1);
}

TEST_CASE("getoutfiles6", "[outputfiles][parameters]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", "filec.o", options::out, "filea.hpp", "fileb.hpp"};
	auto in = getinfiles(p);
	REQUIRE_THROWS_AS(getoutfiles(in, p), std::runtime_error);
	REQUIRE(p.size() == 4);
}

TEST_CASE("getoutfiles7", "[outputfiles][parameters][invalid]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", options::out, "filea.hpp", "fileb.hpp", "filec.hpp"};
	auto in = getinfiles(p);
	REQUIRE_THROWS_AS(getoutfiles(in, p), std::runtime_error);
	REQUIRE(p.size() == 5);
}

TEST_CASE("getoutfiles8", "[outputfiles][parameters][invalid]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", options::out};
	auto in = getinfiles(p);
	REQUIRE_THROWS_AS(getoutfiles(in, p), std::runtime_error);
	REQUIRE(p.size() == 2);
}

////////////////////////////////////////////////////////////////////////
// variable names
TEST_CASE("getvarnames", "[names][parameters]"){
	std::vector<std::string> p = {options::in, "filea.o", "fileb.o", options::names, "filea", "fileb"};
	auto in = getinfiles(p);
	auto vn = getvarnames(in, p);
	REQUIRE(vn.size() == 2);
	REQUIRE(p.empty());
}

TEST_CASE("getvarnames2", "[names][parameters]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", options::names, "filea", "fileb"};
	auto in = getinfiles(p);
	auto vn = getvarnames(in, p);
	REQUIRE(vn.size() == 2);
	REQUIRE(p.size() == 1);
}

TEST_CASE("getvarnames3", "[names][parameters]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o"};
	auto in = getinfiles(p);
	auto vn = getvarnames(in, p);
	REQUIRE(vn.size() == 2);
	REQUIRE(p.size() == 1);
}

TEST_CASE("getvarnames4", "[names][parameters]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", options::names, "file"};
	auto in = getinfiles(p);
	REQUIRE_THROWS_AS(getvarnames(in, p), std::runtime_error);
	REQUIRE(p.size() == 3);
}

TEST_CASE("getvarnames5", "[names][parameters]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", options::names, options::in, "fileb"};
	auto in = getinfiles(p);
	auto vn = getvarnames(in, p);
	REQUIRE(vn.size() == 2);
	REQUIRE(p.size() == 1);
}

TEST_CASE("getvarnames6", "[names][parameters]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", "filec.o", options::names, "filea", "fileb"};
	auto in = getinfiles(p);
	REQUIRE_THROWS_AS(getvarnames(in, p), std::runtime_error);
	REQUIRE(p.size() == 4);
}

TEST_CASE("getvarnames7", "[names][parameters][invalid]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", options::names, "filea", "fileb", "filec"};
	auto in = getinfiles(p);
	REQUIRE_THROWS_AS(getvarnames(in, p), std::runtime_error);
	REQUIRE(p.size() == 5);
}


TEST_CASE("getvarnames8", "[names][parameters][invalid]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", options::names, "filea", options::out};
	auto in = getinfiles(p);
	REQUIRE_THROWS_AS(getvarnames(in, p), std::runtime_error);
	REQUIRE(p.size() == 4);
}

TEST_CASE("getvarnames9", "[names][parameters][invalid]"){
	std::vector<std::string> p = {"a", options::in, "filea.o", "fileb.o", options::names, "filea", "fileb", options::out};
	auto in = getinfiles(p);
	auto vn = getvarnames(in, p);
	REQUIRE(vn.size() == 2);
	REQUIRE(p.size() == 2);
}
