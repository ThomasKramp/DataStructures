//
// Created by Thoma on 09/12/2022.
//

#ifndef LABO_7_QUADTREE_ITERATOR_H
#define LABO_7_QUADTREE_ITERATOR_H

#include <vector>
#include "meta_bounding_box.h"

// TODO: Vraag aan de prof
//       Heeft te  maken met de begin() & end() methodes
template <typename Metadata>
class QuadtreeIterator {
private:
    std::vector<MetaBoundingBox<Metadata>> boxes;
    std::size_t index = 0;

    QuadtreeIterator& operator++ ();
    QuadtreeIterator operator==(const QuadtreeIterator& qit);

public:

};


#endif //LABO_7_QUADTREE_ITERATOR_H
