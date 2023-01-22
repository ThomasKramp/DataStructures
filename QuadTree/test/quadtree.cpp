//
// Created by Thoma on 11/12/2022.
//

#include "catch2/catch.hpp"
#include "quadtree/quadtree.h"
#include <iostream>

TEST_CASE("insertion", "[no_check]") {
    // Create a quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);

    quadTree.insert(AxisAlignedBoundingBox(1, 2, 3, 4), "figure1");
    quadTree.insert(AxisAlignedBoundingBox(5, 6, 7, 8), "figure2");

    auto boxes = quadTree.query_region(bounds);
    for(auto box: quadTree){ std::cout << static_cast<std::string>(*box) << "\n"; }
}

TEST_CASE("get bounds", "[getter]") {
    // Create a quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);

    quadTree.insert(AxisAlignedBoundingBox(1, 2, 3, 4), "figure1");
    quadTree.insert(AxisAlignedBoundingBox(5, 6, 7, 8), "figure2");

    CHECK(quadTree.getBounds() == bounds);
}

TEST_CASE("Quadtree begin", "[iterator]") {
    // Create boxes
    auto box1 = AxisAlignedBoundingBox(AxisAlignedBoundingBox(1, 2, 3, 4));
    auto box2 = AxisAlignedBoundingBox(AxisAlignedBoundingBox(5, 6, 7, 8));
    std::string name1 = "figure1", name2 = "figure2";

    // Create quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);
    quadTree.insert(box1, name1);
    quadTree.insert(box2, name2);

    QuadtreeIterator<std::string> begin = quadTree.begin();

    CHECK(**begin == MetaBoundingBox<std::string>(box2, name2));
}

TEST_CASE("Quadtree end", "[iterator]") {
    // Create boxes
    auto box1 = AxisAlignedBoundingBox(AxisAlignedBoundingBox(1, 2, 3, 4));
    auto box2 = AxisAlignedBoundingBox(AxisAlignedBoundingBox(5, 6, 7, 8));
    std::string name1 = "figure1", name2 = "figure2";

    // Create quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);
    quadTree.insert(box1, name1);
    quadTree.insert(box2, name2);

    QuadtreeIterator<std::string> end = quadTree.end();

    CHECK(**(--end) == MetaBoundingBox<std::string>(box1, name1));
}

TEST_CASE("loop", "[no_check]") {
    // Create a quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);

    // quadTree.insert(AxisAlignedBoundingBox(1, 2, 3, 4), "figure1");
    // quadTree.insert(AxisAlignedBoundingBox(5, 6, 7, 8), "figure2");
    // quadTree.insert(AxisAlignedBoundingBox(9, 0, 1, 2), "figure3");

    quadTree.insert(AxisAlignedBoundingBox(1, 0, 3, 2), "figure1");
    quadTree.insert(AxisAlignedBoundingBox(7, 7, 1, 2), "figure2");
    quadTree.insert(AxisAlignedBoundingBox(2, 8, 4, 2), "figure3");
    quadTree.insert(AxisAlignedBoundingBox(4, 4, 2, 2), "figure4");

    for(auto box: quadTree){ std::cout << static_cast<std::string>(*box) << "\n"; }
}

TEST_CASE("Query Region", "[getter]") {
    // Create a quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);

    quadTree.insert(AxisAlignedBoundingBox(1, 2, 3, 4), "figure1");
    quadTree.insert(AxisAlignedBoundingBox(5, 6, 7, 8), "figure2");
    quadTree.insert(AxisAlignedBoundingBox(9, 0, 1, 2), "figure3");

    auto boxes = quadTree.query_region(AxisAlignedBoundingBox(6, 6, 1, 1));

    CHECK(*boxes.begin() == MetaBoundingBox<std::string>(AxisAlignedBoundingBox(5, 6, 7, 8), "figure2"));
}

TEST_CASE("Quadtree into quadtree", "[constructor]") {
    // Create boxes
    auto box1 = AxisAlignedBoundingBox(AxisAlignedBoundingBox(1, 2, 3, 4));
    auto box2 = AxisAlignedBoundingBox(AxisAlignedBoundingBox(5, 6, 7, 8));
    std::string name1 = "figure1", name2 = "figure2";

    // Create quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);
    quadTree.insert(box1, name1);
    quadTree.insert(box2, name2);

    // Create quadtree with quadtree
    Quadtree<std::string> newTree = Quadtree<std::string>(quadTree);

    CHECK(**quadTree.begin() == **newTree.begin());
}

TEST_CASE("Query Sub-Zone (SW)", "[getter] [sub_zone]") {
    // Create a quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);

    quadTree.insert(AxisAlignedBoundingBox(1, 0, 3, 2), "figure1"); // Yes
    quadTree.insert(AxisAlignedBoundingBox(7, 7, 1, 2), "figure2"); // No
    quadTree.insert(AxisAlignedBoundingBox(2, 8, 4, 2), "figure3"); // No
    quadTree.insert(AxisAlignedBoundingBox(4, 4, 2, 2), "figure4"); // Yes

    auto boxes = quadTree.query_region(AxisAlignedBoundingBox(0, 0, 5, 5));
    for(auto box: boxes){ std::cout << static_cast<std::string>(box) << "\n"; }

    CHECK(boxes.size() == 2);
}

