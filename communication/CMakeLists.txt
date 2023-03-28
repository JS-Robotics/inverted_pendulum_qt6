cmake_minimum_required(VERSION 3.16)

add_library(communication src/communication.cc)

target_include_directories(communication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(communication PUBLIC simulator)