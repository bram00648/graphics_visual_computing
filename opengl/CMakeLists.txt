cmake_minimum_required(VERSION 3.16)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 3.3 REQUIRED)

add_executable(myapp main.cpp src/glad.c)

target_include_directories(myapp PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(myapp PRIVATE glfw pthread)