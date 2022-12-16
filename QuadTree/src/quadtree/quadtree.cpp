//
// Created by Thoma on 05/12/2022.
//

#include "quadtree/quadtree.h"

// https://github.com/alwex/QuadTree

// private
template<typename Metadata>
void Quadtree<Metadata>::createSubZones() {
    double subX, subY;
    double subWidth = this->bounds.get_width() / 2;
    double subHeight = this->bounds.get_height() / 2;

    // NW Zone Declaration
    subX = this->bounds.get_x();
    subY = this->bounds.get_y() + subHeight;
    auto bounds = AxisAlignedBoundingBox(subX, subY, subWidth, subHeight);
    subZones.push_back(Quadtree<Metadata>(bounds, this->region_capacity));

    // NE Zone Declaration
    subX = this->bounds.get_x() + subWidth;
    subY = this->bounds.get_y() + subHeight;
    bounds = AxisAlignedBoundingBox(subX, subY, subWidth, subHeight);
    subZones.push_back(Quadtree<Metadata>(bounds, this->region_capacity));

    // SW Zone Declaration
    subX = this->bounds.get_x();
    subY = this->bounds.get_y();
    bounds = AxisAlignedBoundingBox(subX, subY, subWidth, subHeight);
    subZones.push_back(Quadtree<Metadata>(bounds, this->region_capacity));

    // SE Zone Declaration
    subX = this->bounds.get_x() + subWidth;
    subY = this->bounds.get_y();
    bounds = AxisAlignedBoundingBox(subX, subY, subWidth, subHeight);
    subZones.push_back(Quadtree<Metadata>(bounds, this->region_capacity));
}

template<typename Metadata>
void Quadtree<Metadata>::insertToSubZone(const AxisAlignedBoundingBox &newBox, const Metadata &meta) {
    for (auto& zone: subZones) {
        if (collides(zone.bounds, newBox)) {
            zone.insert(newBox, meta);
        }
    }
}

// public
// - constructors
template<typename Metadata>
Quadtree<Metadata>::Quadtree(const AxisAlignedBoundingBox &bounds, unsigned int region_capacity): bounds(bounds), region_capacity(region_capacity) {};

template<typename MetadataType>
Quadtree<MetadataType> &Quadtree<MetadataType>::operator=(Quadtree<MetadataType> &&other) {
    this->bounds = std::move(other.bounds);
    this->region_capacity = std::move(other.region_capacity);
    this->abBoxes = std::move(other.abBoxes);
    this->subZones = std::move(other.subZones);
    return *this;
}

template<typename Metadata>
Quadtree<Metadata>::Quadtree(const Quadtree<Metadata> &other): bounds(other.bounds),
                                                               region_capacity(other.region_capacity), abBoxes(other.abBoxes), subZones(other.subZones) { }

// - methods
template<typename Metadata>
void Quadtree<Metadata>::insert(const AxisAlignedBoundingBox &newBox, const Metadata &meta) {
    // TODO: add collision detection

    if (subZones.empty() && abBoxes.size() < region_capacity) {
        abBoxes.emplace_back(newBox, meta);
    } else {
        if (subZones.empty()) {
            createSubZones();
            for (auto &abBox: abBoxes) { insertToSubZone(abBox.first, abBox.second); }
            abBoxes.clear();
        }
        insertToSubZone(newBox, meta);
        // in qich square does the box need to be put into
    }
}

// TODO: Make pair vector || Create hash function for AxisAlignedBoundingBox || Create object for pair && Add operator
//       Remove pointer
template<typename Metadata>
std::unordered_set<std::pair<AxisAlignedBoundingBox, Metadata>*> Quadtree<Metadata>
        ::query_region(const AxisAlignedBoundingBox &container) {
    std::unordered_set<std::pair<AxisAlignedBoundingBox, Metadata>*> boxes = std::unordered_set<std::pair<AxisAlignedBoundingBox, Metadata>*>();
    if (subZones.empty()) {
        // If there aren't any sub-zones loop through all boxes
        for (auto &abBox: abBoxes) {
            // Add the box if there is a collision
            if (collides(abBox.first, container)) {
                boxes.insert(&abBox);
            }
        }
    } else {
        // If there are sub-zones loop through all sub-zones
        for (auto &zone: subZones) {
            // Look into sub-zone if there is a collision
            if (collides(zone.getBounds(), container)) {
                // Get all colliding boxes in sub-zone
                auto zone_boxes = zone.query_region(container);
                // Add all the colliding boxes
                for (auto &zone_box: zone_boxes) { boxes.insert(zone_box); }
            }
        }
    }
    return boxes;
}

// - getters
template<typename Metadata>
AxisAlignedBoundingBox Quadtree<Metadata>::getBounds() { return this->bounds; }

template<typename Metadata>
auto Quadtree<Metadata>::begin() {
    auto boxes = query_region(this->bounds);
    return boxes.begin();
}

template<typename Metadata>
auto Quadtree<Metadata>::end() {
    auto boxes = query_region(this->bounds);
    return boxes.end();
}

template class Quadtree<std::string>;
