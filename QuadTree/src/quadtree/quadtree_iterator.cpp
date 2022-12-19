//
// Created by Thoma on 09/12/2022.
//

#include "quadtree/quadtree_iterator.h"

template<typename Metadata>
QuadtreeIterator<Metadata> &QuadtreeIterator<Metadata>::operator++() {
    this->index++;
    return *this;
}

template<typename Metadata>
MetaBoundingBox<Metadata>* QuadtreeIterator<Metadata>::operator*() {
    return (this->boxes.data() + this->index);
}

template<typename Metadata>
bool QuadtreeIterator<Metadata>::operator==(const QuadtreeIterator &qit) {
    return this->index == qit.index;
}

template<typename Metadata>
bool QuadtreeIterator<Metadata>::operator!=(const QuadtreeIterator &qit) {
    return this->index != qit.index;
}

template<typename Metadata>
QuadtreeIterator<Metadata>::QuadtreeIterator(std::unordered_set<MetaBoundingBox<Metadata>> boxes, std::size_t index) : boxes() {
    std::copy(boxes.begin(), boxes.end(), std::back_inserter(this->boxes));
    this->index = index;
}

template class QuadtreeIterator<std::string>;