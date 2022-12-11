cmake_minimum_required(VERSION 3.23)
project(QuadTree)

set(CMAKE_CXX_STANDARD 17)

# QuadLib
add_library(QuadLib STATIC
        src/quadtree/quadtree.cpp
        src/quadtree/axis_aligned_bounding_box.cpp
        src/quadtree/quadtree_iterator.cpp)

target_include_directories(QuadLib PUBLIC include/)

# SDL2 packages:
# - Git Download (VC): https://github.com/libsdl-org/SDL/releases/tag/release-2.26.1
# - Installation video: https://www.youtube.com/watch?v=SjH_z0x7dWU
set(SDL2_INCLUDE_DIR include/SDL2)
set(SDL2_LIB_DIR lib/SDL2/x64)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
# target_link_libraries(${PROJECT_NAME} SDL2main SDL2)

# TestSuite
add_executable(TestSuite
        test/main.cpp
        test/axis_aligned_bounding_box.cpp test/quadtree.cpp)
target_include_directories(TestSuite PUBLIC include/)

target_link_libraries(TestSuite PRIVATE QuadLib)
