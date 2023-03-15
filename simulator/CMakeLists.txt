cmake_minimum_required(VERSION 3.16)

add_library(simulator src/simulator.cc)

target_include_directories(simulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
