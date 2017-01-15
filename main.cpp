
//
#include "params.hpp"
#include "bin2hpp.hpp"

// std
#include <string>
#include <fstream>



int main(int argc, char *argv[]){
	auto cmdline = params::cmdlinetovector(argc, argv);

	if(params::askedforhelp(cmdline, std::cout)){
		return 0;
	}
	auto lang = params::getlanguage(cmdline);

	if(lang.id == bin2hpp::lang_id::cpp) {

		auto defaultsettings = bin2hpp::lang_options_cpp(lang._cpprev);
		auto par = params::parsecmdlinecpp(cmdline, defaultsettings);
		for (size_t i = 0; i != par.in.size(); i++) {
			std::ifstream input(par.in.at(i), std::ifstream::binary);
			std::ofstream output(par.out.at(i), std::ofstream::binary);

			bin2hpp::create_file(input, par.langopt, par.names.at(i), output);
		}

	} else if(lang.id == bin2hpp::lang_id::c){

		auto defaultsettings = bin2hpp::lang_options_c(lang._crev);
		auto par = params::parsecmdlinec(cmdline, defaultsettings);
		for (size_t i = 0; i != par.in.size(); i++) {
			std::ifstream input(par.in.at(i), std::ifstream::binary);
			std::ofstream output(par.out.at(i), std::ofstream::binary);

			bin2hpp::create_file(input, par.langopt, par.names.at(i), output);
		}

	} else if(lang.id == bin2hpp::lang_id::java){
		auto defaultsettings = bin2hpp::lang_options_java(lang._javarev);
		auto par = params::parsecmdline_java(cmdline, defaultsettings);
		for (size_t i = 0; i != par.in.size(); i++) {
			std::ifstream input(par.in.at(i), std::ifstream::binary);
			std::ofstream output(par.out.at(i), std::ofstream::binary);

			bin2hpp::create_file(input, par.langopt, par.names.at(i), "", output);
		}

	} else {
		assert(false && "unrecognized language");
	}
	return 0;
}
