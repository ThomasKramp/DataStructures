cmake_minimum_required(VERSION 3.23)
project(QuadTree)

set(CMAKE_CXX_STANDARD 17)

# QuadLib
add_library(QuadLib STATIC
        src/quadtree/quadtree.cpp
        src/quadtree/axis_aligned_bounding_box.cpp
        src/quadtree/meta_bounding_box.cpp
        src/quadtree/quadtree_iterator.cpp)

target_include_directories(QuadLib PUBLIC include/)

# TestSuite
add_executable(TestSuite
        test/main.cpp
        test/quadtree.cpp
        test/axis_aligned_bounding_box.cpp
        test/meta_bounding_box.cpp
        test/project_test.cpp)

target_include_directories(TestSuite PUBLIC include/)

target_link_libraries(TestSuite PRIVATE QuadLib)

# Error check
target_compile_options(QuadLib PUBLIC -Wall -Wextra -Wpedantic -Werror)