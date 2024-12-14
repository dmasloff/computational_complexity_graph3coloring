cmake_minimum_required(VERSION 3.26)
project(benchmarks)

add_executable(profile_graph benchmark.cpp)
target_link_libraries(profile_graph PRIVATE gtest gtest_main benchmark::benchmark graph_lib)
target_include_directories(profile_graph PRIVATE ${CMAKE_SOURCE_DIR}/src)
