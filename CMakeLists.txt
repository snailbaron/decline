cmake_minimum_required(VERSION 3.0)

project(decline)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

enable_testing()

add_subdirectory(deps)
add_subdirectory(src)
