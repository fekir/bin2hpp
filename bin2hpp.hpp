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
	enum class cpprev{ cpp98, cpp03, cpp11, cpp14, cpp17};
	enum class crev{ c89, c99, c11};
	enum class javarev{j1_3, j1_4, j1_5, j1_6, j1_7, j1_8, j1_9};


    enum class resource_type_cpp{std_arr, c_arr, std_string, c_string};
    enum class resource_type_c{c_arr, c_string};
    enum class resource_type_java{byte_arr, Byte_arr, obj_arr, jstring};

	namespace constid {
		const std::string _enum       = "enum";
		const std::string _const      = "const";
		const std::string _constexpr  = "constexpr";
	}

	struct language{
		lang_id id = lang_id::cpp;
		union{
			cpprev  _cpprev   = cpprev::cpp17;
			crev    _crev;
			javarev _javarev;
		};
	};

	enum class constid_array{ _const, _constexpr};
	enum class constid_size{ _const, _constexpr, _enum};

	inline std::string getID(constid_array id){
		switch(id){
			case constid_array::_const: return constid::_const;
			case constid_array::_constexpr: return constid::_constexpr;
			default: assert(false);
		}
	}

	inline bool has_constexpxr(const cpprev r){
		return (r != cpprev::cpp98) && (r != cpprev::cpp03);
	}

	inline bool has_stdarr(const cpprev r){
		return has_constexpxr(r); // both where introduced with c++11
	}

	struct langoptionscpp{
		bin2hpp::cpprev _rev;
		bin2hpp::resource_type_cpp res;
		bin2hpp::constid_array const_arr;
		bin2hpp::constid_size const_size;
		bool usepragma = false;
		std::string _namespace = defaultnamespace;
		langoptionscpp(const cpprev rev = cpprev::cpp17) :
		    _rev(rev),
		    res(has_stdarr(rev) ? resource_type_cpp::std_arr : resource_type_cpp::c_arr),
		    const_arr(has_constexpxr(rev) ? constid_array::_constexpr : constid_array::_const),
		    const_size(has_constexpxr(rev) ? constid_size::_constexpr : constid_size::_const)
		{
		}
	};

	struct langoptionsc{
		bin2hpp::crev rev = bin2hpp::crev::c11;
		bin2hpp::constid_array const_arr = bin2hpp::constid_array::_const;
		bin2hpp::constid_size const_size = bin2hpp::constid_size::_enum;
		bool usepragma = false;
		std::string _namespace = defaultnamespace;
	};

	inline std::string getID(constid_size id){
		switch(id){
			case constid_size::_const: return constid::_const;
			case constid_size::_constexpr: return constid::_constexpr;
			case constid_size::_enum: return constid::_enum;
			default: assert(false);
		}
	}


	// crea sequenza " 0xAB,0xCD,... " ritorna lunghezza dell'array
	// fixme: controllare se servono cast per alcuni warnings
	inline size_t convertstreamtohexnotation(std::istream& in, std::ostream& out){
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
				out << "'\\x" << c[0] << c[1] << "',";
			}
            int a = 1;
		}
		return totalsize;

	}

	// crea constexpr_id std::array<unsigned char, size> variablename = { "0xAB", "0xCD" };
	// tutto tabbed di 1\t
	inline void create_std_array(std::istream& in, const std::string& variablename, constid_array c_a, std::ostream& out){
		std::stringstream tmp;
		const auto size = convertstreamtohexnotation(in, tmp);
		out << getID(c_a) << " std::array<unsigned char," << size << "> " << variablename << " = {\n";
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
			out << getID(c_s) << (iscpp ? " : std::size_t " : " ") << "{" << variablename << "_size = " << size << "};\n";
		} else {
			out << (iscpp ? "" : "static ") << getID(c_s) << (iscpp ? " std::" : " ") << "size_t " << variablename << "_size = " << size << ";\n";
		}
		out << (iscpp ? "" : "static ") << getID(c_a) << " unsigned char " << variablename << "[" << size << "] " <<  "= {\n";
		out << tmp.rdbuf() << "\n";
		out << "};\n";
	}

	inline void create_file(std::istream& in, const langoptionscpp& op, const std::string& variablename, std::ostream& out) {

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

	inline void create_file(std::istream& in, const langoptionsc& op, const std::string& variablename, std::ostream& out) {

		if(op.usepragma){
			out << "#pragma once\n\n";
		} else {
            static int ii = 0;
            const std::string header = "HEADER_"+variablename+"_"+std::to_string(ii++); // fixme: add timestamp and all uppercase (like vs...)
			out << "#ifndef " << header << "\n";
			out << "#define " << header << "\n\n";
		}
		if(op.rev == bin2hpp::crev::c89){
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

}

#endif
