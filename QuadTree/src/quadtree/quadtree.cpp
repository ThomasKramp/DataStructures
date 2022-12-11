//
// Created by Thoma on 05/12/2022.
//

#include "quadtree/quadtree.h"

// https://github.com/alwex/QuadTree

// private
template<typename MetadataType>
void Quadtree<MetadataType>::createSubZones() {
    double subX, subY;
    double subWidth = this->bounds.get_width() / 2;
    double subHeight = this->bounds.get_height() / 2;

    // NW Zone Declaration
    subX = this->bounds.get_x();
    subY = this->bounds.get_y() + subHeight;
    this->subZones[this->REGION_NW] = Quadtree<MetadataType>(AxisAlignedBoundingBox(subX, subY, subWidth, subHeight), this->region_capacity);

    // NE Zone Declaration
    subX = this->bounds.get_x() + subWidth;
    subY = this->bounds.get_y() + subHeight;
    this->subZones[this->REGION_NE] = Quadtree<MetadataType>(AxisAlignedBoundingBox(subX, subY, subWidth, subHeight), this->region_capacity);

    // SW Zone Declaration
    subX = this->bounds.get_x();
    subY = this->bounds.get_y();
    this->subZones[this->REGION_SW] = Quadtree<MetadataType>(AxisAlignedBoundingBox(subX, subY, subWidth, subHeight), this->region_capacity);

    // SE Zone Declaration
    subX = this->bounds.get_x() + subWidth;
    subY = this->bounds.get_y();
    this->subZones[this->REGION_SE] = Quadtree<MetadataType>(AxisAlignedBoundingBox(subX, subY, subWidth, subHeight), this->region_capacity);
}

// public
template<typename MetadataType>
Quadtree<MetadataType>::Quadtree(const AxisAlignedBoundingBox &bounds, unsigned int region_capacity): bounds(bounds), region_capacity(region_capacity) {};

template<typename MetadataType>
void Quadtree<MetadataType>::insert(const AxisAlignedBoundingBox &aabb, const MetadataType &meta) {
    // TODO: Add meta to vector
    if (abBoxes.size() < region_capacity) {
        abBoxes.push_back(aabb);
    } else {
        if (subZones == 0) { createSubZones(); }
    }
}

template<typename MetadataType>
auto Quadtree<MetadataType>::begin() {
    return nullptr;
}

template<typename MetadataType>
auto Quadtree<MetadataType>::end() {
    return nullptr;
}


// private
template void Quadtree<std::string>::createSubZones();

// public
template Quadtree<std::string>::Quadtree(const AxisAlignedBoundingBox &bounds, unsigned int region_capacity);
template void Quadtree<std::string>::insert(const AxisAlignedBoundingBox &aabb, const std::string &meta);

template auto Quadtree<std::string>::begin();
template auto Quadtree<std::string>::end();
