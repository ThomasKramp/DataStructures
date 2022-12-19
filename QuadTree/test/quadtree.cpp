//
// Created by Thoma on 11/12/2022.
//

#include "catch2/catch.hpp"
#include "quadtree/quadtree.h"
#include <chrono>
#include <iomanip>
#include <iostream>

// TODO: Unit test edge cases

TEST_CASE("time_complexity") {
    // Create a quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);

    std::srand( (unsigned)time( NULL ) );

    int loops = 7;
    float x = 0, y = 0, w = 0, h = 0;
    for (int i = 0; i < loops; i++) {
        // Generate random float between 0 and 10
        x = (float) std::rand()/RAND_MAX * 10;
        y = (float) std::rand()/RAND_MAX * 10;
        do { w = (float) std::rand()/RAND_MAX * 10 / loops; } while ((w == 0) || (x + w > 10));
        do { h = (float) std::rand()/RAND_MAX * 10 / loops; } while ((h == 0) || (y + h > 10));
        quadTree.insert(AxisAlignedBoundingBox(x, y, w, h), "figure" + std::to_string(i));
    }

    for(auto box: quadTree){
        std::cout << static_cast<std::string>(*box) << "\n";
    }

    // Start Clock
    auto start = std::chrono::steady_clock::now();
    // Search boxes
    auto boxes = quadTree.query_region(AxisAlignedBoundingBox(4, 4, 6, 6));
    // Stop Clock
    auto end = std::chrono::steady_clock::now();
    // Display time
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time elapsed: " << std::setprecision(5) << diff.count() << " s\n";
    std::cout << "Amount of boxes: " << " \n";
}

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