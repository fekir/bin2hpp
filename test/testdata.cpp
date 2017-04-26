#include "catch.hpp"

// personal
#include "../bin2hpp.hpp"

// std
#include <sstream>      // std::stringstream

using namespace bin2hpp;

// TODO: verify content
TEST_CASE("HelloWorldToHex for C source", "[convertstreamtohexnotation][Hello World!][c]"){
	std::stringstream in;
	in << "Hello World!";
	std::stringstream out;
	auto length = convertstreamtohexnotation(in, out);
	REQUIRE(in.str().size() == length);
	std::string out2 = out.str();
	int j = 0;
	for(size_t i = 0; i != out2.size(); ++i, ++j){
		char c = out2.at(i);
		if(j == 4){
			REQUIRE(c == ',');
			j = -1;
		} else if(j == 3 || j == 2){
			REQUIRE((isdigit(c) || (c >= 'A' && c<='F')));
		} else if(j== 1){
			REQUIRE(c == 'x');
		} else {
			REQUIRE(j==0);
			REQUIRE(c == '0');
		}
	}
}

// TODO: verify content
TEST_CASE("HelloWorldToHex for Java source", "[convertstreamtohexnotation][Hello World!][java]"){
	std::stringstream in;
	in << "Hello World!";
	std::stringstream out;
	auto length = convertstreamtohexnotation(in, out, format::java_byte);
	REQUIRE(in.str().size() == length);
	std::string out2 = out.str();
	int j = 0;
	for(size_t i = 0; i != out2.size(); ++i, ++j){
		char c = out2.at(i);
		if(j == 10){
			REQUIRE(c == ',');
			j = -1;
		} else if(j == 9 || j == 8){
			REQUIRE((isdigit(c) || (c >= 'A' && c<='F')));
		} else if(j== 7){
			REQUIRE(c == 'x');
		} else if(j == 6){
			REQUIRE(c == '0');
		} else if(j == 5){
			REQUIRE(c == ')');
		} else if(j == 4){
			REQUIRE(c == 'e');
		} else if(j == 3){
			REQUIRE(c == 't');
		} else if(j == 2){
			REQUIRE(c == 'y');
		} else if(j == 1){
			REQUIRE(c == 'b');
		} else {
			REQUIRE(j==0);
			REQUIRE(c == '(');
		}
	}
}




// TODO: verify content
TEST_CASE("HelloWorldTostdarray", "[helloworldtostarray]"){
	std::stringstream in;
	in << "Hello World!";
	std::stringstream out;
	create_std_array(in, "myarr", constid_array::_constexpr, out );
}



TEST_CASE("file1","[]"){
	std::stringstream in;
	in << "Hello World!";
	std::ofstream out("/tmp/data2.h", std::ofstream::binary);

	bin2hpp::lang_options_cpp langopt;
	bin2hpp::create_file(in, langopt, "varname", out);
}
