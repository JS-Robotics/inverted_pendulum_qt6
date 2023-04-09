cmake_minimum_required(VERSION 3.16)

find_package(Qt6 COMPONENTS Widgets)  # TODO figure out why it has to be added here too

add_library(simulator src/simulator.cc)

target_include_directories(simulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
