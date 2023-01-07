//
// Created by Thoma on 11/12/2022.
//

#include "catch2/catch.hpp"
#include "quadtree/quadtree.h"
#include <iostream>

TEST_CASE("edge_cases_intersection") {
    // This test case is to show that, boxes that lay on the intersection lines between sub-zones
    // will be added to all sub-zones that have that intersection.
    // This quadtree has an intersection on y = 1 & x = 1.

    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);
    quadTree.insert(AxisAlignedBoundingBox(3, 3, 2.000, 2.000), "figure1"); // Hits the x- & y-intersections
    auto boxes_y = quadTree.query_region(AxisAlignedBoundingBox(0, 5, 10, 1));  // Should return figure 1 & 2
    auto boxes_x = quadTree.query_region(AxisAlignedBoundingBox(5, 0, 1, 10));  // Should return figure 1 & 3
    for(auto box: boxes_y){ std::cout << "y-axis:\t" << static_cast<std::string>(box) << "\n"; }
    for(auto box: boxes_x){ std::cout << "x-axis:\t" << static_cast<std::string>(box) << "\n"; }

    quadTree = Quadtree<std::string>(bounds, 3);
    quadTree.insert(AxisAlignedBoundingBox(3, 3, 2.000, 1.999), "figure2"); // Hits the x-intersection
    boxes_y = quadTree.query_region(AxisAlignedBoundingBox(0, 5, 10, 1));  // Should return figure 1 & 2
    boxes_x = quadTree.query_region(AxisAlignedBoundingBox(5, 0, 1, 10));  // Should return figure 1 & 3
    for(auto box: boxes_y){ std::cout << "y-axis:\t" << static_cast<std::string>(box) << "\n"; }
    for(auto box: boxes_x){ std::cout << "x-axis:\t" << static_cast<std::string>(box) << "\n"; }

    quadTree = Quadtree<std::string>(bounds, 3);
    quadTree.insert(AxisAlignedBoundingBox(3, 3, 1.999, 2.000), "figure3"); // Hits the y-intersection
    boxes_y = quadTree.query_region(AxisAlignedBoundingBox(0, 5, 10, 1));  // Should return figure 1 & 2
    boxes_x = quadTree.query_region(AxisAlignedBoundingBox(5, 0, 1, 10));  // Should return figure 1 & 3
    for(auto box: boxes_y){ std::cout << "y-axis:\t" << static_cast<std::string>(box) << "\n"; }
    for(auto box: boxes_x){ std::cout << "x-axis:\t" << static_cast<std::string>(box) << "\n"; }

    quadTree = Quadtree<std::string>(bounds, 3);
    quadTree.insert(AxisAlignedBoundingBox(3, 3, 1.999, 1.999), "figure4"); // Hits no intersections
    boxes_y = quadTree.query_region(AxisAlignedBoundingBox(0, 5, 10, 1));  // Should return figure 1 & 2
    boxes_x = quadTree.query_region(AxisAlignedBoundingBox(5, 0, 1, 10));  // Should return figure 1 & 3
    for(auto box: boxes_y){ std::cout << "y-axis:\t" << static_cast<std::string>(box) << "\n"; }
    for(auto box: boxes_x){ std::cout << "x-axis:\t" << static_cast<std::string>(box) << "\n"; }

    std::cout << "\n";
}

TEST_CASE("insertion") {
    // Create a quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);

    quadTree.insert(AxisAlignedBoundingBox(1, 0, 3, 2), "figure1");
    quadTree.insert(AxisAlignedBoundingBox(7, 7, 1, 2), "figure2");
    quadTree.insert(AxisAlignedBoundingBox(2, 8, 4, 2), "figure3");
    quadTree.insert(AxisAlignedBoundingBox(5, 3, 5, 1), "figure4");
    quadTree.insert(AxisAlignedBoundingBox(4, 4, 2, 2), "figure5");
    quadTree.insert(AxisAlignedBoundingBox(3, 3, 2, 2), "figure6");

    auto boxes = quadTree.query_region(AxisAlignedBoundingBox(4, 4, 6, 6));
    //auto boxes = quadTree.query_region(AxisAlignedBoundingBox(0, 0, 10, 10));
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