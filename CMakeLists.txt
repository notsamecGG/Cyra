cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cyra VERSION 1.0)

add_executable(cyra libs/glad.c src/main.cpp)

target_link_libraries(cyra GL dl glfw)

