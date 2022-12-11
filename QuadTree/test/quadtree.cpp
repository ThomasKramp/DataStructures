//
// Created by Thoma on 11/12/2022.
//

#include "catch2/catch.hpp"
#include "quadtree/quadtree.h"

TEST_CASE("insertion") {
    // Create a quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 5);

    quadTree.insert(AxisAlignedBoundingBox(1, 0, 3, 2), "figure1");
    quadTree.insert(AxisAlignedBoundingBox(7, 7, 1, 2), "figure2");
    quadTree.insert(AxisAlignedBoundingBox(4, 2, 4, 2), "figure3");
    quadTree.insert(AxisAlignedBoundingBox(0, 3, 5, 1), "figure4");
    quadTree.insert(AxisAlignedBoundingBox(4, 4, 2, 2), "figure5");
}