cmake_minimum_required(VERSION 3.2)

find_package(Java REQUIRED)
include(UseJava)

project(bin2hpp_test_compile_java CXX)

set(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.8" "-target" "1.8")

#find_jar(JUNIT_JAR junit4)
#set(CMAKE_JAVA_INCLUDE_PATH "${CMAKE_JAVA_INCLUDE_PATH}:${JUNIT_JAR}")

add_jar(${PROJECT_NAME}
	Main.java ${OUT_JAVA_FILES}
	ENTRY_POINT Main
	OUTPUT_NAME Bin2hppTestCompileJava
#	INCLUDE_JARS ${JUNIT_JAR}
)

add_dependencies(${PROJECT_NAME} ${GENERATE_JAVA_FILES})

