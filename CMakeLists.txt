cmake_minimum_required( VERSION 2.8 )
project( RenderEngine )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -g -ggdb")

find_package(PkgConfig)
find_package( Eigen3 REQUIRED )

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

message(STATUS "sdl2 include = ${SDL2_INCLUDE_DIRS}")
message(STATUS "sdl2 ldflag = ${SDL2_LDFLAGS}")
message(STATUS "sdl2 ldflag other = ${SDL2_LDFLAGS_OTHER}")
message(STATUS "sdl2 cflag = ${SDL2_CFLAGS}")
message(STATUS "sdl2 cflag other = ${SDL2_CFLAGS_OTHER}")
message(STATUS "eigen3 include = ${EIGEN3_INCLUDE_DIR}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
