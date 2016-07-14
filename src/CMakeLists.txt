# Daemon
cmake_minimum_required(VERSION 3.0.2)
project(tcp-server CXX)

# Boost Package ###############################################################
find_package(Boost REQUIRED regex log log_setup filesystem system thread)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

include_directories(SYSTEM ${CONAN_INCLUDE_DIRS_POCO})

# Applicaion files ############################################################
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Create Application ##########################################################
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${CONAN_LIBS_POCO} pthread)

# Install #####################################################################
install(TARGETS ${PROJECT_NAME}
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_EXECUTE WORLD_READ)
