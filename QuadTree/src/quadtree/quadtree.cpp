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
    auto bounds = AxisAlignedBoundingBox(subX, subY, subWidth, subHeight);
    subZones.push_back(Quadtree<MetadataType>(bounds, this->region_capacity));

    // NE Zone Declaration
    subX = this->bounds.get_x() + subWidth;
    subY = this->bounds.get_y() + subHeight;
    bounds = AxisAlignedBoundingBox(subX, subY, subWidth, subHeight);
    subZones.push_back(Quadtree<MetadataType>(bounds, this->region_capacity));

    // SW Zone Declaration
    subX = this->bounds.get_x();
    subY = this->bounds.get_y();
    bounds = AxisAlignedBoundingBox(subX, subY, subWidth, subHeight);
    subZones.push_back(Quadtree<MetadataType>(bounds, this->region_capacity));

    // SE Zone Declaration
    subX = this->bounds.get_x() + subWidth;
    subY = this->bounds.get_y();
    bounds = AxisAlignedBoundingBox(subX, subY, subWidth, subHeight);
    subZones.push_back(Quadtree<MetadataType>(bounds, this->region_capacity));
}

template<typename MetadataType>
void Quadtree<MetadataType>::insertToSubZone(const AxisAlignedBoundingBox aabbBox, const MetadataType &meta) {
    for (auto& zone: subZones) {
        if (collides(zone.bounds, aabbBox)) {
            zone.insert(aabbBox, meta);
        }
    }
}

// public
template<typename MetadataType>
Quadtree<MetadataType>::Quadtree(const AxisAlignedBoundingBox &bounds, unsigned int region_capacity): bounds(bounds), region_capacity(region_capacity) {};

template<typename MetadataType>
Quadtree<MetadataType> &Quadtree<MetadataType>::operator=(Quadtree<MetadataType> &&other) {
    this->bounds = std::move(other.bounds);
    this->region_capacity = std::move(other.region_capacity);
    this->abBoxes = std::move(other.abBoxes);
    this->subZones = std::move(other.subZones);
    return *this;
}

template<typename MetadataType>
Quadtree<MetadataType>::Quadtree(const Quadtree<MetadataType> &other): bounds(other.bounds),
region_capacity(other.region_capacity), abBoxes(other.abBoxes), subZones(other.subZones) { }

template<typename MetadataType>
void Quadtree<MetadataType>::insert(const AxisAlignedBoundingBox &aabb, const MetadataType &meta) {
    // TODO: add collision detection

    if (abBoxes.size() < region_capacity && subZones.empty()) {
        abBoxes.emplace_back(aabb, meta);
    } else {
        if (subZones.empty()) {
            createSubZones();
            for (auto &abBox: abBoxes) { insertToSubZone(abBox.first, abBox.second); }
            abBoxes.clear();
        }
        insertToSubZone(aabb, meta);
        // in qich square does the box need to be put into
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
template void Quadtree<std::string>::insertToSubZone(const AxisAlignedBoundingBox aabbBox, const std::string &meta);

// public
template Quadtree<std::string>::Quadtree(const AxisAlignedBoundingBox &bounds, unsigned int region_capacity);
template Quadtree<std::string> &Quadtree<std::string>::operator=(Quadtree<std::string> &&other);
template Quadtree<std::string>::Quadtree(const Quadtree<std::string> &other);

template void Quadtree<std::string>::insert(const AxisAlignedBoundingBox &aabb, const std::string &meta);

template auto Quadtree<std::string>::begin();
template auto Quadtree<std::string>::end();
