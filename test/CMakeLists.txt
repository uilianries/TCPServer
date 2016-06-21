# Tests
cmake_minimum_required(VERSION 3.0.2)
project(test-tcp-server CXX)

# GTest package ###############################################################
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Applicaion files ############################################################
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Create Application ##########################################################
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} ${CONAN_LIBS_POCO})
GTEST_ADD_TESTS(${PROJECT_NAME} "" AUTO)