TEST_CASE("Query Sub-Zone (SE)", "[getter] [sub_zone]") {
    // Create a quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);

    quadTree.insert(AxisAlignedBoundingBox(1, 0, 3, 2), "figure1"); // No
    quadTree.insert(AxisAlignedBoundingBox(7, 7, 1, 2), "figure2"); // No
    quadTree.insert(AxisAlignedBoundingBox(2, 8, 4, 2), "figure3"); // No
    quadTree.insert(AxisAlignedBoundingBox(4, 4, 2, 2), "figure4"); // Yes

    auto boxes = quadTree.query_region(AxisAlignedBoundingBox(5, 0, 5, 5));
    for(auto box: boxes){ std::cout << static_cast<std::string>(box) << "\n"; }

    CHECK(boxes.size() == 1);
}

TEST_CASE("Query Sub-Zone (NW)", "[getter] [sub_zone]") {
    // Create a quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);

    quadTree.insert(AxisAlignedBoundingBox(1, 0, 3, 2), "figure1"); // No
    quadTree.insert(AxisAlignedBoundingBox(7, 7, 1, 2), "figure2"); // No
    quadTree.insert(AxisAlignedBoundingBox(2, 8, 4, 2), "figure3"); // Yes
    quadTree.insert(AxisAlignedBoundingBox(4, 4, 2, 2), "figure4"); // Yes

    auto boxes = quadTree.query_region(AxisAlignedBoundingBox(0, 5, 5, 5));
    for(auto box: boxes){ std::cout << static_cast<std::string>(box) << "\n"; }

    CHECK(boxes.size() == 2);
}

TEST_CASE("Query Sub-Zone (NE)", "[getter] [sub_zone]") {
    // Create a quadtree
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);

    quadTree.insert(AxisAlignedBoundingBox(1, 0, 3, 2), "figure1"); // No
    quadTree.insert(AxisAlignedBoundingBox(7, 7, 1, 2), "figure2"); // Yes
    quadTree.insert(AxisAlignedBoundingBox(2, 8, 4, 2), "figure3"); // Yes
    quadTree.insert(AxisAlignedBoundingBox(4, 4, 2, 2), "figure4"); // Yes

    auto boxes = quadTree.query_region(AxisAlignedBoundingBox(5, 5, 5, 5));
    for(auto box: boxes){ std::cout << static_cast<std::string>(box) << "\n"; }

    CHECK(boxes.size() == 3);
}

// These test cases are to show that, boxes that lay on the intersection lines between sub-zones
// will be added to all sub-zones that have that intersection.
// This quadtree has an intersection on y = 1 & x = 1.
TEST_CASE("Edge Cases (x- & y-intersection", "[collision_detection]") {
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);
    quadTree.insert(AxisAlignedBoundingBox(3, 3, 2.000, 2.000), "figure1"); // Hits the x- & y-intersections
    auto boxes_y = quadTree.query_region(AxisAlignedBoundingBox(0, 5, 10, 1));  // Should return figure 1 & 2
    auto boxes_x = quadTree.query_region(AxisAlignedBoundingBox(5, 0, 1, 10));  // Should return figure 1 & 3
    for(auto box: boxes_y){ std::cout << "y-axis:\t" << static_cast<std::string>(box) << "\n"; }
    for(auto box: boxes_x){ std::cout << "x-axis:\t" << static_cast<std::string>(box) << "\n"; }
    CHECK(((boxes_x.size() == 1) && (boxes_y.size() == 1)));
}

TEST_CASE("Edge Cases (x-intersection)", "[collision_detection]") {
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);
    quadTree.insert(AxisAlignedBoundingBox(3, 3, 2.000, 1.999), "figure2"); // Hits the x-intersection
    auto boxes_y = quadTree.query_region(AxisAlignedBoundingBox(0, 5, 10, 1));  // Should return figure 1 & 2
    auto boxes_x = quadTree.query_region(AxisAlignedBoundingBox(5, 0, 1, 10));  // Should return figure 1 & 3
    for(auto box: boxes_y){ std::cout << "y-axis:\t" << static_cast<std::string>(box) << "\n"; }
    for(auto box: boxes_x){ std::cout << "x-axis:\t" << static_cast<std::string>(box) << "\n"; }
    CHECK(((boxes_x.size() == 1) && (boxes_y.size() == 0)));
}

TEST_CASE("Edge Cases (y-intersection)", "[collision_detection]") {
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);
    quadTree.insert(AxisAlignedBoundingBox(3, 3, 1.999, 2.000), "figure3"); // Hits the y-intersection
    auto boxes_y = quadTree.query_region(AxisAlignedBoundingBox(0, 5, 10, 1));  // Should return figure 1 & 2
    auto boxes_x = quadTree.query_region(AxisAlignedBoundingBox(5, 0, 1, 10));  // Should return figure 1 & 3
    for(auto box: boxes_y){ std::cout << "y-axis:\t" << static_cast<std::string>(box) << "\n"; }
    for(auto box: boxes_x){ std::cout << "x-axis:\t" << static_cast<std::string>(box) << "\n"; }
    CHECK(((boxes_x.size() == 0) && (boxes_y.size() == 1)));
}

TEST_CASE("Edge Cases (no intersection)", "[collision_detection]") {
    AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
    Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);
    quadTree.insert(AxisAlignedBoundingBox(3, 3, 1.999, 1.999), "figure4"); // Hits no intersections
    auto boxes_y = quadTree.query_region(AxisAlignedBoundingBox(0, 5, 10, 1));  // Should return figure 1 & 2
    auto boxes_x = quadTree.query_region(AxisAlignedBoundingBox(5, 0, 1, 10));  // Should return figure 1 & 3
    for(auto box: boxes_y){ std::cout << "y-axis:\t" << static_cast<std::string>(box) << "\n"; }
    for(auto box: boxes_x){ std::cout << "x-axis:\t" << static_cast<std::string>(box) << "\n"; }
    CHECK(((boxes_x.size() == 0) && (boxes_y.size() == 0)));
}