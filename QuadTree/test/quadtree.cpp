//
// Created by Thoma on 11/12/2022.
//

#include "catch2/catch.hpp"
#include "quadtree/quadtree.h"
#include <chrono>
#include <iomanip>
#include <iostream>

// TODO: Unit test edge cases

TEST_CASE("insertion") {
    // Create a quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);

    quadTree.insert(AxisAlignedBoundingBox(1, 0, 3, 2), "figure1");
    quadTree.insert(AxisAlignedBoundingBox(7, 7, 1, 2), "figure2");
    quadTree.insert(AxisAlignedBoundingBox(2, 8, 4, 2), "figure3");
    quadTree.insert(AxisAlignedBoundingBox(0, 3, 5, 1), "figure4");
    quadTree.insert(AxisAlignedBoundingBox(4, 4, 2, 2), "figure5");

    auto boxes = quadTree.query_region(AxisAlignedBoundingBox(4, 4, 6, 6));
    std::cout << "\n";
}

TEST_CASE("loop") {
    // Create a quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);

    quadTree.insert(AxisAlignedBoundingBox(1, 0, 3, 2), "figure1");
    quadTree.insert(AxisAlignedBoundingBox(7, 7, 1, 2), "figure2");
    quadTree.insert(AxisAlignedBoundingBox(2, 8, 4, 2), "figure3");
    quadTree.insert(AxisAlignedBoundingBox(0, 3, 5, 1), "figure4");
    quadTree.insert(AxisAlignedBoundingBox(4, 4, 2, 2), "figure5");

    for(auto box: quadTree){
        std::cout << static_cast<std::string>(*box) << "\n";
    }
    std::cout << "\n";
}