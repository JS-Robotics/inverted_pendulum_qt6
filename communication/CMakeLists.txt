cmake_minimum_required(VERSION 3.16)

find_package(Qt6 COMPONENTS Widgets)  # TODO figure out why it has to be added here too

set(MESSAGE_SOURCES
        src/message_types/Float32/Float32.cxx
        src/message_types/Float32/Float32PubSubTypes.cxx
        src/message_types/Vector3/Vector3.cxx
        src/message_types/Vector3/Vector3PubSubTypes.cxx
        )

add_library(communication
        src/communication.cc
        src/turns_publisher.cc
        src/ros_publisher.h
        ${MESSAGE_SOURCES}
        )

find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)


target_include_directories(communication PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

target_link_libraries(communication PUBLIC
        simulator
        fastcdr
        fastrtps
        )