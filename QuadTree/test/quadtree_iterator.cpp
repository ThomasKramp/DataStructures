//
// Created by Thoma on 07/12/2022.
//

#include "catch2/catch.hpp"
#include "quadtree/quadtree_iterator.h"

TEST_CASE("Compare 2 iterators (same)"  "[operator] [comparison]") {
    // Create boxes
    MetaBoundingBox<std::string> box1 = MetaBoundingBox<std::string>(AxisAlignedBoundingBox(1, 2, 3, 4), "box");
    MetaBoundingBox<std::string> box2 = MetaBoundingBox<std::string>(AxisAlignedBoundingBox(5, 6, 7, 8), "box");

    // Insert boxes
    std::unordered_set<MetaBoundingBox<std::string>> boxes = std::unordered_set<MetaBoundingBox<std::string>>();
    boxes.insert(box1);
    boxes.insert(box2);

    // Create iterator
    QuadtreeIterator iterator = QuadtreeIterator(boxes, 0);
    MetaBoundingBox<std::string>* iteratorBox = *iterator;

    CHECK(*iteratorBox == box2);
}

TEST_CASE("Compare 2 iterators (different)"  "[operator] [comparison]") {
    // Create boxes
    MetaBoundingBox<std::string> box1 = MetaBoundingBox<std::string>(AxisAlignedBoundingBox(1, 2, 3, 4), "box");
    MetaBoundingBox<std::string> box2 = MetaBoundingBox<std::string>(AxisAlignedBoundingBox(5, 6, 7, 8), "box");

    // Insert boxes
    std::unordered_set<MetaBoundingBox<std::string>> boxes = std::unordered_set<MetaBoundingBox<std::string>>();
    boxes.insert(box1);
    boxes.insert(box2);

    // Create iterator
    QuadtreeIterator iterator = QuadtreeIterator(boxes, 0);
    MetaBoundingBox<std::string>* iteratorBox = *iterator;

    CHECK(*iteratorBox != box1);
}

TEST_CASE("Iterate iterator"  "[operator] [iterate]") {
    // Create boxes
    MetaBoundingBox<std::string> box1 = MetaBoundingBox<std::string>(AxisAlignedBoundingBox(1, 2, 3, 4), "box");
    MetaBoundingBox<std::string> box2 = MetaBoundingBox<std::string>(AxisAlignedBoundingBox(5, 6, 7, 8), "box");

    // Insert boxes
    std::unordered_set<MetaBoundingBox<std::string>> boxes = std::unordered_set<MetaBoundingBox<std::string>>();
    boxes.insert(box1);
    boxes.insert(box2);

    // Create iterator
    QuadtreeIterator iterator = QuadtreeIterator(boxes, 0);
    ++iterator;
    MetaBoundingBox<std::string>* iteratorBox = *iterator;

    CHECK(*iteratorBox == box1);
}