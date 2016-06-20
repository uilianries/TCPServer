# Daemon
cmake_minimum_required(VERSION 3.0.2)
project(tcp-server CXX)

# Compiler flags ##############################################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage -std=c++11 -pedantic -Wall -Wshadow -Wextra -Winit-self -Wold-style-cast -Woverloaded-virtual -Werror")

# Applicaion files ############################################################
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Create Application ##########################################################
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME})

# Install #####################################################################
install(TARGETS ${PROJECT_NAME}
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_EXECUTE WORLD_READ)