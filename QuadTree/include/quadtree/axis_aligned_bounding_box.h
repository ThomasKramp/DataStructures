//
// Created by Thoma on 05/12/2022.
//

#ifndef LABO_7_AXIS_ALIGNED_BOUNDING_BOX_H
#define LABO_7_AXIS_ALIGNED_BOUNDING_BOX_H

#include <string>

// This class represents an axis-aligned bounding box
// In a 2D problem, this is simply a rectangle whose sides are parallel to the X- and Y-axis
class AxisAlignedBoundingBox {
private:
    double x, y, width, height;
    friend bool checkIfInBetween(double value, double lowerBound, double upperBound);
    friend bool checkIfBoxesOverlap(const AxisAlignedBoundingBox& one, const AxisAlignedBoundingBox& two);

public:
    // Constructor
    AxisAlignedBoundingBox(double &x, double &y, double &width, double &height);
    AxisAlignedBoundingBox(double &&x, double &&y, double &&width, double &&height);

    // This friend function (A free function that can access private fields) should check if two AABBs overlap
    // It returns true if there is overlap, it returns false if there isn’t
    friend bool checkIfBoxContainsCorner(const AxisAlignedBoundingBox& one, const AxisAlignedBoundingBox& two);
    friend bool collides(const AxisAlignedBoundingBox& one, const AxisAlignedBoundingBox& two);

    // getters
    [[nodiscard]] double get_x() const;
    [[nodiscard]] double get_y() const;
    [[nodiscard]] double get_width() const;
    [[nodiscard]] double get_height() const;

    // Operators
    // Comparison Operator: Compare 2 AxisAlignedBoundingBoxes with each other
    bool operator==(const AxisAlignedBoundingBox& aabb) const;
    bool operator!=(const AxisAlignedBoundingBox& aabb) const;
    // Convert object to string
    explicit operator std::string() const;
};

#endif //LABO_7_AXIS_ALIGNED_BOUNDING_BOX_H
