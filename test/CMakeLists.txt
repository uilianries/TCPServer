# Tests
cmake_minimum_required(VERSION 3.0.2)
project(test-tcp-server CXX)

# Applicaion files ############################################################
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Create Application ##########################################################
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS_GTEST} ${CONAN_LIBS_POCO})