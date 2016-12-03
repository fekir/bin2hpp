#include "catch.hpp"

// personal
#include "../bin2hpp.hpp"

// std
#include <iostream>
#include <cassert>
#include <sstream>      // std::stringstream

using namespace bin2hpp;

// TODO: verify content
TEST_CASE("HelloWorldToHex", "[helloworldtohex][lenght][content]"){
	std::stringstream in;
	in << "Hello World!";
	std::stringstream out;
	auto length = convertstreamtohexnotation(in, out);
	//std::cout << "content:\n" << out.str() << "\n";
	REQUIRE(in.str().size() == length);
}


TEST_CASE("LongTextToHex", "[helloworldtohex][lenght][content]"){
	std::string content(10000, 'q');

	std::stringstream in;
	in << content << std::endl;
	std::stringstream out;
	auto length = convertstreamtohexnotation(in, out);
	//std::cout << "content:\n" << out.str() << "\n";
	REQUIRE(in.str().size() == length);
}

// TODO: verify content
TEST_CASE("HelloWorldTostdarray", "[helloworldtostarray]"){
	std::stringstream in;
	in << "Hello World!";
	std::stringstream out;
	create_std_array(in, "myarr", constid_array::_constexpr, out );
	//std::cout << "content:\n" << out.str() << "\n";
}



TEST_CASE("file1","[]"){
	std::stringstream in;
	in << "Hello World!";
	std::ofstream out("/tmp/data2.h");

	bin2hpp::langoptionscpp langopt;
	bin2hpp::create_file(in, langopt, "varname", out);
}
