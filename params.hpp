#ifndef PARAMS_HEADER
#define PARAMS_HEADER

#include "bin2hpp.hpp"

#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include <cassert>
#include <algorithm>
#include <utility>
#include <tuple>

namespace params{

	inline bool begins_with(const std::string& str1, const std::string& str2){
		return str1.compare(0, str2.size(), str2) == 0;
	}

	enum param_errors : int{ // fixme: non vengono ancora usati
		noerror = 0
		, invalid_namespaceoption // ie: -ns && -nons
		, invalid_namespacename   // ie: name contains strange character, comincia per punto, whitesapce, ...
		, invalid_varsize         // ie: # files != # names
		, invalid_varname         // ie: name contains strange character, comincia per punto, whitesapce, ...
		, invalid_constqual       // ie: invalid const param
		, invalid_language        // ie: -std=c++15
		, invalid_outputscount    // ie: # files in != # files out && # files out > 1
	};

	namespace options{

		const std::string ns       = "-ns=";
		const std::string pragma   = "-pragma";
		const std::string standard = "-std=";
		    // c++98, c++03, c++11, c++14, c++17   | std::array/constexpr: c++11 | namespace : c++
		    // c89, c99, c11
		    // j1.3, j1.4, j1.5, j1.6, j1.7, j1.8  | generics: j1.5  | byte[], Byte[]/Object[], ArrayList<Byte>/ ArrayList<Object>
		const std::string constspec  = "-const=";     // const, constexpr
		const std::string constsize  = "-constsize="; // enum, const, constexpr
		const std::string constarray = "-constarr=";  // const, constexpr
		const std::string vartype    = "-vartype=";   // std::array, c_array, string, ...

		const std::string in       = "-in";
		const std::string out      = "-out";
		const std::string names    = "-names";
		const std::string help     = "-h";
	}

	namespace rev {
		const std::string cpp   = "c++";
		const std::string cpp98 = "c++98";
		const std::string cpp03 = "c++03";
		const std::string cpp11 = "c++11";
		const std::string cpp14 = "c++14";
		const std::string cpp17 = "c++17";
		const std::string c     = "c";
		const std::string c89   = "c89";
		const std::string c99   = "c99";
		const std::string c11   = "c11";
		const std::string j     = "java";
		const std::string j1_3  = "java1.3";
		const std::string j1_4  = "java1.4";
		const std::string j1_5  = "java1.5";
		const std::string j1_6  = "java1.6";
		const std::string j1_7  = "java1.7";
		const std::string j1_8  = "java1.8";
		const std::string j1_9  = "java1.9";
	}

	/// does not store argc[0]
	inline std::vector<std::string> cmdlinetovector(int argc, const char * const * argv){
		assert(argc >= 0);
		if(argc == 0){
			return {};
		}
		std::vector<std::string> toreturn;
		toreturn.reserve(static_cast<size_t>(argc-1));
		for(int i = 1; i < argc; ++i){
			toreturn.push_back(argv[i]);
		}
		return toreturn;
	}

	inline bin2hpp::language tolang(const std::string& lang){

		bin2hpp::language toreturn;
		// cpp
		toreturn.id = bin2hpp::lang_id::cpp;
		if(lang==rev::cpp || lang == rev::cpp17){
			toreturn._cpprev = bin2hpp::cpp_rev::cpp17;
			return toreturn;
		}
		if(lang == rev::cpp98){
			toreturn._cpprev = bin2hpp::cpp_rev::cpp98;
			return toreturn;
		}
		if(lang == rev::cpp03){
			toreturn._cpprev = bin2hpp::cpp_rev::cpp03;
			return toreturn;
		}
		if(lang == rev::cpp11){
			toreturn._cpprev = bin2hpp::cpp_rev::cpp11;
			return toreturn;
		}
		if(lang == rev::cpp14){
			toreturn._cpprev = bin2hpp::cpp_rev::cpp14;
			return toreturn;
		}

		// c
		toreturn.id = bin2hpp::lang_id::c;
		if(lang==rev::c || lang == rev::c11){
			toreturn._crev = bin2hpp::c_rev::c11;
			return toreturn;
		}
		if(lang == rev::c89){
			toreturn._crev = bin2hpp::c_rev::c89;
			return toreturn;
		}
		if(lang == rev::c99){
			toreturn._crev = bin2hpp::c_rev::c99;
			return toreturn;
		}

		// java
		toreturn.id = bin2hpp::lang_id::java;
		if(lang==rev::j || lang == rev::j1_9){
			toreturn._javarev = bin2hpp::java_rev::j1_9;
			return toreturn;
		}
		if(lang == rev::j1_3){
			toreturn._javarev = bin2hpp::java_rev::j1_3;
			return toreturn;
		}
		if(lang == rev::j1_4){
			toreturn._javarev = bin2hpp::java_rev::j1_4;
			return toreturn;
		}
		if(lang == rev::j1_5){
			toreturn._javarev = bin2hpp::java_rev::j1_5;
			return toreturn;
		}
		if(lang == rev::j1_6){
			toreturn._javarev = bin2hpp::java_rev::j1_6;
			return toreturn;
		}
		if(lang == rev::j1_7){
			toreturn._javarev = bin2hpp::java_rev::j1_7;
			return toreturn;
		}
		if(lang == rev::j1_8){
			toreturn._javarev = bin2hpp::java_rev::j1_8;
			return toreturn;
		}

		throw std::runtime_error("No valid language or language revision specified");
	}

