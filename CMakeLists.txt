
cmake_minimum_required(VERSION 3.5.1)
project (atte-motor)

set (CMAKE_CXX_FLAGS "-std=c++1z ${CMAKE_CXX_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS "-lGL -lglfw ${CMAKE_EXE_LINKER_FLAGS}")

add_executable(main main.cpp)

