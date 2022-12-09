//
// Created by Thoma on 05/12/2022.
//

#ifndef LABO_7_QUADTREE_H
#define LABO_7_QUADTREE_H

#include <unordered_set>
#include <vector>
#include "quadtree/axis_aligned_bounding_box.h"

// This class is our actual quadtree
// It stores AABB’s together with some metadata
// Space Complexity: O(N)
template <typename MetadataType>
class Quadtree {
    // This was the solution to lab-4' problem
    // bool operator==(const Quadtree &Quadtree) const;

private:
    const AxisAlignedBoundingBox bounds;
    unsigned int region_capacity;
    std::vector<AxisAlignedBoundingBox> aabbBoxes = std::vector<AxisAlignedBoundingBox>();
    // Quadtree<MetadataType> subZones[4] = {};

    // https://github.com/alwex/QuadTree/blob/master/src/main/java/com/alwex/tree/QuadTree.java
    // Create an enum that specifies the sub-zones
    const uint8_t REGION_SELF = -1;
    const uint8_t REGION_NW = 0;
    const uint8_t REGION_NE = 1;
    const uint8_t REGION_SW = 2;
    const uint8_t REGION_SE = 3;

    void createSubZones();

public:
    // Constructor
    // `bounds` specifies the edges of the region that the quadtree covers.
    // `region_capacity` specifies the maximum number of objects in a single region.
    Quadtree(const AxisAlignedBoundingBox& bounds, unsigned int region_capacity);

    // This method inserts the given metadata and AABB into the quadtree.
    void insert(const AxisAlignedBoundingBox& aabb, const MetadataType& meta);

    // This method should return a std::unordered_set of all items inside the given AABB.
    // The given AABB may span multiple square regions of the quadtree.
    // The worst-case time-complexity of this method should be O(log(N)) for a Quadtree with N leaf nodes
    // TODO: You should decide the element type of the std::unordered_set
    // Your set should contain the AABB and the Metadata of all objects in the given region.
    /////////std::unordered_set<> query_region(const AxisAlignedBoundingBox& aabb);

    // TODO: You should decide the return type for this method
    // This method should return an iterator that runs over every element in the quadtree.
    auto begin();

    // TODO: You should decide the return type for this method
    // This method should return an iterator pointing one past the last element in the quadtree.
    // When iterating from begin() to end(), we should visit all elements in the quadtree.
    // There is no requirement with regards to the order that you visit these elements in.
    auto end();
};

template<>
Quadtree<std::string>::Quadtree(const AxisAlignedBoundingBox &bounds, unsigned int region_capacity): bounds(bounds), region_capacity(region_capacity) {}

template<>
void Quadtree<std::string>::insert(const AxisAlignedBoundingBox &aabb, const std::string &meta) {

}

/*template<typename MetadataType>
std::unordered_set<> Quadtree<MetadataType>::query_region(const AxisAlignedBoundingBox &aabb) {
    return nullptr;
}*/

template<>
auto Quadtree<std::string>::begin() {
    return nullptr;
}

template<>
auto Quadtree<std::string>::end() {
    return nullptr;
}

#endif //LABO_7_QUADTREE_H
