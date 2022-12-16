//
// Created by Thoma on 11/12/2022.
//

#include "catch2/catch.hpp"
#include "quadtree/quadtree.h"
#include <ctime>

TEST_CASE("insertion") {
    // Create a quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);

    quadTree.insert(AxisAlignedBoundingBox(1, 0, 3, 2), "figure1");
    quadTree.insert(AxisAlignedBoundingBox(7, 7, 1, 2), "figure2");
    quadTree.insert(AxisAlignedBoundingBox(2, 8, 4, 2), "figure3");
    quadTree.insert(AxisAlignedBoundingBox(0, 3, 5, 1), "figure4");
    quadTree.insert(AxisAlignedBoundingBox(4, 4, 2, 2), "figure5");

    // repeaded adding (even thought unordered_set shouldn't allow it
    // boxes on the edges get added to zone
    // hoe moet je het timen
    // begin & end laten nakijken

    // https://stackoverflow.com/a/39438574
    clock_t start = clock();
    auto boxes = quadTree.query_region(AxisAlignedBoundingBox(0, 0, 6, 6));
    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5f\n", elapsed);
    std::printf("");
}

// TODO: Unit test edge cases