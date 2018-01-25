cmake_minimum_required(VERSION 3.8)
project(plugins)

set(CMAKE_CXX_STANDARD 17)

include_directories(interfaces)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/)

add_subdirectory(h3c)
#add_subdirectory(example)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libh3c.so
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/firerain-campus-network/plugins)