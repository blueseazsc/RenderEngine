cmake_minimum_required( VERSION 2.8 )
project( RenderEngine )

add_executable( main src/main.cpp )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

find_package(PkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

message(STATUS "include = ${SDL2_INCLUDE_DIRS}")
message(STATUS "ldflag = ${SDL2_LDFLAGS}")
message(STATUS "ldflag other = ${SDL2_LDFLAGS_OTHER}")
message(STATUS "cflag = ${SDL2_CFLAGS}")
message(STATUS "cflag other = ${SDL2_CFLAGS_OTHER}")

target_include_directories(main PUBLIC ${SDL2_INCLUDE_DIRS})
target_compile_options(main PUBLIC ${SDL2_CFLAGS_OTHER})
target_link_libraries(main ${SDL2_LDFLAGS})
