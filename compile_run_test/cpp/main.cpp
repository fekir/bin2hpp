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
#include <numeric>

const std::string helloworld = "Hello World!\n\n"; // 2nd ewline is EOF
constexpr size_t helloworldlength = 14;

constexpr size_t binarybloblength = std::numeric_limits<unsigned char>::max()*2;

// avaiable in c++17
template <class T>
std::size_t mysize(const T& t){
	return t.size();
}

template <class T, std::size_t N>
constexpr std::size_t mysize(const T (&)[N]) noexcept {
	return N;
}

template< size_t s, class T>
constexpr bool is_stdarray(const T&){
	using value_type_with_qualifier = T;
	using value_type = typename std::remove_cv<value_type_with_qualifier>::type;
	return std::is_same<value_type, std::array<unsigned char, s>>::value;
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

inline std::vector<unsigned char> create_binary_blob(){
	std::vector<unsigned char> tmp(std::numeric_limits<unsigned char>::max()*2);
	std::iota(tmp.begin(), tmp.end(), 0);
	return tmp;
}


const auto binary_blob = create_binary_blob();

TEST_CASE("stdarray1", "[cpp]"){
	static_assert(is_stdarray<binarybloblength>(res1::bin2hppbinarydata_dat), "retval must be std::array");
	compare(binary_blob, res1::bin2hppbinarydata_dat);
}

TEST_CASE("stdarray2", "[cpp]"){
	static_assert(is_stdarray<binarybloblength>(res2::bin2hppbinarydata_dat), "retval must be std::array");
	REQUIRE(res1::bin2hppbinarydata_dat == res2::bin2hppbinarydata_dat);
}

TEST_CASE("stdarray3", "[cpp]"){
	static_assert(is_stdarray<binarybloblength>(res3::bin2hppbinarydata_dat), "retval must be std::array");
	REQUIRE(res1::bin2hppbinarydata_dat == res3::bin2hppbinarydata_dat);
}

TEST_CASE("carray1_cpp", "[cpp]"){
	static_assert(is_carr(res4::bin2hppbinarydata_dat), "retval must be unsigned char*");
	static_assert(!is_stdarray<binarybloblength>(res4::bin2hppbinarydata_dat), "retval must not be std::array");
	compare(binary_blob, res4::bin2hppbinarydata_dat);
}

TEST_CASE("carray1", "[c]"){
	static_assert(is_carr(res1_bin2hppbinarydata_dat), "retval must be unsigned char*");
	static_assert(!is_stdarray<binarybloblength>(res1_bin2hppbinarydata_dat), "retval must not be std::array");
	compare(binary_blob, res1_bin2hppbinarydata_dat);
}
TEST_CASE("carray2", "[c]"){
	static_assert(is_carr(res2_bin2hppbinarydata_dat), "retval must be unsigned char*");
	static_assert(!is_stdarray<binarybloblength>(res2_bin2hppbinarydata_dat), "retval must not be std::array");
	compare(res1_bin2hppbinarydata_dat, res2_bin2hppbinarydata_dat);
}
TEST_CASE("carray3", "[c]"){
	static_assert(is_carr(res3_bin2hppbinarydata_dat), "retval must be unsigned char*");
	static_assert(!is_stdarray<binarybloblength>(res3_bin2hppbinarydata_dat), "retval must not be std::array");
	compare(res1_bin2hppbinarydata_dat, res3_bin2hppbinarydata_dat);
}
