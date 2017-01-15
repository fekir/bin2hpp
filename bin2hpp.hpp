#ifndef BIN2HPP_HEADER
#define BIN2HPP_HEADER

#include <random>

#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>      // std::stringstream

#include <iostream>

namespace hexutils{

	constexpr char elems[] = "0123456789ABCDEF";
	inline constexpr std::array<char,2> to_hex(const unsigned char c) noexcept {
		static_assert(((std::numeric_limits<unsigned char>::max() & 0xff) >> 4 )<16, "Impossible");
		static_assert(((std::numeric_limits<unsigned char>::max() & 0x0f)      )<16, "Impossible");
		return {elems[(c & '\xff') >> 4], elems[c & 0x0f]};
	}

}

namespace bin2hpp{

	const std::string comment = "This file has been autogenerated by bin2hpp";

	const std::string defaultnamespace = "resource";

	enum class lang_id{ cpp, c, java };
	enum class cpp_rev{ cpp98, cpp03, cpp11, cpp14, cpp17};
	enum class c_rev{ c89, c99, c11};
	enum class java_rev{j1_3, j1_4, j1_5, j1_6, j1_7, j1_8, j1_9};


	enum class resource_type_cpp{std_arr, c_arr, std_string, c_string};
	enum class resource_type_c{c_arr, c_string};
	enum class resource_type_java{byte_arr, Byte_arr, String, list};

	namespace constid {
		const std::string _enum       = "enum";
		const std::string _const      = "const";
		const std::string _constexpr  = "constexpr";
	}

	namespace array_id {
		// c++
		const std::string _std_arr     = "std::array";
		const std::string _std_string  = "std::string";
		// c and c++
		const std::string _c_arr       = "c_arr";
		const std::string _c_string    = "c_str";
		// java
		const std::string _byte_arr    = "byte[]";
		const std::string _Byte_arr    = "Byte[]";
		const std::string _string      = "String";
		const std::string _list        = "List<Byte>";

		inline resource_type_c to_res_type_c(const std::string& res){
			if(res == _c_arr){
				return resource_type_c::c_arr;
			}
			if(res == _c_string){
				return resource_type_c::c_string;
			}
			throw std::runtime_error("no valid cpp resource type");
		}

		inline resource_type_cpp to_res_type_cpp(const std::string& res){
			if(res == _std_arr){
				return resource_type_cpp::std_arr;
			}
			if(res == _std_string){
				return resource_type_cpp::std_string;
			}
			if(res == _c_arr){
				return resource_type_cpp::c_arr;
			}
			if(res == _c_string){
				return resource_type_cpp::c_string;
			}
			throw std::runtime_error("no valid cpp resource type");
		}

		inline resource_type_java to_res_type_java(const std::string& res){
			if(res == _byte_arr){
				return resource_type_java::byte_arr;
			}
			if(res == _byte_arr){
				return resource_type_java::Byte_arr;
			}
			if(res == _byte_arr){
				return resource_type_java::String;
			}
			if(res == _byte_arr){
				return resource_type_java::list;
			}
			throw std::runtime_error("no valid java resource type");

			const std::string _byte_arr    = "byte[]";
			const std::string _Byte_arr    = "Byte[]";
			const std::string _string      = "String";
			const std::string _list        = "List";
		}
	}

	struct language{
		lang_id id = lang_id::cpp;
		union{
			cpp_rev  _cpprev   = cpp_rev::cpp17;
			c_rev    _crev;
			java_rev _javarev;
		};
	};

	enum class constid_array{ _const, _constexpr};
	enum class constid_size{ _const, _constexpr, _enum};

	inline std::string constid_tostr(constid_array id){
		switch(id){
			case constid_array::_const: return constid::_const;
			case constid_array::_constexpr: return constid::_constexpr;
			default: assert(false);
		}
	}

	inline bool has_constexpxr(const cpp_rev r){
		return r >= cpp_rev::cpp11;
	}

	inline bool has_stdarr(const cpp_rev r){
		return has_constexpxr(r); // both where introduced with c++11
	}

	inline bool has_generics(const java_rev r){
		return r >= java_rev::j1_5;
	}

