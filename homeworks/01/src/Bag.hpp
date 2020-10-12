//
// Created by the on 10/11/2020.
//

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

    const std::vector<Item> &getItems() const {
        return items;
    }

    unsigned long getCapacity() const {
        return capacity;
    }

    unsigned long getMinimalCost() const {
        return minimalCost;
    }

private:
    std::vector<Item> items;
    unsigned long capacity;
    unsigned long minimalCost;
};


#endif //INC_01_BAG_HPP
