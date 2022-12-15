//
// Created by Thoma on 05/12/2022.
//

#ifndef LABO_7_QUADTREE_H
#define LABO_7_QUADTREE_H

#include <unordered_set>
#include <vector>
#include "quadtree/axis_aligned_bounding_box.h"
#include "quadtree/quadtree.h"

// This class is our actual quadtree
// It stores AABB’s together with some metadata
// Space Complexity: O(N)
template <typename MetadataType>
class Quadtree {
private:
    AxisAlignedBoundingBox bounds;
    unsigned int region_capacity;
    std::vector<std::pair<AxisAlignedBoundingBox, MetadataType>> abBoxes = std::vector<std::pair<AxisAlignedBoundingBox, MetadataType>>();
    // https://stackoverflow.com/a/3571746
    std::vector<Quadtree<MetadataType>> subZones = { };

    void createSubZones();
    void insertToSubZone(const AxisAlignedBoundingBox& newBox, const MetadataType &meta);

public:
    // Constructor
    // `bounds` specifies the edges of the region that the quadtree covers.
    // `region_capacity` specifies the maximum number of objects in a single region.
    Quadtree(const AxisAlignedBoundingBox& bounds, unsigned int region_capacity);
    Quadtree<MetadataType>& operator=(Quadtree<MetadataType>&& other);
    Quadtree(const Quadtree<MetadataType>& other);

    // This method inserts the given metadata and AABB into the quadtree.
    void insert(const AxisAlignedBoundingBox& newBox, const MetadataType& meta);

    // This method should return a std::unordered_set of all items inside the given AABB.
    // The given AABB may span multiple square regions of the quadtree.
    // The worst-case time-complexity of this method should be O(log(N)) for a Quadtree with N leaf nodes
    // TODO: You should decide the element type of the std::unordered_set
    // Your set should contain the AABB and the Metadata of all objects in the given region.
    // https://stackoverflow.com/q/62869571
    std::unordered_set<std::pair<AxisAlignedBoundingBox, MetadataType>*> query_region(const AxisAlignedBoundingBox& container);

    AxisAlignedBoundingBox getBounds();

    // TODO: You should decide the return type for this method
    // This method should return an iterator that runs over every element in the quadtree.
    auto begin();

    // TODO: You should decide the return type for this method
    // This method should return an iterator pointing one past the last element in the quadtree.
    // When iterating from begin() to end(), we should visit all elements in the quadtree.
    // There is no requirement with regards to the order that you visit these elements in.
    auto end();
};

#endif //LABO_7_QUADTREE_H
