cmake_minimum_required(VERSION 3.0.2)
project(TCPServer CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

option(TESTS "Generate tests" ON)

add_subdirectory(src)
add_subdirectory(config)