cmake_minimum_required( VERSION 2.8 )

# set(CMAKE_C_COMPILER "/usr/bin/gcc")
# set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project( RenderEngine )

message(STATUS "project source dir= ${RenderEngine_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11")

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${RenderEngine_SOURCE_DIR}/cmake")
# find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)

find_package(PkgConfig)
find_package( Eigen3 REQUIRED )

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)

message(STATUS "sdl2 include dir 			= ${SDL2_INCLUDE_DIR}")
message(STATUS "sdl2 include dirs 			= ${SDL2_INCLUDE_DIRS}")
message(STATUS "sdl2 ldflag 				= ${SDL2_LDFLAGS}")
message(STATUS "sdl2 ldflag other 			= ${SDL2_LDFLAGS_OTHER}")
message(STATUS "sdl2 cflag 					= ${SDL2_CFLAGS}")
message(STATUS "sdl2 cflag other 			= ${SDL2_CFLAGS_OTHER}")
message(STATUS "sdl2 library 				= ${SDL2_LIBRARY}")
message(STATUS "sdl2 libraries 				= ${SDL2_LIBRARIES}")

message(STATUS "sdl2 image include dir 		= ${SDL2_IMAGE_INCLUDE_DIR}")
message(STATUS "sdl2 image include dirs 	= ${SDL2_IMAGE_INCLUDE_DIRS}")
message(STATUS "sdl2 image ldflag 			= ${SDL2_IMAGE_LDFLAGS}")
message(STATUS "sdl2 image ldflag other 	= ${SDL2_IMAGE_LDFLAGS_OTHER}")
message(STATUS "sdl2 image cflag 			= ${SDL2_IMAGE_CFLAGS}")
message(STATUS "sdl2 image cflag other 		= ${SDL2_IMAGE_CFLAGS_OTHER}")
message(STATUS "sdl2 image library 			= ${SDL2_IMAGE_LIBRARY}")
message(STATUS "sdl2 image libraries 		= ${SDL2_IMAGE_LIBRARIES}")

message(STATUS "eigen3 include 				= ${EIGEN3_INCLUDE_DIR}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
