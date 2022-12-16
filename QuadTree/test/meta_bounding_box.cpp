//
// Created by Thoma on 07/12/2022.
//

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