	inline bool askedforhelp(const std::vector<std::string>& params, std::ostream& out){
		const auto itinend = std::find(params.begin(), params.end(), options::in);
		const auto it   = std::find(params.begin(), itinend, options::help);
		if( it == itinend && !params.empty()){
			return false;
		}

		const std::string indent(4, ' ');
		out << "Usage: bin2hpp [options] -in [input files] -names [optional names] -out [optional output files]\n";
		out << "\n Options:\n ========\n"; // fixme, get length of title

		out << indent << options::ns << " <namespace>\n";
		out << indent << indent << "for specifying namespace, use "<<options::ns<<"\"\" for removing the namespace. Default namespace is \"resource\"\n";

		out << indent << options::pragma << "\n";
		out << indent << indent << "for using a pragma instead of an include guard\n";

		out << indent << options::standard << " <standard-id>\n";
		out << indent << indent << "for specifying language and/or language revision, for example " << options::standard << rev::cpp11 << ".\n";
		out << indent << indent << "Valid revisions for c++ are:  " << rev::cpp << ", " << rev::cpp98 << ", " << rev::cpp03 << ", " << rev::cpp11 << ", " << rev::cpp14 << ", " << rev::cpp17 << "\n";
		out << indent << indent << "Valid revisions for c are:    " << rev::c << ", " << rev::c89 << ", " << rev::c99 << ", " << rev::c11 << "\n";
		out << indent << indent << "Valid revisions for java are: " << rev::j << ", " << rev::j1_3 << ", " << rev::j1_4 << ", " << rev::j1_5 << ", " << rev::j1_6 << ", " << rev::j1_7 << ", " << rev::j1_8 << ", " << rev::j1_9 << "\n";

		out << indent << options::constspec << " <const-id>\n";
		out << indent << indent << "for specifying const id of array and size.\n";

		out << indent << options::constsize << " <const-id>.\n";
		out << indent << indent << "for specifying const id of size.\n";

		out << indent << options::constarray << " <const-id>\n";
		out << indent << indent << "for specifying const id of array.\n";

		out << indent << options::vartype << "<vartype>\n";
		out << indent << indent << "for c++:       " << bin2hpp::array_id::_std_arr << ", " << bin2hpp::array_id::_std_string << "\n";
		out << indent << indent << "for c and c++: " << bin2hpp::array_id::_c_arr << ", " << bin2hpp::array_id::_c_string << "\n";
		out << indent << indent << "for java:      " << bin2hpp::array_id::_byte_arr << ", "
		    << bin2hpp::array_id::_Byte_arr << ", " << bin2hpp::array_id::_string << ", " << bin2hpp::array_id::_list << "\n";

		out << indent << options::in << " <list-input-files>\n";
		out << indent << indent << " list of input files, separated by space.\n";

		out << indent << options::out << " <list-output-files>\n";
		out << indent << indent << "list of output files, separated by space.\n";

		out << indent << options::names << " <list-variable-names>\n";
		out << indent << indent << "list of variable names, separated by space.\n";
		return true;
	}

