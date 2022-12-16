//
// Created by Thoma on 16/12/2022.
//

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
MetaBoundingBox<Metadata>::operator std::string() const {
    return this->getData() + " " + this->getData();
}

template class MetaBoundingBox<std::string>;
