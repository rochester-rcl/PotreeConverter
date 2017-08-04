project(PotreeConverter)

set(RAPIDJSON_INCLUDE_DIR lib/rapidjson/include)
set(ARGUMENTS_INCLUDE_DIR lib/arguments)
set(CMAKE_VERBOSE_MAKEFILE on)
set(BOOST_EMSCRIPTEN_INCLUDE_DIR $ENV{BOOST_PATH}/dist/emscripten/include)
set(BOOST_EMSCRIPTEN_LIB_DIR $ENV{BOOST_PATH}/dist/emscripten/lib)
set(BOOST_LINK_FLAGS "-lboost_system -lboost_filesystem")
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

add_executable(PotreeConverter ${files} ${lib_rapidjson_files} ${lib_argument_files})

target_link_libraries(PotreeConverter ${LASZIP_LIBRARY})
set_target_properties(PotreeConverter PROPERTIES LINK_FLAGS "--bind -s TOTAL_MEMORY=160MB -s LINKABLE=1 -O3 -I${BOOST_EMSCRIPTEN_INCLUDE_DIR} -L${BOOST_EMSCRIPTEN_LIB_DIR} ${BOOST_LINK_FLAGS} ${LASZIP_LIBRARY}")

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -pthread -lstdc++ -lm")
    # target_link_libraries(PotreeConverter -lstdc++fs) using boost
endif()

install(TARGETS PotreeConverter RUNTIME DESTINATION bin/ )
