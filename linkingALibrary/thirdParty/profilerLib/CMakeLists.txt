cmake_minimum_required(VERSION 3.13)
project(profilerLib)


add_library(profilerLib INTERFACE)
target_include_directories(profilerLib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")


add_executable(profilerLib_test)
target_sources(profilerLib_test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp" )
target_link_libraries(profilerLib_test PUBLIC profilerLib)

