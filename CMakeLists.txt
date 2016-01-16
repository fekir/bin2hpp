cmake_minimum_required(VERSION 3.2)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(catch REQUIRED)

project(bin2hpp CXX)
set (PROJ1_VERSION_MAJOR 0)
set (PROJ1_VERSION_MINOR 7)

##########################################################
# Program Options/settings                               #
##########################################################
set(HEADER_FILES
	bin2hpp.hpp
	params.hpp
)


set(SOURCE_FILES
	bin2hpp.cpp
)

add_executable(${PROJECT_NAME} main.cpp
	${HEADER_FILES} ${SOURCE_FILES}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

##########################################################
# Test settings
#if ("${CATCH_INCLUDE_DIR}" STREQUAL "")
#	add_subdirectory(extern/catch)
#endif()
#include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
enable_testing(true)

set(TEST_FILES test/maintest.cpp
		test/testdata.cpp
		test/testparams.cpp
		test/testhelp.cpp
		test/testfiles.cpp)

add_executable(${PROJECT_NAME}Test
	${HEADER_FILES} ${SOURCE_FILES} ${TEST_FILES}
)
#add_dependencies(${PROJECT_NAME}Test catch)
add_dependencies(${PROJECT_NAME}Test ${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME}Test PROPERTY CXX_STANDARD 14)
add_test(test1 ${PROJECT_NAME}Test)
# Copy data used for testing
#file(COPY "extern/data/" DESTINATION "/tmp/testfilediggerdir")


############################################################
# create files for create_run
set(CMAKE_INCLUDE_CURRENT_DIR on)

#set(OUT_DIR_CPP "${CMAKE_CURRENT_SOURCE_DIR}/compile_run_test/CPP")
#set(OUT_DIR_C "${CMAKE_CURRENT_SOURCE_DIR}/compile_run_test/C")
set(OUT_DIR_CPP "${CMAKE_CURRENT_BINARY_DIR}")
set(OUT_DIR_C "${CMAKE_CURRENT_BINARY_DIR}")
message(${OUT_DIR_CPP})
message(${CMAKE_CURRENT_BINARY_DIR})


set(GENERATE_CPP_FILES generateCPPfiles)
add_custom_target(${GENERATE_CPP_FILES}
 	DEPENDS ${OUT_DIR_CPP}/res_stdarray.hpp
)
set(GENERATE_C_FILES generateCfiles)
add_custom_target(${GENERATE_C_FILES}
 	DEPENDS ${OUT_DIR_C}/res_carray.h
)

set(OUT_CPP_FILES ${OUT_DIR_CPP}/res_stdarray.hpp ${OUT_DIR_CPP}/res_stdarray_pragma.hpp ${OUT_DIR_CPP}/res_stdarray_const.hpp ${OUT_DIR_CPP}/res_carray.hpp ${OUT_DIR_CPP}/res_carray_enum.hpp ${OUT_DIR_CPP}/res_carray_const1.hpp)

set(helloworldfile "${CMAKE_CURRENT_SOURCE_DIR}/extern/data/helloworld")
message(${helloworldfile})
add_custom_command(
	OUTPUT ${OUT_DIR_CPP}/res_stdarray.hpp
    COMMAND bin2hpp -ns=res1                               -in ${helloworldfile} -out ${OUT_DIR_CPP}/res_stdarray.hpp
	COMMAND bin2hpp -ns=res2 -pragma                       -in ${helloworldfile} -out ${OUT_DIR_CPP}/res_stdarray_pragma.hpp
	COMMAND bin2hpp -ns=res3 -const=const                  -in ${helloworldfile} -out ${OUT_DIR_CPP}/res_stdarray_const.hpp
	COMMAND bin2hpp -ns=res4 -stdarr=false                 -in ${helloworldfile} -out ${OUT_DIR_CPP}/res_carray.hpp
	COMMAND bin2hpp -ns=res5 -stdarr=false -constsize=enum -in ${helloworldfile} -out ${OUT_DIR_CPP}/res_carray_enum.hpp
	COMMAND bin2hpp -ns=res6 -stdarr=false -const=const    -in ${helloworldfile} -out ${OUT_DIR_CPP}/res_carray_const1.hpp
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

set(OUT_C_FILES ${OUT_DIR_C}/res_carray.h ${OUT_DIR_C}/res_carray_enum.h ${OUT_DIR_C}/res_carray_const1.h)
add_custom_command(
#    TARGET ${PROJECT_NAME}TestCompileC PRE_BUILD
	OUTPUT ${OUT_DIR_C}/res_carray.h
	COMMAND bin2hpp -std=c -ns=res1                 -in ${helloworldfile} -out ${OUT_DIR_C}/res_carray.h
	COMMAND bin2hpp -std=c -ns=res2 -constsize=enum -in ${helloworldfile} -out ${OUT_DIR_C}/res_carray_enum.h
	COMMAND bin2hpp -std=c -ns=res3 -const=const    -in ${helloworldfile} -out ${OUT_DIR_C}/res_carray_const1.h
	COMMAND bin2hpp -std=c -ns=res4 -pragma         -in ${helloworldfile} -out ${OUT_DIR_C}/res_carray_pragma.h
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

##########################################################
## Compile Test
add_executable(${PROJECT_NAME}TestCompileCPP 
	compile_run_test/CPP/main.cpp
)
#add_dependencies(${PROJECT_NAME}TestCompileCPP catch)
add_dependencies(${PROJECT_NAME}TestCompileCPP ${GENERATE_CPP_FILES})
set_property(TARGET ${PROJECT_NAME}TestCompileCPP PROPERTY CXX_STANDARD 14)

# create files for verifyng that generated data is valid C/CPP/Java code



#add_executable(${PROJECT_NAME}TestCompileC
#	compile_run_test/C/main.c
#)

#add_dependencies(${PROJECT_NAME}TestCompileC ${GENERATE_C_FILES})
#set_property(TARGET ${PROJECT_NAME}TestCompileC PROPERTY C_STANDARD 11)


