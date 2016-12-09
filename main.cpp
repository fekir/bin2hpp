
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

		auto defaultsettings = bin2hpp::langoptionscpp(lang._cpprev);
		auto par = params::parsecmdlinecpp(cmdline, defaultsettings);
		for (size_t i = 0; i != par.in.size(); i++) {
			std::ifstream input(par.in.at(i));
			std::ofstream output(par.out.at(i));

			bin2hpp::create_file(input, par.langopt, par.names.at(i), output);
		}

	} else if(lang.id == bin2hpp::lang_id::c){

		auto defaultsettings = bin2hpp::langoptionsc(lang._crev);
		auto par = params::parsecmdlinec(cmdline, defaultsettings);
		for (size_t i = 0; i != par.in.size(); i++) {
			std::ifstream input(par.in.at(i));
			std::ofstream output(par.out.at(i));

			bin2hpp::create_file(input, par.langopt, par.names.at(i), output);
		}

	} else {
		std::cerr << "java is not supported yet!\n";
	return 1;
}

return 0;
}
