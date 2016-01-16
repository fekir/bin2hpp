#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

//bin2hpp -ns=res1                               -in helloworld -out ${OUT_DIR}/res_stdarray.hpp
#include "res_stdarray.hpp"
#include "res_stdarray.hpp"
//bin2hpp -ns=res2 -pragma                       -in helloworld -out ${OUT_DIR}/res_stdarray_pragma.hpp
#include "res_stdarray_pragma.hpp"
#include "res_stdarray_pragma.hpp"
//bin2hpp -ns=res3 -const=const                  -in helloworld -out ${OUT_DIR}/res_stdarray_const.hpp
#include "res_stdarray_const.hpp"
#include "res_stdarray_const.hpp"
//bin2hpp -ns=res4 -stdarr=false                 -in helloworld -out ${OUT_DIR}/res_carray.hpp
#include "res_carray.hpp"
#include "res_carray.hpp"
//bin2hpp -ns=res5 -stdarr=false -constsize=enum -in helloworld -out ${OUT_DIR}/res_carray_enum.hpp
#include "res_carray_enum.hpp"
#include "res_carray_enum.hpp"
//bin2hpp -ns=res6 -stdarr=false -const=const    -in helloworld -out ${OUT_DIR}/res_carray_const1.hpp
#include "res_carray_const1.hpp"
#include "res_carray_const1.hpp"

const std::string helloworld = "Hello World!\n\n"; // 2nd ewline is EOF

template <class T1, class T2> 
void compare(const T1& t1, const T2& t2){
	REQUIRE(t1.size() == t2.size());
	for(size_t i = 0; i != t1.size(); ++i){
		REQUIRE(t1.at(i) == static_cast<const char>(t2.at(i)));
	}
}

TEST_CASE("stdarray", "[]"){
	compare(helloworld, res1::helloworld);
}

TEST_CASE("stdarray2", "[]"){
	REQUIRE(res1::helloworld == res2::helloworld);
}

TEST_CASE("stdarray3", "[]"){
	REQUIRE(res1::helloworld == res3::helloworld);
}


