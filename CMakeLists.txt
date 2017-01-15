cmake_minimum_required(VERSION 3.2)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(catch REQUIRED)
include_directories(SYSTEM ${CATCH_INCLUDE_DIRS})

project(bin2hpp CXX)
set (PROJ1_VERSION_MAJOR 0)
set (PROJ1_VERSION_MINOR 8)

##########################################################
# Program Options/settings                               #
##########################################################
set(SOURCE_FILES
	bin2hpp.cpp
	bin2hpp.hpp
	params.hpp
)

add_executable(${PROJECT_NAME} main.cpp
	${SOURCE_FILES}
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
	test/testfiles.cpp
)

add_executable(${PROJECT_NAME}_test
	${HEADER_FILES} ${SOURCE_FILES} ${TEST_FILES}
)
#add_dependencies(${PROJECT_NAME}Test catch)
add_dependencies(${PROJECT_NAME}_test ${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME}_test PROPERTY CXX_STANDARD 14)
add_test(test1 ${PROJECT_NAME}Test)
# Copy data used for testing
#file(COPY "extern/data/" DESTINATION "/tmp/testfilediggerdir")

add_subdirectory(compile_run_test)

