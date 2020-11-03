#ifndef INC_01_BFSOLVER_HPP
#define INC_01_BFSOLVER_HPP


#include <stack>
#include <utility>
#include "Solver.hpp"


class BfSolver : public Solver {
public:
    explicit BfSolver(Bag &bag) : Solver(bag) {}

    void solve() override {
        bestCost = 0;
        result = bfRecursion(-1, 0, 0, calculateBestBagEstimate());
    }

    void print() override {
        std::cout << bag.id << " " << bag.n << " " << result.cost;

        while (!result.items.empty()) {
            std::cout << " " << (result.items.top() ? "1" : "0");
            result.items.pop();
        }

        std::cout << std::endl;
    }

private:
    unsigned long bestCost = 0;

    class BfResult {
    public:
        BfResult(bool isValid,
                 unsigned long cost,
                 unsigned long weight,
                 std::stack<bool> items) : isValid(isValid),
                                           cost(cost),
                                           weight(weight),
                                           items(std::move(items)) {}

        bool isValid;
        unsigned long cost;
        unsigned long weight;
        std::stack<bool> items;
    };

    BfResult _nonValidResult = BfResult(false, 0, 0, std::stack<bool>());

    BfResult result = _nonValidResult;

    BfResult mergeBfResults(const BfResult& first, const BfResult& second, bool& firstIsUsed) {
        bool isValid = false;
        bool useFirst = false;

        if (first.isValid && second.isValid) {
            isValid = true;
            if (first.cost > second.cost) {
                useFirst = true;
            }
        } else if (first.isValid && !second.isValid) {
            isValid = true;
            useFirst = true;
        } else if (!first.isValid && second.isValid) {
            isValid = true;
            useFirst = false;
        }

        firstIsUsed = useFirst;

        if (isValid) {
            return useFirst ? first : second;
        }

        return _nonValidResult;
    }

    BfResult bfRecursion(long level, unsigned long weight, unsigned long cost, unsigned long costEstimate) {
        Item currentItem = Item(0, 0);

        if (level != -1) {
            currentItem = bag.items.at(level);
        }

        // Check last item
        if ((unsigned long) (level) == (bag.items.size() - 1)) {
            std::stack<bool> stack;

            // with
            if ((weight + bag.items.at(level).getWeight()) <= bag.capacity) {
                if ((cost + bag.items.at(level).getCost()) >= bestCost) {
                    bestCost = cost + bag.items.at(level).getCost();
                }

                stack.push(true);

                return BfResult(true,
                                cost + bag.items.at(level).getCost(),
                                weight + bag.items.at(level).getWeight(),
                                stack);
            } else if (weight <= bag.capacity) {
                if (cost >= bestCost) {
                    bestCost = cost;
                }

                stack.push(false);
                return BfResult(true,
                                cost,
                                weight,
                                stack);
            }

            return BfResult(false, 0, 0, stack);
        }

        // with current item
        auto with = bfRecursion(level + 1,
                                weight + currentItem.getWeight(),
                                cost + currentItem.getCost(),
                                costEstimate - currentItem.getCost());

        // without current item
        auto without = bfRecursion(level + 1,
                                   weight,
                                   cost,
                                   costEstimate - currentItem.getCost());

        bool mergeUsingWith = false;
        auto merged = mergeBfResults(with, without, mergeUsingWith);

        if (level != -1 && merged.isValid) {
            merged.items.push(mergeUsingWith);
        }

        return merged;
    }
};


#endif //INC_01_BFSOLVER_HPP
