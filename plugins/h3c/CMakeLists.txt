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

set(C3H_SOURCE_FILES
        c3hclient/adapter.h
        c3hclient/adapter.c
        c3hclient/auth.c
        c3hclient/auth.h
        c3hclient/defs.h
        c3hclient/md5.c
        c3hclient/md5.h
        c3hclient/main.c)

set(SOURCE_FILES
        H3cWidget.cpp
        H3cWidget.h
        H3cPlugins.cpp
        H3cPlugins.h
        H3cThread.cpp
        H3cThread.h)

add_library(h3c SHARED ${SOURCE_FILES} ${QRC_FILES})
target_link_libraries(h3c Qt5::Core Qt5::Gui Qt5::Widgets pcap)

add_executable(c3hclient ${C3H_SOURCE_FILES})
target_link_libraries(c3hclient pcap)

install(TARGETS c3hclient RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/share/flyos-campus-network/h3c)

