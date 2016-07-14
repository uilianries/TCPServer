cmake_minimum_required(VERSION 3.0.2)
project(TCPServer CXX)

# Include Conan.io ###########################################################
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Compiler flags ##############################################################
set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage -std=c++11 -pedantic -Wall -Wextra -Wshadow -Winit-self -Wold-style-cast -Woverloaded-virtual -Werror")

# Add sub directories #########################################################
option(TESTS "Generate tests" ON)
if(TESTS)
    add_subdirectory(test)
endif()

add_subdirectory(src)
add_subdirectory(config)
