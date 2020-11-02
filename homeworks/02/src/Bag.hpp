#ifndef INC_01_BAG_HPP
#define INC_01_BAG_HPP


#include <utility>
#include <vector>
#include "Item.hpp"

class Bag {
public:
    Bag(long id,
        std::vector<Item> items,
        unsigned long capacity) : id(id),
                                  items(std::move(items)),
                                  capacity(capacity) {}

    long id;
    std::vector<Item> items;
    unsigned long capacity;
};


#endif //INC_01_BAG_HPP