	inline bin2hpp::language getlanguage(std::vector<std::string>& params){
		const auto itinend = std::find(params.begin(), params.end(), options::in);
		const auto it   = std::find_if(params.begin(), itinend, [](const std::string& s){return begins_with(s, options::standard);});
		if( it != itinend ){
			assert(it->length() >= options::standard.length());
			if(it->length() == options::standard.length()){
				throw std::runtime_error("option -lang without name"); // invalidparam_namespace
			}
			std::string lang = it->substr(options::standard.length()); // fixme: validate namespace
			params.erase(it);
			return tolang(lang);
		}
		bin2hpp::language toreturn;
		return toreturn;
	}

	inline std::string getnamespace(std::vector<std::string>& params){
		const auto itinend = std::find(params.begin(), params.end(), options::in);
		const auto it   = std::find_if(params.begin(), itinend, [](const std::string& s){return begins_with(s, options::ns);});
		if( it == itinend ) {
			return bin2hpp::defaultnamespace;
		}

		assert(it->length() >= options::ns.length() && "impossible since it should contain at least options::ns");
		std::string toreturn = it->substr(options::ns.length()); // fixme: validate namespace
		params.erase(it);
		return toreturn;
	}

	inline std::vector<std::string> getinfiles(std::vector<std::string>& params){
		const auto it = std::find(params.begin(), params.end(), options::in);
		if(it == params.end() || it+1 == params.end()){
			throw std::runtime_error("no input files");
		}

		auto itend = std::find(params.begin(), params.end(), options::names);
		if(itend == params.end()){ // there are no names specified
			itend = std::find(params.begin(), params.end(), options::out);
		}

		std::vector<std::string> toreturn;
		toreturn.reserve(std::distance(it, itend));
		for(auto i = it +1; i != itend; ++i){
			// fixme: validate #files > 0
			if(i->empty()){
				throw std::runtime_error("invalid filename");
			}
			toreturn.push_back(*i);
		}
		params.erase(it, itend);
		return toreturn;
	}

	// replace invalid chars with '_'
	inline std::string tovarname(const std::string& filename){
		const size_t lastSlashIndex = filename.find_last_of("/\\");
		std::string var = filename.substr(lastSlashIndex + 1);
		std::replace_if(var.begin(), var.end(), [](char c){
			switch(c){
				case '.':
				case '?':
					return true;
				default:
					return false;
			}
		}, '_');
		return var;
	}

	inline std::vector<std::string> getvarnames(const std::vector<std::string>& in, std::vector<std::string>& params){
		const auto it = std::find(params.begin(), params.end(), options::names);
		if(it == params.end()){
			std::vector<std::string> toreturn(in.size());
			std::transform(in.begin(), in.end(), toreturn.begin(), [](const std::string& inputfile){ return tovarname(inputfile);}); // fixme: validate and unique
			return toreturn;
		}

		const auto itend = std::find(params.begin(), params.end(), options::out);
		const auto numberofelements = std::distance(it+1, itend);
		assert(numberofelements>0);
		auto numberofelements_pos = static_cast<decltype(in.size())>(numberofelements);
		if(numberofelements_pos != in.size()){
			throw std::runtime_error("invalid # of names");
		}

		std::vector<std::string> toreturn;
		toreturn.reserve(numberofelements_pos);
		for(auto i = it +1; i != itend; ++i){
			if(i->empty()){// fixme: validate filenames...
				throw std::runtime_error("invalid name");
			}
			toreturn.push_back(*i);
		}
		params.erase(it, itend);
		return toreturn;
	}

	inline std::vector<std::string> getoutfiles(const std::vector<std::string>& in, std::vector<std::string>& params){
		const auto it = std::find(params.begin(), params.end(), options::out);
		if(it == params.end()){
			std::vector<std::string> toreturn(in.size());
			std::transform(in.begin(), in.end(), toreturn.begin(), [](const std::string& inputfile){ return inputfile +".hpp";});
			return toreturn;
		}

		const auto itend = params.end();
		const auto numberofelements = std::distance(it+1, itend);
		assert(numberofelements >= 0);
		const auto numberofelements_pos = static_cast<decltype(in.size())>(numberofelements);
		if(numberofelements_pos != in.size() && numberofelements != 1){
			throw std::runtime_error("invalid # of files");
		}

		std::vector<std::string> toreturn;
		toreturn.reserve(numberofelements_pos);
		for(auto i = it +1; i != itend; ++i){
			if(i->empty()){// fixme: validate filenames...
				throw std::runtime_error("invalid filename");
			}
			toreturn.push_back(*i);
		}
		params.erase(it, itend);
		return toreturn;
	}

