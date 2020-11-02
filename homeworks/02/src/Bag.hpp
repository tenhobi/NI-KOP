#ifndef INC_01_BAG_HPP
#define INC_01_BAG_HPP


#include <utility>
#include <vector>
#include "Item.hpp"

class Bag {
public:
    Bag(std::vector<Item> items,
        unsigned long capacity,
        unsigned long minimalCost) : items(std::move(items)),
                                     capacity(capacity),
                                     minimalCost(minimalCost) {}

    std::vector<Item> items;
    unsigned long capacity;
    unsigned long minimalCost;
};


#endif //INC_01_BAG_HPP
