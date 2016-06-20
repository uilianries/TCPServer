# Configuration
cmake_minimum_required(VERSION 3.0.2)

# Configuration files #########################################################
file(GLOB CONFIG_FILES *.json)

# Install file ################################################################
install(FILES ${CONFIG_FILES}
        DESTINATION /etc/tcp-server
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE WORLD_READ)