project(PotreeConverter)

set(RAPIDJSON_INCLUDE_DIR lib/rapidjson/include)
set(ARGUMENTS_INCLUDE_DIR lib/arguments)
set(CMAKE_VERBOSE_MAKEFILE on)
set(BOOST_EMSCRIPTEN_INCLUDE_DIR $ENV{BOOST_PATH}/dist/emscripten/include)
set(BOOST_EMSCRIPTEN_LIB_DIR $ENV{BOOST_PATH}/dist/emscripten/lib)
set(BOOST_LINK_FLAGS "-lboost_system -lboost_filesystem")
set(PRE_JS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/resources/prepare-fs.js)
set(CMAKE_STATIC_LIBRARY_SUFFIX ".bc")


file(GLOB_RECURSE files src/*.cpp include/*.h include/*.hpp )
file(GLOB_RECURSE lib_rapidjson_files ${RAPIDJSON_INCLUDE_DIR}/* )
file(GLOB_RECURSE lib_argument_files ${ARGUMENTS_INCLUDE_DIR}/* )

include_directories(include ${LASZIP_INCLUDE_DIRS})
include_directories(include ${LIBZIP_INCLUDE_DIR})
include_directories(include ${RAPIDJSON_INCLUDE_DIR})
include_directories(include ${ARGUMENTS_INCLUDE_DIR})
include_directories(include ${BOOST_EMSCRIPTEN_INCLUDE_DIR})
include_directories(include ${BOOST_EMSCRIPTEN_LIB_DIR})

SOURCE_GROUP("Header Files\\io" FILES
	include/BINPointReader.hpp
	include/BINPointWriter.hpp
	include/LASPointReader.h
	include/LASPointWriter.hpp
	include/PlyPointReader.h
	include/PointReader.h
	include/PointWriter.hpp
	include/PTXPointReader.h
	include/XYZPointReader.hpp
)

SOURCE_GROUP("Source Files\\io" FILES
	src/BINPointReader.cpp
	src/LASPointReader.cpp
	src/LASPointWriter.cpp
	src/PTXPointReader.cpp
)

list(REMOVE_ITEM files ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

SOURCE_GROUP("lib\\rapidjson" FILES ${lib_rapidjson_files})
SOURCE_GROUP("lib\\arguments" FILES ${lib_argument_files})

if (NOT ${POTREE_TARGET} STREQUAL "")
	if (${POTREE_TARGET} STREQUAL "WASM_NODE")
		message(STATUS "nodejs wasm target will be built")
		set(POTREE_BUILD_TARGET "PotreeConverterNode")
		add_executable(PotreeConverterNode ${files} ${lib_rapidjson_files} ${lib_argument_files})
		target_link_libraries(PotreeConverterNode ${LASZIP_LIBRARY})
		set_target_properties(PotreeConverterNode PROPERTIES LINK_FLAGS "--bind \
			-s ALLOW_MEMORY_GROWTH=1 -s BINARYEN=1 -s MODULARIZE=1 --post-js  \
			${PRE_JS_PATH} -s USE_ZLIB=1 -O3 -s LINKABLE=1 -I${BOOST_EMSCRIPTEN_INCLUDE_DIR} \
			-L${BOOST_EMSCRIPTEN_LIB_DIR} ${BOOST_LINK_FLAGS} ${LASZIP_LIBRARY} ${LIBZIP_LIB}")

	elseif (${POTREE_TARGET} STREQUAL "WASM_BROWSER")
		message(STATUS "web browser wasm target will be built")
		set(POTREE_BUILD_TARGET "PotreeConverterWASM")
		add_executable(PotreeConverterWASM ${files} ${lib_rapidjson_files} ${lib_argument_files})
		target_link_libraries(PotreeConverterWASM ${LASZIP_LIBRARY})
		set_target_properties(PotreeConverterWASM PROPERTIES LINK_FLAGS "--bind \
		 	--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/resources@/resources \
			--exclude-file ${CMAKE_CURRENT_SOURCE_DIR}/resources/prepare-fs.js \
			-s ALLOW_MEMORY_GROWTH=1 -s BINARYEN=1 -s MODULARIZE=1 --post-js  \
			${PRE_JS_PATH} -s USE_ZLIB=1 -O3 -s LINKABLE=1 -I${BOOST_EMSCRIPTEN_INCLUDE_DIR} \
			-L${BOOST_EMSCRIPTEN_LIB_DIR} ${BOOST_LINK_FLAGS} ${LASZIP_LIBRARY} ${LIBZIP_LIB}")

	elseif (${POTREE_TARGET} STREQUAL "ASM")
		message(STATUS "asm.js target will be built")
		set(POTREE_BUILD_TARGET "PotreeConverterASM")
		set_target_properties(PotreeConverterASM PROPERTIES LINK_FLAGS "--bind \
			-s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1 --memory-init-file 0 --post-js ${PRE_JS_PATH} \
			-s LINKABLE=1 -s USE_ZLIB=1 -O3 -I${BOOST_EMSCRIPTEN_INCLUDE_DIR} \
			-L${BOOST_EMSCRIPTEN_LIB_DIR} ${BOOST_LINK_FLAGS} ${LASZIP_LIBRARY} ${LIBZIP_LIB}")
	endif()
else()
	message(FATAL_ERROR "A build target (-DPOTREE_TARGET) of either WASM_NODE, WASM_BROWSER, ASM_NODE, or ASM_BROWSER must be specified!")
endif()

if(UNIX)
		 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -pthread -lstdc++ -lm")
endif()
install(TARGETS ${POTREE_BUILD_TARGET} RUNTIME DESTINATION bin/ )
