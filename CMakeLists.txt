cmake_minimum_required(VERSION 3.8)
project(flyos_campus_network)

set(CMAKE_CXX_STANDARD 17)

#qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(PkgConfig)

pkg_check_modules(DTK REQUIRED
        dtkcore
        dtkwidget
        )

set(QRC_FILES
        images/images.qrc)

set(SOURCE_FILES
        main.cpp
        ui/mainwindow.cpp
        ui/mainwindow.h
        ui/widgets/LeftWidget.cpp
        ui/widgets/LeftWidget.h interfaces/pluginsInterface.h)

include_directories(${DTK_INCLUDE_DIRS})

add_subdirectory(plugins)

add_executable(flyos-campus-network  ${SOURCE_FILES} ${QRC_FILES})
target_link_libraries(flyos-campus-network Qt5::Core Qt5::Gui Qt5::Widgets ${DTK_LIBRARIES})

install(TARGETS flyos-campus-network RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(FILES flyos-campus-network.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
install(FILES images/logo.png DESTINATION ${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/64x64/apps RENAME flyos-campus-network.png)