	struct lang_options_cpp{
		bin2hpp::cpp_rev _rev;
		bin2hpp::resource_type_cpp res;
		bin2hpp::constid_array const_arr;
		bin2hpp::constid_size const_size;
		bool usepragma = false;
		std::string _namespace = defaultnamespace;
		explicit lang_options_cpp(const cpp_rev rev = cpp_rev::cpp17) :
		    _rev(rev),
		    res(has_stdarr(rev) ? resource_type_cpp::std_arr : resource_type_cpp::c_arr),
		    const_arr(has_constexpxr(rev) ? constid_array::_constexpr : constid_array::_const),
		    const_size(has_constexpxr(rev) ? constid_size::_constexpr : constid_size::_const)
		{
		}
	};

	struct lang_options_c{
		bin2hpp::c_rev rev;
		bin2hpp::constid_array const_arr = bin2hpp::constid_array::_const;
		bin2hpp::constid_size const_size = bin2hpp::constid_size::_enum;
		bool usepragma = false;
		std::string _namespace = defaultnamespace;
		explicit lang_options_c(const bin2hpp::c_rev rev_ = bin2hpp::c_rev::c11) : rev(rev_){}
	};

	struct lang_options_java{
		bin2hpp::java_rev rev;
		bin2hpp::resource_type_java res = bin2hpp::resource_type_java::byte_arr;
		std::string _namespace = defaultnamespace;
		explicit lang_options_java(const bin2hpp::java_rev rev_ = bin2hpp::java_rev::j1_9) : rev(rev_){}
	};

	inline std::string constid_tostr(constid_size id){
		switch(id){
			case constid_size::_const: return constid::_const;
			case constid_size::_constexpr: return constid::_constexpr;
			case constid_size::_enum: return constid::_enum;
			default: assert(false);
		}
	}


	// crea sequenza " 0xAB,0xCD,... " ritorna lunghezza dell'array
	// fixme: controllare se servono cast per alcuni warnings
	enum class format{c, java_byte, java_Byte, string};
	inline size_t convertstreamtohexnotation(std::istream& in, std::ostream& out, const format f = format::c){
		size_t totalsize = {};

		std::array<unsigned char, 1024> buffer;
		while(!in.eof()){

			const auto readed = in.read(reinterpret_cast<char*>(&buffer.at(0)), buffer.size()).gcount();
			assert(readed >= 0);
			const auto unsigned_readed = static_cast<std::make_unsigned<decltype(readed)>::type>(readed);
			// fixme: if totalsize >int_max-readed throw error "file is too big" as it can' be saved in an array
			totalsize += unsigned_readed;

			if(in.fail() && !in.eof()){ // something went wrong, but we where not at the end of the file
				throw std::runtime_error("error reading stream");
			}

			// fixme: error checking
			// suppongo legga tutto --> altrimenti exception!
			//if(in.) --> check se qualcosa andato male
			for(auto i = decltype(unsigned_readed){0} ; i != unsigned_readed; ++i){
				auto c = hexutils::to_hex(buffer.at(i));
				if(f == format::c){
					// notation '\xaa' can lead to problems..
					out << "0x" << c[0] << c[1] << ","; // fixme: format should be specified with out param...
				} else if (f == format::java_byte){
					out << "(byte)0x" << c[0] << c[1] << ","; // fixme: format should be specified with out param...
				}
			}
		}
		return totalsize;

	}

	// crea constexpr_id std::array<unsigned char, size> variablename = { "0xAB", "0xCD" };
	// tutto tabbed di 1\t
	inline void create_std_array(std::istream& in, const std::string& variablename, constid_array c_a, std::ostream& out){
		std::stringstream tmp;
		const auto size = convertstreamtohexnotation(in, tmp);
		out << constid_tostr(c_a) << " std::array<unsigned char," << size << "> " << variablename << " = {\n";
		out << tmp.rdbuf() << "\n";
		out << "};\n";
	}

	inline void create_std_string(std::istream& in, const std::string& variablename, constid_array c_a, std::ostream& out){
		out << "const std::string " << variablename << "\"";
		size_t totalsize = {};

		std::string tmp;
		while(std::getline (in,tmp)){
			out << tmp << "\n";

		}
		// fixme: ad error checking!
		out << "\"";
	}


