project(list-project)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

include_directories(list)
add_subdirectory(list)
add_subdirectory(tests)
add_subdirectory(lib/googletest)