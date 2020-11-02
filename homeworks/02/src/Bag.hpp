#ifndef INC_01_BAG_HPP
#define INC_01_BAG_HPP


#include <utility>
#include <vector>
#include "Item.hpp"

class Bag {
public:
    Bag(long id,
        long n,
        std::vector<Item> items,
        unsigned long capacity) : id(id),
                                  n(n),
                                  items(std::move(items)),
                                  capacity(capacity) {}

    long id;
    long n;
    std::vector<Item> items;
    unsigned long capacity;
};


#endif //INC_01_BAG_HPP
