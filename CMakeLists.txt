cmake_minimum_required( VERSION 2.8 )
project( RenderEngine )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -g -ggdb")

find_package(PkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

message(STATUS "include = ${SDL2_INCLUDE_DIRS}")
message(STATUS "ldflag = ${SDL2_LDFLAGS}")
message(STATUS "ldflag other = ${SDL2_LDFLAGS_OTHER}")
message(STATUS "cflag = ${SDL2_CFLAGS}")
message(STATUS "cflag other = ${SDL2_CFLAGS_OTHER}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
