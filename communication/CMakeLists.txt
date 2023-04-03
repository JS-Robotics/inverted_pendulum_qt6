cmake_minimum_required(VERSION 3.16)


add_library(communication src/communication.cc src/turns_publisher.cc)

find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)


target_include_directories(communication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(communication PUBLIC simulator)