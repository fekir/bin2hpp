cmake_minimum_required(VERSION 3.2)

project(bin2hpp_test_compile_cpp CXX)

include_directories(${OUT_DIR_CPP})
include_directories(${OUT_DIR_C})

add_executable(${PROJECT_NAME} main.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

##########################################################
## Compile Test

add_dependencies(${PROJECT_NAME} ${GENERATE_CPP_FILES} ${GENERATE_C_FILES})