	// crea const_id size_t variablename_size = 42;
	//      const_id unsigned char[42] = { "0xAB", "0xCD" };
	// tutto tabbed di 1\t
	inline void create_c_array(std::istream& in, const std::string& variablename, constid_array c_a, constid_size c_s, bool iscpp, std::ostream& out){

		assert(iscpp || c_a != constid_array::_constexpr && "c does not support constexpr");
		assert(iscpp || c_s != constid_size::_constexpr  && "c does not support constexpr");

		std::stringstream tmp;
		const auto size = convertstreamtohexnotation(in, tmp);
		if(c_s==constid_size::_enum){
			out << constid_tostr(c_s) << (iscpp ? " : std::size_t " : " ") << "{" << variablename << "_size = " << size << "};\n";
		} else {
			out << (iscpp ? "" : "static ") << constid_tostr(c_s) << (iscpp ? " std::" : " ") << "size_t " << variablename << "_size = " << size << ";\n";
		}
		out << (iscpp ? "" : "static ") << constid_tostr(c_a) << " unsigned char " << variablename << "[" << size << "] " <<  "= {\n";
		out << tmp.rdbuf() << "\n";
		out << "};\n";
	}

	inline void create_byte_array(std::istream& in, const std::string& variablename, std::ostream& out){
		out << "public static final byte[] " << variablename << " = { ";
		convertstreamtohexnotation(in, out, format::java_byte);
		out << "};\n";
	}

	inline void create_file(std::istream& in, const lang_options_cpp& op, const std::string& variablename, std::ostream& out) {

		if(op.usepragma){
			out << "#pragma once\n\n";
		} else {
			// fixme --> uni as external dependency to unittest
			std::random_device rd;     // only used once to initialise (seed) engine
			std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
			std::uniform_int_distribution<int> uni(0,std::numeric_limits<int>::max()); // guaranteed unbiased
			auto random_integer = uni(rng);
			const std::string header = "HEADER_"+variablename+"_" +std::to_string(random_integer);
			out << "#ifndef " << header << "\n";
			out << "#define " << header << "\n\n";
		}
		out << "// " << comment << "\n\n";

		switch (op.res) {
			case bin2hpp::resource_type_cpp::std_arr:
				out << "#include <array>\n\n";
				break;
			case bin2hpp::resource_type_cpp::std_string:
				out << "#include <string>\n\n";
				break;
			case bin2hpp::resource_type_cpp::c_arr:
			case bin2hpp::resource_type_cpp::c_string:
				out << "#include <cstddef>\n\n";
				break;
			default:
				assert(false);
				break;
		}

		if(!op._namespace.empty()){
			out << "namespace " << op._namespace << " {\n\n";
		}

		switch (op.res) {
			case bin2hpp::resource_type_cpp::std_arr:
				create_std_array(in, variablename, op.const_arr, out);
				break;
			case bin2hpp::resource_type_cpp::std_string:
				create_std_string(in, variablename, op.const_arr, out);
				break;
			case bin2hpp::resource_type_cpp::c_arr:
				create_c_array(in, variablename, op.const_arr, op.const_size, true, out);
				break;
			case bin2hpp::resource_type_cpp::c_string:
				create_c_array(in, variablename, op.const_arr, op.const_size, true, out);
				break;
			default:
				assert(false);
				break;
		}

		// close namespace
		if(!op._namespace.empty()){
			out << "\n}\n\n";
		}

		// close header guard
		if(!op.usepragma){
			out << "\n#endif\n";
		}

	}

	inline void create_file(std::istream& in, const lang_options_c& op, const std::string& variablename, std::ostream& out) {

		if(op.usepragma){
			out << "#pragma once\n\n";
		} else {
			// fixme --> uni as external dependency to unittest
			std::random_device rd;     // only used once to initialise (seed) engine
			std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
			std::uniform_int_distribution<int> uni(0,std::numeric_limits<int>::max()); // guaranteed unbiased
			auto random_integer = uni(rng);
			const std::string header = "HEADER_"+variablename+"_" +std::to_string(random_integer);
			out << "#ifndef " << header << "\n";
			out << "#define " << header << "\n\n";
		}
		if(op.rev == bin2hpp::c_rev::c89){
			out << "/* " << comment << "*/\n\n";
		} else {
			out << "// " << comment << "\n\n";
		}


		if(op.const_size != constid_size::_enum){
			out << "#include <stddef.h>\n\n";
		}

		create_c_array(in, op._namespace + "_" + variablename, constid_array::_const, op.const_size, false, out);

		// close header guard
		if(!op.usepragma){
			out << "\n#endif\n";
		}

	}

	inline void create_file(std::istream& in, const lang_options_java& op, const std::string& variablename, const std::string& package, std::ostream& out) {
		if(!package.empty()){
			out << "package " << package << ";\n";
		}
		out << "// " << comment << "\n\n";
		out << "class " << op._namespace << "{\n";
		create_byte_array(in, variablename, out);
		out << "}\n\n";

	}

}

#endif
