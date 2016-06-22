# Daemon
cmake_minimum_required(VERSION 3.0.2)
project(tcp-server CXX)

# Boost Package ###############################################################
find_package(Boost REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS})

# Libraries ###################################################################
find_library(POCO_FOUNDATION PocoFoundation)
find_library(POCO_UTIL PocoUtil)
find_library(POCO_JSON PocoJSON)
find_library(POCO_XML PocoXML)
find_library(POCO_DATA PocoData)
find_library(POCO_NET PocoNet)
set(Poco_LIBRARIES ${POCO_UTIL} ${POCO_JSON} ${POCO_XML} ${POCO_FOUNDATION})

# Applicaion files ############################################################
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Create Application ##########################################################
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${Poco_LIBRARIES} pthread)

# Install #####################################################################
install(TARGETS ${PROJECT_NAME}
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_EXECUTE WORLD_READ)
