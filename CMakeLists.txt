
cmake_minimum_required(VERSION 3.5.1)
project (atte-motor)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set (CMAKE_CXX_FLAGS "-std=c++1z ${CMAKE_CXX_FLAGS}")

add_executable(main main.cpp)

target_link_libraries(main ${OPENGL_LIBRARY} glfw)