	inline bool usepragma(std::vector<std::string>& params){
		const auto itinend = std::find(params.begin(), params.end(), options::in);
		const auto it = std::find(params.begin(), itinend, options::pragma);
		if(it == itinend){
			return false;
		}
		params.erase(it);
		return true;
	}

	inline void overwriteconstspec(std::vector<std::string>& params, const bin2hpp::language& constspec, bin2hpp::constid_array& c_arr, bin2hpp::constid_size& c_siz ){
		auto itinend       = std::find(params.begin(), params.end(), options::in);

		{
			const auto itcons = std::find_if(params.begin(), itinend,
			                                 [](const std::string &s) { return begins_with(s, options::constspec); }
			);
			if (itcons != itinend) {
				if(constspec.id == bin2hpp::lang_id::java){
					throw std::runtime_error("java does not accept a const id");
				}
				std::string o_c_size = itcons->substr(options::constspec.length());
				const auto tmp = params.erase(itcons);
				itinend = std::find(tmp, params.end(), options::in); // reload since we have invalidated the iterator
				if (o_c_size == "const") {
					c_siz = bin2hpp::constid_size::_const;
					c_arr = bin2hpp::constid_array::_const;
				} else if (o_c_size == bin2hpp::constid::_constexpr) {
					if(constspec.id != bin2hpp::lang_id::cpp || !bin2hpp::has_constexpxr(constspec._cpprev)){
						throw std::runtime_error("invalid const specifier for the specified language");
					}
					c_siz = bin2hpp::constid_size::_constexpr;
					c_arr = bin2hpp::constid_array::_constexpr;
				} else {
					throw std::runtime_error("invalid const specifier");
				}
			}
		}

		{
			const auto itconstsize = std::find_if(params.begin(), itinend,
			                                      [](const std::string &s) {
				                                      return begins_with(s, options::constsize);
			                                      }
			);
			if (itconstsize != itinend) {
				if(constspec.id == bin2hpp::lang_id::java){
					throw std::runtime_error("java does not accept a const id");
				}
				std::string o_c_size = itconstsize->substr(options::constsize.length()); // fixme: validate namespace
				const auto tmp = params.erase(itconstsize);
				itinend = std::find(tmp, params.end(), options::in); // reload since we have invalidated the iterator
				if (o_c_size == bin2hpp::constid::_const) {
					c_siz = bin2hpp::constid_size::_const;
				} else if (o_c_size == bin2hpp::constid::_enum) {
					c_siz = bin2hpp::constid_size::_enum;
				} else if (o_c_size == bin2hpp::constid::_constexpr) {
					if(constspec.id != bin2hpp::lang_id::cpp || !bin2hpp::has_constexpxr(constspec._cpprev)){
						throw std::runtime_error("invalid const specifier for the specified language");
					}
					c_siz = bin2hpp::constid_size::_constexpr;
				} else {
					throw std::runtime_error("invalid const specifier");
				}
			}
		}

		{
			const auto itconstarray = std::find_if(params.begin(), itinend,
			                                       [](const std::string &s) {
				                                       return begins_with(s, options::constarray);
			                                       }
			);

			if (itconstarray != itinend) {
				if(constspec.id == bin2hpp::lang_id::java){
					throw std::runtime_error("java does not accept a const id");
				}
				std::string o_c_arr = itconstarray->substr(options::constarray.length()); // fixme: validate namespace
				const auto tmp = params.erase(itconstarray); // reload since we have invalidated the iterator
				itinend = std::find(tmp, params.end(), options::in);
				if (o_c_arr == bin2hpp::constid::_const) {
					c_arr = bin2hpp::constid_array::_const;
				} else if (o_c_arr == bin2hpp::constid::_constexpr) {
					if(constspec.id != bin2hpp::lang_id::cpp || !bin2hpp::has_constexpxr(constspec._cpprev)){
						throw std::runtime_error("invalid const specifier for the specified language");
					}
					c_arr = bin2hpp::constid_array::_constexpr;
				} else {
					throw std::runtime_error("invalid const specifier");
				}
			}
		}
	}

