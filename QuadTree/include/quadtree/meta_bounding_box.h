//
// Created by Thoma on 16/12/2022.
//

#ifndef LABO_7_META_BOUNDING_BOX_H
#define LABO_7_META_BOUNDING_BOX_H

#include "axis_aligned_bounding_box.h"

template <typename Metadata>
class MetaBoundingBox {
private:
    AxisAlignedBoundingBox aabb;
    Metadata meta;

public:
    // Constructors
    MetaBoundingBox(AxisAlignedBoundingBox aabb, Metadata meta);

    // Getters
    AxisAlignedBoundingBox getBox() const;
    Metadata getData() const;

    // Operators
    // Comparison Operator: Compare 2 MetaBoundingBoxes with each other
    bool operator==(const MetaBoundingBox<Metadata>& metaBox) const;
    // Convert object to string
    explicit operator std::string() const;
};

#endif //LABO_7_META_BOUNDING_BOX_H
