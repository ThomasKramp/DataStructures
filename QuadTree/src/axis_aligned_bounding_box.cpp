//
// Created by Thoma on 05/12/2022.
//

#include "axis_aligned_bounding_box.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox(double &x, double &y, double &width, double &height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

AxisAlignedBoundingBox::operator std::string() const {
    return "x: " + std::to_string(this->x) + " y: " + std::to_string(this->y)
        + " w: " + std::to_string(this->width) + " h: " + std::to_string(this->height);
}

bool checkIfInBetween(const double value, const double lowerBound, const double upperBound) {
    return (value >= lowerBound) && (value <= lowerBound + upperBound);
}

bool checkIfBoxContainsCorner(const AxisAlignedBoundingBox &one, const AxisAlignedBoundingBox &two) {
    // Check if box 1 has a point in box 2
    bool oneXIsInTwoX = checkIfInBetween(one.x, two.x, two.width)       // Check if box 1 x is in box 2
            || checkIfInBetween(one.x + one.width, two.x, two.width);   // Check if box 1 x + box 1 width is in box 2
    bool oneYIsInTwoY = checkIfInBetween(one.y, two.y, two.height)      // Check if box 1 y is in box 2
            || checkIfInBetween(one.y + two.height, two.y, two.height); // Check if box 1 y + box 1 height is in box 2
    return oneXIsInTwoX && oneYIsInTwoY;
}

bool collides(const AxisAlignedBoundingBox &one, const AxisAlignedBoundingBox &two) {
    // Check if both boxes exist and aren't infinitely small
    bool oneHasDimension = one.width > 0 && one.height > 0;
    bool twoHasDimension = two.width > 0 && two.height > 0;

    bool oneIsInTwo = checkIfBoxContainsCorner(one, two);
    bool twoIsInOne = checkIfBoxContainsCorner(two, one);

    return (oneHasDimension && twoHasDimension) && (oneIsInTwo || twoIsInOne);
}
