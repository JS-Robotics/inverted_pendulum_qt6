# https://doc.qt.io/qt-6/qtquick3d-index.html
# https://www.jetbrains.com/help/clion/qt-tutorial.html#troubleshooting
# https://www.qt.io/product/qt6/qml-book/ch12-qtquick3d-assets
# In Blender use Y-up and Z-forward to align with Qt when models are imported
# https://doc.qt.io/qt-5/qtqml-cppintegration-topic.html

cmake_minimum_required(VERSION 3.16)
project(inverted_pendulum_simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.4.2/mingw_64")
endif ()

if (UNIX)
    set(CMAKE_PREFIX_PATH "$ENV{HOME}/Qt/6.4.2/gcc_64/lib/cmake/Qt6")
endif ()

find_package(Qt6 COMPONENTS
        Core
        Gui
        Quick
        Quick3D
        REQUIRED)

add_executable(inverted_pendulum_simulation main.cpp
                qml.qrc
        )

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
