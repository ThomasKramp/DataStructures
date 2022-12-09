//
// Created by Thoma on 07/12/2022.
//

#include "catch2/catch.hpp"
#include "quadtree/axis_aligned_bounding_box.h"

TEST_CASE("4 Corner Collision" "[collision]") {
    // Base box to be compared to with collision
    AxisAlignedBoundingBox baseBox = AxisAlignedBoundingBox(0, 0, 10, 10);

    // A small box inside the base box
    AxisAlignedBoundingBox internalBox = AxisAlignedBoundingBox(4, 4, 2, 2);
    CHECK(collides(baseBox, internalBox));
}

TEST_CASE("4 Corner Collision (Overlap)" "[collision][overlap]") {
    // Base box to be compared to with collision
    AxisAlignedBoundingBox baseBox = AxisAlignedBoundingBox(0, 0, 10, 10);

    // A box with the same data as the base box
    AxisAlignedBoundingBox internalBox = AxisAlignedBoundingBox(0, 0, 10, 10);
    CHECK(collides(baseBox, internalBox));
}

TEST_CASE("2 Corner Collision" "[collision]") {
    // Base box to be compared to with collision
    AxisAlignedBoundingBox baseBox = AxisAlignedBoundingBox(0, 0, 10, 10);

    // A box that has 2 corners inside the base box
    AxisAlignedBoundingBox halfCoverBox = AxisAlignedBoundingBox(3, 8, 4, 4);
    CHECK(collides(baseBox, halfCoverBox));
}

TEST_CASE("2 Corner Collision (Overlap)" "[collision][overlap]") {
    // Base box to be compared to with collision
    AxisAlignedBoundingBox baseBox = AxisAlignedBoundingBox(0, 0, 10, 10);

    // A box that has 2 corners on the edge of the base box
    AxisAlignedBoundingBox halfCoverBox = AxisAlignedBoundingBox(10, 3, 4, 4);
    CHECK(collides(baseBox, halfCoverBox));
}

TEST_CASE("1 Corner Collision" "[collision]") {
    // Base box to be compared to with collision
    AxisAlignedBoundingBox baseBox = AxisAlignedBoundingBox(0, 0, 10, 10);

    // A box that has 2 corners inside the base box
    AxisAlignedBoundingBox quarterCoverBox = AxisAlignedBoundingBox(8, 8, 4, 4);
    CHECK(collides(baseBox, quarterCoverBox));
}

TEST_CASE("1 Corner Collision (Overlap)" "[collision][overlap]") {
    // Base box to be compared to with collision
    AxisAlignedBoundingBox baseBox = AxisAlignedBoundingBox(0, 0, 10, 10);

    // A box that has 1 corners on the edge of the base box
    AxisAlignedBoundingBox quarterCoverBox = AxisAlignedBoundingBox(10, 10, 4, 4);
    CHECK(collides(baseBox, quarterCoverBox));
}

TEST_CASE("0 Corner Collision" "[collision]") {
    // Base box to be compared to with collision
    AxisAlignedBoundingBox baseBox = AxisAlignedBoundingBox(0, 0, 10, 10);

    // A box that is outside the base box
    AxisAlignedBoundingBox externalBox = AxisAlignedBoundingBox(12, 12, 2, 2);
    CHECK_FALSE(collides(baseBox, externalBox));
}

TEST_CASE("0 Corner Collision (Overlap)" "[collision][overlap]") {
    // Base box to be compared to with collision
    AxisAlignedBoundingBox baseBox = AxisAlignedBoundingBox(0, 3, 10, 4);

    // A box that overlaps with the base box
    AxisAlignedBoundingBox externalBox = AxisAlignedBoundingBox(3, 0, 4, 10);
    CHECK(collides(baseBox, externalBox));
}