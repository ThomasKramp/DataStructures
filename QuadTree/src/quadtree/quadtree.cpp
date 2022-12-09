//
// Created by Thoma on 05/12/2022.
//

#include "quadtree/quadtree.h"

// https://github.com/alwex/QuadTree

template<> void Quadtree<std::string>::createSubZones() {
    double subX, subY;
    double subWidth = this->bounds.get_width() / 2;
    double subHeight = this->bounds.get_height() / 2;

    // NW Zone Declaration
    subX = this->bounds.get_x();
    subY = this->bounds.get_y() + subHeight;
    // this->subZones[this->REGION_NW] = AxisAlignedBoundingBox(subX, subY, subWidth, subHeight);

    // NE Zone Declaration
    subX = this->bounds.get_x() + subWidth;
    subY = this->bounds.get_y() + subHeight;
    // this->subZones[this->REGION_NE] = AxisAlignedBoundingBox(subX, subY, subWidth, subHeight);

    // SW Zone Declaration
    subX = this->bounds.get_x();
    subY = this->bounds.get_y();
    // this->subZones[this->REGION_SW] = AxisAlignedBoundingBox(subX, subY, subWidth, subHeight);

    // SE Zone Declaration
    subX = this->bounds.get_x() + subWidth;
    subY = this->bounds.get_y();
    // this->subZones[this->REGION_SE] = AxisAlignedBoundingBox(subX, subY, subWidth, subHeight);

    // this->subZones = {};
}