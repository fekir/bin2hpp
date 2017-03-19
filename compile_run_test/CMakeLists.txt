
# Settings for generating include files
set(OUT_DIR_CPP "${CMAKE_CURRENT_BINARY_DIR}")
set(OUT_DIR_C "${CMAKE_CURRENT_BINARY_DIR}")
set(OUT_DIR_JAVA "${CMAKE_CURRENT_BINARY_DIR}")


set(GENERATE_CPP_FILES generateCPPfiles)
add_custom_target(${GENERATE_CPP_FILES}
	DEPENDS ${OUT_DIR_CPP}/res_stdarray.hpp
)
set(GENERATE_C_FILES generateCfiles)
add_custom_target(${GENERATE_C_FILES}
	DEPENDS ${OUT_DIR_C}/res_carray.h
)
set(GENERATE_JAVA_FILES generate_java_files)
add_custom_target(${GENERATE_JAVA_FILES}
	DEPENDS ${OUT_DIR_JAVA}/res_array.java
)

set(OUT_CPP_FILES
	${OUT_DIR_CPP}/res_stdarray.hpp
	${OUT_DIR_CPP}/res_stdarray_pragma.hpp
	${OUT_DIR_CPP}/res_stdarray_const.hpp
	${OUT_DIR_CPP}/res_carray.hpp
	${OUT_DIR_CPP}/res_carray_enum.hpp
	${OUT_DIR_CPP}/res_carray_const1.hpp
	${OUT_DIR_CPP}/res_stdstring.hpp
)

set(helloworldfile "${CMAKE_CURRENT_SOURCE_DIR}/../extern/data/helloworld.txt")
set(binaryblobfile "${CMAKE_CURRENT_SOURCE_DIR}/../extern/data/bin2hppbinarydata.dat")
add_custom_command(
	OUTPUT ${OUT_CPP_FILES}
	COMMAND bin2hpp -ns=res1                                -in ${binaryblobfile} -out ${OUT_DIR_CPP}/res_stdarray.hpp
	COMMAND bin2hpp -ns=res2 -pragma                        -in ${binaryblobfile} -out ${OUT_DIR_CPP}/res_stdarray_pragma.hpp
	COMMAND bin2hpp -ns=res3 -const=const                   -in ${binaryblobfile} -out ${OUT_DIR_CPP}/res_stdarray_const.hpp
	COMMAND bin2hpp -ns=res4 -vartype=c_arr                 -in ${binaryblobfile} -out ${OUT_DIR_CPP}/res_carray.hpp
	COMMAND bin2hpp -ns=res5 -vartype=c_arr -constsize=enum -in ${binaryblobfile} -out ${OUT_DIR_CPP}/res_carray_enum.hpp
	COMMAND bin2hpp -ns=res6 -vartype=c_arr -const=const    -in ${binaryblobfile} -out ${OUT_DIR_CPP}/res_carray_const1.hpp
	COMMAND bin2hpp -ns=res7 -vartype=std::string           -in ${helloworldfile} -out ${OUT_DIR_CPP}/res_stdstring.hpp
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	DEPENDS ${helloworldfile} ${binaryblobfile} bin2hpp
)

set(OUT_C_FILES
	${OUT_DIR_C}/res_carray.h
	${OUT_DIR_C}/res_carray_enum.h
	${OUT_DIR_C}/res_carray_const1.h
	${OUT_DIR_C}/res_carray_pragma.h
	${OUT_DIR_C}/res_c_str.hpp
)
add_custom_command(
	OUTPUT ${OUT_C_FILES}
	COMMAND bin2hpp -std=c -ns=res1                 -in ${binaryblobfile} -out ${OUT_DIR_C}/res_carray.h
	COMMAND bin2hpp -std=c -ns=res2 -constsize=enum -in ${binaryblobfile} -out ${OUT_DIR_C}/res_carray_enum.h
	COMMAND bin2hpp -std=c -ns=res3 -const=const    -in ${binaryblobfile} -out ${OUT_DIR_C}/res_carray_const1.h
	COMMAND bin2hpp -std=c -ns=res4 -pragma         -in ${binaryblobfile} -out ${OUT_DIR_C}/res_carray_pragma.h
	COMMAND bin2hpp -std=c -ns=res5 -vartype=c_str  -in ${binaryblobfile} -out ${OUT_DIR_C}/res_c_str.hpp
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	DEPENDS ${helloworldfile} ${binaryblobfile} bin2hpp
)

set(OUT_JAVA_FILES
	${OUT_DIR_JAVA}/res_array.java
)
add_custom_command(
	OUTPUT ${OUT_DIR_JAVA}
	COMMAND bin2hpp -std=java -ns=res1                 -in ${helloworldfile} -out ${OUT_DIR_JAVA}/res_array.java
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	DEPENDS ${helloworldfile} ${binaryblobfile} bin2hpp
)

add_subdirectory(cpp)
add_subdirectory(c)
add_subdirectory(java)

