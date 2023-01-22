//
// Created by Thoma on 16/12/2022.
//

#include <valarray>
#include <iostream>
#include "quadtree/meta_bounding_box.h"

template<typename Metadata>
MetaBoundingBox<Metadata>::MetaBoundingBox(AxisAlignedBoundingBox aabb, Metadata meta): aabb(aabb), meta(meta) {}

template<typename Metadata>
AxisAlignedBoundingBox MetaBoundingBox<Metadata>::getBox() const { return this->aabb; }

template<typename Metadata>
Metadata MetaBoundingBox<Metadata>::getData() const { return this->meta; }

template<typename Metadata>
bool MetaBoundingBox<Metadata>::operator==(const MetaBoundingBox<Metadata> &metaBox) const {
    return (this->aabb == metaBox.getBox()) && (this->meta == metaBox.getData());
}

template<typename Metadata>
bool MetaBoundingBox<Metadata>::operator!=(const MetaBoundingBox<Metadata> &metaBox) const {
    return (this->aabb != metaBox.getBox()) || (this->meta != metaBox.getData());
}

template<typename Metadata>
MetaBoundingBox<Metadata>::operator std::string() const {
    return static_cast<std::string>(this->getBox()) + " " + this->getData();
}

// Hashing
namespace std { // add to the std library
    template<typename Metadata>
    std::size_t std::hash<MetaBoundingBox<Metadata>>::operator() (const MetaBoundingBox<Metadata>& key) const noexcept {
        int64_t H = 0;
        // Create double value based on aabb box values
        auto box = key.getBox();
        auto center_x = (box.get_x() + box.get_width()) / 2;
        auto center_y = (box.get_y() + box.get_height()) / 2;
        auto center_z = std::sqrt(std::pow(center_x, 2) + std::pow(center_y, 2));

        // Give y values a higher weight
        auto weight = box.get_x() + box.get_width() + (box.get_y() + box.get_height()) * 16;

        // Create hashers
        auto doubleHasher = std::hash<double>();
        auto metaHasher = std::hash<Metadata>();
        metaHasher(key.getData());

        // Combine hashes
        // std::cout << doubleHasher(center_z) << "\n";
        // std::cout << doubleHasher(weight) << "\n";
        H = H xor doubleHasher(center_z) xor doubleHasher(weight); //xor metaHasher(key.getData());
        return H;
    }
}

template class MetaBoundingBox<std::string>;
template std::size_t std::hash<MetaBoundingBox<std::string>>::operator() (const MetaBoundingBox<std::string>& key) const noexcept;

