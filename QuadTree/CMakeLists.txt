cmake_minimum_required(VERSION 3.23)
project(QuadTree)

set(CMAKE_CXX_STANDARD 17)

add_library(QuadLib STATIC src/quadtree.cpp include/axis_aligned_bounding_box.h src/axis_aligned_bounding_box.cpp)
target_include_directories(QuadLib PUBLIC include/)

add_executable(TestSuite test/main.cpp src/axis_aligned_bounding_box.cpp)

target_link_libraries(TestSuite PRIVATE QuadLib)
