//
// Created by Thoma on 11/12/2022.
//

#include "catch2/catch.hpp"
#include "quadtree/quadtree.h"
#include <chrono>
#include <iomanip>
#include <iostream>

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

    // Start Clock
    auto start = std::chrono::steady_clock::now();
    // Execute Code
    auto boxes = quadTree.query_region(AxisAlignedBoundingBox(0, 0, 6, 6));
    // Stop Clock
    auto end = std::chrono::steady_clock::now();
    // Display time
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time elapsed: " << std::setprecision(5) << diff.count() << " s\n";
}

// TODO: Unit test edge cases