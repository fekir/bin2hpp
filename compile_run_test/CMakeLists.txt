

# Settings for generating include files
set(OUT_DIR_CPP "${CMAKE_CURRENT_BINARY_DIR}")
set(OUT_DIR_C "${CMAKE_CURRENT_BINARY_DIR}")


set(GENERATE_CPP_FILES generateCPPfiles)
add_custom_target(${GENERATE_CPP_FILES}
	DEPENDS ${OUT_DIR_CPP}/res_stdarray.hpp
)
set(GENERATE_C_FILES generateCfiles)
add_custom_target(${GENERATE_C_FILES}
	DEPENDS ${OUT_DIR_C}/res_carray.h
)

set(OUT_CPP_FILES 
	${OUT_DIR_CPP}/res_stdarray.hpp 
	${OUT_DIR_CPP}/res_stdarray_pragma.hpp 
	${OUT_DIR_CPP}/res_stdarray_const.hpp 
	${OUT_DIR_CPP}/res_carray.hpp 
	${OUT_DIR_CPP}/res_carray_enum.hpp 
	${OUT_DIR_CPP}/res_carray_const1.hpp
)

set(helloworldfile "${CMAKE_CURRENT_SOURCE_DIR}/../extern/data/helloworld")
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

set(OUT_C_FILES 
	${OUT_DIR_C}/res_carray.h 
	${OUT_DIR_C}/res_carray_enum.h 
	${OUT_DIR_C}/res_carray_const1.h
)
add_custom_command(
	OUTPUT ${OUT_DIR_C}/res_carray.h
	COMMAND bin2hpp -std=c -ns=res1                 -in ${helloworldfile} -out ${OUT_DIR_C}/res_carray.h
	COMMAND bin2hpp -std=c -ns=res2 -constsize=enum -in ${helloworldfile} -out ${OUT_DIR_C}/res_carray_enum.h
	COMMAND bin2hpp -std=c -ns=res3 -const=const    -in ${helloworldfile} -out ${OUT_DIR_C}/res_carray_const1.h
	COMMAND bin2hpp -std=c -ns=res4 -pragma         -in ${helloworldfile} -out ${OUT_DIR_C}/res_carray_pragma.h
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_subdirectory(CPP)
add_subdirectory(C)

