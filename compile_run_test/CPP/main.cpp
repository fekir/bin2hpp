#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

// include twice to detect possible errors with headers or const values


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


//bin2hpp -ns=res4 -stdarr=false                 -in helloworld -out ${OUT_DIR}/res_carray.hpp
#include "res_carray.h"
#include "res_carray.h"
//bin2hpp -ns=res5 -stdarr=false -constsize=enum -in helloworld -out ${OUT_DIR}/res_carray_enum.hpp
#include "res_carray_enum.h"
#include "res_carray_enum.h"
//bin2hpp -ns=res6 -stdarr=false -const=const    -in helloworld -out ${OUT_DIR}/res_carray_const1.hpp
#include "res_carray_const1.h"
#include "res_carray_const1.h"


#include <string>

const std::string helloworld = "Hello World!\n\n"; // 2nd ewline is EOF

// avaiable in c++17
template <class T>
std::size_t mysize(const T& t){
	return t.size();
}

template <class T, std::size_t N>
constexpr std::size_t mysize(const T (&)[N]) noexcept {
	return N;
}

template <class T1, class T2>
void compare(const T1& t1, const T2& t2){
	REQUIRE(mysize(t1) == mysize(t2));
	for(size_t i = 0; i != mysize(t1); ++i){
		REQUIRE(static_cast<const char>(t1[i]) == static_cast<const char>(t2[i]));
	}
}

TEST_CASE("stdarray1", "[cpp]"){
	compare(helloworld, res1::helloworld);
}

TEST_CASE("stdarray2", "[cpp]"){
	REQUIRE(res1::helloworld == res2::helloworld);
}

TEST_CASE("stdarray3", "[cpp]"){
	REQUIRE(res1::helloworld == res3::helloworld);
}

TEST_CASE("carray1_cpp", "[cpp]"){
	compare(helloworld, res4::helloworld);
}

TEST_CASE("carray1", "[c]"){
	compare(helloworld, res1_helloworld);
}
TEST_CASE("carray2", "[c]"){
	compare(helloworld, res2_helloworld);
}
TEST_CASE("carray3", "[c]"){
	compare(helloworld, res3_helloworld);
}
