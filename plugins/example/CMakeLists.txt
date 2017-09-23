cmake_minimum_required(VERSION 3.8)
project(flyos_campus_network)

set(CMAKE_CXX_STANDARD 17)

#qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)

set(QRC_FILES
        resources/resources.qrc)

set(SOURCE_FILES
        examplePlugins.h
        examplePlugins.cpp)

add_library(example SHARED ${SOURCE_FILES} ${QRC_FILES})
target_link_libraries(example Qt5::Core Qt5::Gui Qt5::Widgets)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libexample.so
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/flyos-campus-network/plugins)