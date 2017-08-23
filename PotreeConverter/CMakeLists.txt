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

add_executable(PotreeConverterASM ${files} ${lib_rapidjson_files} ${lib_argument_files})
add_executable(PotreeConverterWASM ${files} ${lib_rapidjson_files} ${lib_argument_files})

target_link_libraries(PotreeConverterASM ${LASZIP_LIBRARY})
target_link_libraries(PotreeConverterWASM ${LASZIP_LIBRARY})

set_target_properties(PotreeConverterASM PROPERTIES LINK_FLAGS "--bind -s TOTAL_MEMORY=160MB -s MODULARIZE=1 --pre-js ${PRE_JS_PATH} -s LINKABLE=1 -O3 -I${BOOST_EMSCRIPTEN_INCLUDE_DIR} -L${BOOST_EMSCRIPTEN_LIB_DIR} ${BOOST_LINK_FLAGS} ${LASZIP_LIBRARY}")
set_target_properties(PotreeConverterWASM PROPERTIES LINK_FLAGS "--bind --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/resources --exclude-file page_template/libs --exclude-file prepare-fs.js -s DISABLE_EXCEPTION_CATCHING=0 -s EXCEPTION_DEBUG=1 -s TOTAL_MEMORY=160MB  -s BINARYEN=1 -s MODULARIZE=1 --pre-js ${PRE_JS_PATH} -O3 -s LINKABLE=1 -I${BOOST_EMSCRIPTEN_INCLUDE_DIR} -L${BOOST_EMSCRIPTEN_LIB_DIR} ${BOOST_LINK_FLAGS} ${LASZIP_LIBRARY}")
if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -pthread -lstdc++ -lm")
endif()

install(TARGETS PotreeConverterASM RUNTIME DESTINATION bin/ )
install(TARGETS PotreeConverterWASM RUNTIME DESTINATION bin/ )
