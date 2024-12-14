cmake_minimum_required(VERSION 3.26)
project(tests)

add_executable(test_graph test.cpp)
target_link_libraries(test_graph PRIVATE gtest gtest_main graph_lib)
target_include_directories(test_graph PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_test(NAME RunGraphTest COMMAND test_graph)
