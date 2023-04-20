cmake_minimum_required(VERSION 3.16)
project(inverted_pendulum_simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (WIN32)
    #set(CMAKE_PREFIX_PATH "$ENV{QT_INSTALL_PATH}/mingw_64")  // Lost support for MinGW64 when FastDDS was added
#    set(CMAKE_PREFIX_PATH "C:/Qt/6.4.2/msvc2019_64")
    set(CMAKE_PREFIX_PATH "$ENV{QT_INSTALL_PATH}")
endif ()

if (UNIX)
    set(CMAKE_PREFIX_PATH "$ENV{QT_INSTALL_PATH}/gcc_64/lib/cmake/Qt6")
#    set(CMAKE_PREFIX_PATH "/home/sondre/Qt/6.5.0/gcc_64/lib/cmake/Qt6")
endif ()

add_subdirectory(simulator)
add_subdirectory(communication)

if(NOT fastcdr_FOUND)
    message(STATUS "Not found")
    find_package(fastcdr REQUIRED)
endif()

if(NOT fastrtps_FOUND)
    find_package(fastrtps REQUIRED)
endif()

find_package(Qt6 COMPONENTS
        Core
        Gui
        Quick
        Quick3D
        Widgets
        REQUIRED)

add_executable(inverted_pendulum_simulation main.cpp backend.cc
                qml.qrc
        )

target_link_libraries(inverted_pendulum_simulation PUBLIC simulator communication)

set_target_properties(inverted_pendulum_simulation PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
        )

target_link_libraries(inverted_pendulum_simulation PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Quick
        Qt::Quick3D
        )

target_include_directories(inverted_pendulum_simulation PUBLIC inverted_pendulum_simulation/include)

if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
