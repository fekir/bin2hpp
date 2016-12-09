cmake_minimum_required(VERSION 3.2)

project(bin2hppTestCompileC C)

include_directories(${OUT_DIR_CPP})
include_directories(${OUT_DIR_C})

add_executable(${PROJECT_NAME} main.c
)

##########################################################
## Compile Test

add_dependencies(${PROJECT_NAME} ${GENERATE_C_FILES})

