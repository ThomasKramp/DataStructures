//
// Created by Thoma on 05/12/2022.
//

#include "quadtree/axis_aligned_bounding_box.h"

bool checkIfBoxesOverlap(const AxisAlignedBoundingBox &box, const AxisAlignedBoundingBox &box1);

AxisAlignedBoundingBox::AxisAlignedBoundingBox(double &x, double &y, double &width, double &height) {
    if (width < 0) {
        this->x = x + width;
        this->width = -1 * width;
    } else {
        this->x = x;
        this->width = width;
    }

    if (height < 0) {
        this->y = y + height;
        this->height = -1 * height;
    } else {
        this->y = y;
        this->height = height;
    }
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(double &&x, double &&y, double &&width, double &&height) {
    if (width < 0) {
        this->x = x + width;
        this->width = -1 * width;
    } else {
        this->x = x;
        this->width = width;
    }

    if (height < 0) {
        this->y = y + height;
        this->height = -1 * height;
    } else {
        this->y = y;
        this->height = height;
    }
}

AxisAlignedBoundingBox::operator std::string() const {
    return "x: " + std::to_string(this->x) + " y: " + std::to_string(this->y)
        + " w: " + std::to_string(this->width) + " h: " + std::to_string(this->height);
}

bool checkIfInBetween(const double value, const double lowerBound, const double upperBound) {
    return (value >= lowerBound) && (value <= upperBound);
}

bool checkIfBoxContainsCorner(const AxisAlignedBoundingBox& one, const AxisAlignedBoundingBox& two) {
    // Check if box 1 has a point in box 2
    bool oneXIsInTwoX = checkIfInBetween(one.x, two.x, two.x + two.width)       // Check if box 1 x is in box 2
            || checkIfInBetween(one.x + one.width, two.x, two.x + two.width);   // Check if box 1 x + box 1 width is in box 2
    bool oneYIsInTwoY = checkIfInBetween(one.y, two.y, two.y + two.height)      // Check if box 1 y is in box 2
            || checkIfInBetween(one.y + one.height, two.y, two.y + two.height); // Check if box 1 y + box 1 height is in box 2
    return oneXIsInTwoX && oneYIsInTwoY;
}

bool checkIfBoxesOverlap(const AxisAlignedBoundingBox& one, const AxisAlignedBoundingBox& two) {
    // Check if box 1 overlaps box 2
    bool oneXIsInTwoX = checkIfInBetween(one.x, two.x, two.x + two.width)       // Check if box 1 x is in box 2
            || checkIfInBetween(one.x + one.width, two.x, two.x + two.width);   // Check if box 1 x + box 1 width is in box 2
    bool twoYIsInOneY = checkIfInBetween(two.y, one.y, one.y + one.height)      // Check if box 2 y is in box 1
            || checkIfInBetween(two.y + two.height, one.y, one.y + one.height); // Check if box 2 y + box 2 height is in box 1
    return oneXIsInTwoX && twoYIsInOneY;
}

bool collides(const AxisAlignedBoundingBox &one, const AxisAlignedBoundingBox &two) {
    // Check if both boxes exist and aren't infinitely small
    bool oneHasDimension = one.width > 0 && one.height > 0;
    bool twoHasDimension = two.width > 0 && two.height > 0;

    bool oneIsInTwo = checkIfBoxContainsCorner(one, two);
    bool twoIsInOne = checkIfBoxContainsCorner(two, one);

    bool oneOverlapsTwo = checkIfBoxesOverlap(one, two);    // X1 <= X2 && X2 + Width2 <= X1 + Width1
                                                            // Y2 <= Y1 && Y1 + Height1 <= Y2 + Height2
    bool twoOverlapsOne = checkIfBoxesOverlap(two, one);    // X2 <= X1 && X1 + Width1 <= X2 + Width2
                                                            // Y1 <= Y2 && Y2 + Height2 <= Y1 + Height1

    return (oneHasDimension && twoHasDimension) && (oneIsInTwo || twoIsInOne || oneOverlapsTwo || twoOverlapsOne);
}

double AxisAlignedBoundingBox::get_x() const { return this->x; }
double AxisAlignedBoundingBox::get_y() const { return this->y; }
double AxisAlignedBoundingBox::get_width() const { return this->width; }
double AxisAlignedBoundingBox::get_height() const { return this->height; }
