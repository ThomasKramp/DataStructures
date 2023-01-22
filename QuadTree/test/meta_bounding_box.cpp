//
// Created by Thoma on 07/12/2022.
//

#include <iostream>
#include "catch2/catch.hpp"
#include "quadtree/meta_bounding_box.h"

TEST_CASE("Compare 2 mbb's (same)"  "[operator] [comparison]") {
    MetaBoundingBox<std::string> box1 = MetaBoundingBox<std::string>(AxisAlignedBoundingBox(4, 4, 2, 2), "box");
    MetaBoundingBox<std::string> box2 = MetaBoundingBox<std::string>(AxisAlignedBoundingBox(4, 4, 2, 2), "box");
    CHECK(box1 == box2);
}

TEST_CASE("Compare 2 mbb's (different)"  "[operator] [comparison]") {
    MetaBoundingBox<std::string> box1 = MetaBoundingBox<std::string>(AxisAlignedBoundingBox(4, 4, 2, 2), "box1");
    MetaBoundingBox<std::string> box2 = MetaBoundingBox<std::string>(AxisAlignedBoundingBox(2, 2, 4, 4), "box2");
    CHECK_FALSE(box1 == box2);
}

TEST_CASE("mbb to string"  "[operator] [toString]") {
    double x = 1, y = 2, w = 3, h = 4;
    std::string name = "box";
    MetaBoundingBox<std::string> box = MetaBoundingBox<std::string>(AxisAlignedBoundingBox(x, y, w, h), "box");
    std::string boxString = "x: " + std::to_string(x) + " y: " + std::to_string(y)
                            + " w: " + std::to_string(w) + " h: " + std::to_string(h) + " " + name;
    CHECK(boxString.compare(static_cast<std::string>(box)) == 0);
}

TEST_CASE("mbb hash"  "[operator] [hashing]") {
    double x = 4, y = 11, w = 6, h = 13;
    MetaBoundingBox<std::string> box = MetaBoundingBox<std::string>(AxisAlignedBoundingBox(x, y, w, h), "box");
    size_t boxHash = std::hash<MetaBoundingBox<std::string>>{}(box);
    // std::cout << boxHash << "\n";
    // z = root of ((x + w)²/2 + (y + h)²/2) = root of ((4 + 6)²/2 + (11 + 13)²/2) = 13
    //      --> hash<double>(13) = 84391782279222564
    // weight = (x + w) + (y + h) * 16 = (4 + 6) + (11 + 13) * 16 = 394
    //      --> hash<double>(394) = 13959674904471585956
    // hash = z xor weight = 84391782279222564 xor 13959674904471585956 = 13875990389757956480
    unsigned long long calcHash = 13875990389757956480U;
    CHECK((size_t) calcHash == boxHash);
}