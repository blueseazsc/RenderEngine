project( Test )

add_executable( main main.cpp raster.cpp )

target_include_directories(main PUBLIC ${SDL2_INCLUDE_DIRS})
target_compile_options(main PUBLIC ${SDL2_CFLAGS_OTHER})
target_link_libraries(main ${SDL2_LDFLAGS})
