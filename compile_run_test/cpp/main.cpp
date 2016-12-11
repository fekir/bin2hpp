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
#include <type_traits>

const std::string helloworld = "Hello World!\n\n"; // 2nd ewline is EOF
constexpr size_t lenght = 14;

// avaiable in c++17
template <class T>
std::size_t mysize(const T& t){
	return t.size();
}

template <class T, std::size_t N>
constexpr std::size_t mysize(const T (&)[N]) noexcept {
	return N;
}

template<class T>
constexpr bool is_stdarray_s14(const T&){
	using value_type_with_qualifier = T;
	using value_type = typename std::remove_cv<value_type_with_qualifier>::type;
	return std::is_same<value_type, std::array<unsigned char, 14>>::value;
}

template<class T>
constexpr bool is_stdstrin(const T&){
	using value_type_with_qualifier = T;
	using value_type = typename std::remove_cv<value_type_with_qualifier>::type;
	return std::is_same<value_type, std::string>::value;
}

template<class T>
constexpr bool is_carr(const T*){
	using value_type_with_qualifier = T;
	using value_type = typename std::remove_cv<value_type_with_qualifier>::type;
	return std::is_same<value_type, unsigned char>::value;
}

template<class T>
constexpr bool is_cstr(const T*){
	using value_type_with_qualifier = T;
	using value_type = typename std::remove_cv<value_type_with_qualifier>::type;
	return std::is_same<value_type, char>::value;
}

template <class T1, class T2>
void compare(const T1& t1, const T2& t2){
	REQUIRE(mysize(t1) == mysize(t2));
	for(size_t i = 0; i != mysize(t1); ++i){
		REQUIRE(static_cast<const char>(t1[i]) == static_cast<const char>(t2[i]));
	}
}

TEST_CASE("stdarray1", "[cpp]"){
	static_assert(is_stdarray_s14(res1::helloworld), "retval must be std::array");
	compare(helloworld, res1::helloworld);
}

TEST_CASE("stdarray2", "[cpp]"){
	static_assert(is_stdarray_s14(res2::helloworld), "retval must be std::array");
	REQUIRE(res1::helloworld == res2::helloworld);
}

TEST_CASE("stdarray3", "[cpp]"){
	static_assert(is_stdarray_s14(res3::helloworld), "retval must be std::array");
	REQUIRE(res1::helloworld == res3::helloworld);
}

TEST_CASE("carray1_cpp", "[cpp]"){
	static_assert(is_carr(res4::helloworld), "retval must be unsigned char*");
	static_assert(!is_stdarray_s14(res4::helloworld), "retval must not be std::array");
	compare(helloworld, res4::helloworld);
}

TEST_CASE("carray1", "[c]"){
	static_assert(is_carr(res1_helloworld), "retval must be unsigned char*");
	static_assert(!is_stdarray_s14(res1_helloworld), "retval must not be std::array");
	compare(helloworld, res1_helloworld);
}
TEST_CASE("carray2", "[c]"){
	static_assert(is_carr(res2_helloworld), "retval must be unsigned char*");
	static_assert(!is_stdarray_s14(res2_helloworld), "retval must not be std::array");
	compare(helloworld, res2_helloworld);
}
TEST_CASE("carray3", "[c]"){
	static_assert(is_carr(res3_helloworld), "retval must be unsigned char*");
	static_assert(!is_stdarray_s14(res3_helloworld), "retval must not be std::array");
	compare(helloworld, res3_helloworld);
}