	inline void overwrite_vartype(std::vector<std::string>& params, bin2hpp::resource_type_cpp& res){
		const auto itinend   = std::find(   params.begin(), params.end(), options::in);
		const auto ituseaarr = std::find_if(params.begin(), itinend,
		  [](const std::string& s){return begins_with(s, options::vartype);}
		);

		if(ituseaarr==itinend){
			return;
		}

		assert((ituseaarr->size() >= options::vartype.size()) && "impossible since it should contain at least options::vartype");

		const std::string restype = ituseaarr->substr(options::vartype.length());
		res = bin2hpp::array_id::to_res_type_cpp(restype);

		params.erase(ituseaarr);
	}

	inline void overwrite_vartype(std::vector<std::string>& params, bin2hpp::resource_type_java& res){
		const auto itinend   = std::find(   params.begin(), params.end(), options::in);
		const auto ituseaarr = std::find_if(params.begin(), itinend,
		  [](const std::string& s){return begins_with(s, options::vartype);}
		);

		if(ituseaarr==itinend){
			return;
		}

		assert((ituseaarr->size() >= options::vartype.size()) && "impossible since it should contain at least options::vartype");

		const std::string restype = ituseaarr->substr(options::vartype.length());
		res = bin2hpp::array_id::to_res_type_java(restype);

		params.erase(ituseaarr);
	}


	struct parameters_cpp{
		bin2hpp::lang_options_cpp langopt; // fixme--> move to an union?
		std::vector<std::string> in;
		std::vector<std::string> names;
		std::vector<std::string> out;
	};

	struct parameters_c{
		bin2hpp::lang_options_c langopt; // fixme--> move to an union?
		std::vector<std::string> in;
		std::vector<std::string> names;
		std::vector<std::string> out;
	};

	struct parameters_java{
		bin2hpp::lang_options_java langopt; // fixme--> move to an union?
		std::vector<std::string> in;
		std::vector<std::string> names;
		std::vector<std::string> out;
	};


	// throws if configuration is 'bad' --> invalid arguments or unrecognized parameters
	inline parameters_cpp parsecmdlinecpp(std::vector<std::string> params, bin2hpp::lang_options_cpp defaultsettings){
		parameters_cpp toreturn;

		toreturn.langopt = defaultsettings;

		// namespace
		toreturn.langopt._namespace = getnamespace(params);

		bin2hpp::language lang;
		lang._cpprev = toreturn.langopt._rev;

		overwriteconstspec(params, lang, toreturn.langopt.const_arr, toreturn.langopt.const_size);

		// fixme: add param for other options (string)
		overwrite_vartype(params, toreturn.langopt.res);

		toreturn.langopt.usepragma = usepragma(params);

		// inputs
		toreturn.in = getinfiles(params);

		// names
		toreturn.names = getvarnames(toreturn.in, params);

		// outputs
		toreturn.out = getoutfiles(toreturn.in, params);

		return toreturn;
	}

	inline parameters_c parsecmdlinec(std::vector<std::string> params, bin2hpp::lang_options_c defaultsettings){
		parameters_c toreturn;

		toreturn.langopt = defaultsettings;

		// namespace
		toreturn.langopt._namespace = getnamespace(params);

		bin2hpp::language lang;
		lang._crev = toreturn.langopt.rev;

		overwriteconstspec(params, lang, toreturn.langopt.const_arr, toreturn.langopt.const_size);

		toreturn.langopt.usepragma = usepragma(params);

		// inputs
		toreturn.in = getinfiles(params);

		// names
		toreturn.names = getvarnames(toreturn.in, params);

		// outputs
		toreturn.out = getoutfiles(toreturn.in, params);

		return toreturn;
	}

	inline parameters_java parsecmdline_java(std::vector<std::string> params, bin2hpp::lang_options_java defaultsettings){
		parameters_java toreturn;

		toreturn.langopt = defaultsettings;

		// namespace
		toreturn.langopt.class_name = getnamespace(params);

		bin2hpp::language lang;
		lang._javarev = toreturn.langopt.rev;

		// fixme: add param for other options (string)
		overwrite_vartype(params, toreturn.langopt.res);

		// inputs
		toreturn.in = getinfiles(params);

		// names
		toreturn.names = getvarnames(toreturn.in, params);

		// outputs
		toreturn.out = getoutfiles(toreturn.in, params);

		return toreturn;
	}
}
#endif
