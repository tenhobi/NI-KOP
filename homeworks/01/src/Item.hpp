//
// Created by the on 10/11/2020.
//

#ifndef INC_01_ITEM_HPP
#define INC_01_ITEM_HPP

class Item {
public:
    explicit Item(unsigned long weight, unsigned long cost) : weight(weight), cost(cost) {}

    unsigned long getWeight() const {
        return weight;
    }

    unsigned long getCost() const {
        return cost;
    }

private:
    unsigned long weight;
    unsigned long cost;
};

#endif //INC_01_ITEM_HPP
