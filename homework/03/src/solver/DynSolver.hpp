#ifndef INC_01_DYNSOLVER_HPP
#define INC_01_DYNSOLVER_HPP


#include <utility>
#include <string>
#include <climits>
#include "Solver.hpp"


class DynSolver : public Solver {
public:
    explicit DynSolver(Bag &bag) : Solver(bag) {}

    void solve() override {
        solveDyn();
    }

    void print() override {
        std::cout << bag.id << " " << bag.n << " " << resultCost;

        for (auto &&item : itemsFlag) {
            std::cout << " " << (item ? "1" : "0");
        }

        std::cout << std::endl;
    }

protected:
    std::vector<bool> itemsFlag;
    unsigned long resultCost = 0;
    unsigned long resultWeight = 0;

    void solveDyn() {
        // == number of items
        unsigned long totalColumns = bag.items.size();
        // == max possible cost
        unsigned long totalRows = 1; // + "0"
        unsigned long weight = 0;
        unsigned long cost = 0;

        for (auto &item : bag.items) {
            totalRows += item.getCost();
        }

        // Create table
        // table[ i * (totalRows) + j] == "table[i][j]" == "table[row][column]"
        auto *table = new unsigned long[totalRows * totalColumns];
        // auto **table = new unsigned long*[totalRows];

        // Fill w/ dummy values
        std::fill(table, table + totalRows * totalColumns, ULONG_MAX);

        // w/ first item
        if (bag.items[0].getCost() != 0) {
            table[bag.items[0].getCost()] = bag.items[0].getWeight();
        }
        // w/o first item
        table[0] = 0;

        // CALCULATE

        // Starts at 1 'cause 0 is trivially done above
        for (unsigned long column = 1; column < totalColumns; column++) {
            unsigned long previousColumn = column - 1;
            unsigned long columnWeight = bag.items[column].getWeight();
            unsigned long columnCost = bag.items[column].getCost();

            for (unsigned long row = 0; row < totalRows; row++) {
                // Duplicate "left" item
                table[column * totalRows + row] = table[previousColumn * totalRows + row];

                // Compare "left bottom" item
                if (bag.items[column].getCost() <= row
                    && table[previousColumn * totalRows + row - columnCost] != ULONG_MAX
                    && table[previousColumn * totalRows + row - columnCost] + columnWeight <
                       table[column * totalRows + row]
                        ) {
                    table[column * totalRows + row] =
                            table[previousColumn * totalRows + row - columnCost] + columnWeight;
                }
            }
        }

        itemsFlag = std::vector<bool>();
        for (auto &item : bag.items) {
            std::ignore = item;
            itemsFlag.push_back(false);
        }

        // RESULT

        unsigned long lastColumn = totalColumns - 1;

        for (unsigned long i = totalRows - 1; i >= 0; i--) {
            if (bag.capacity >= table[lastColumn * totalRows + i]) {
                weight = table[lastColumn * totalRows + i];
                cost = i;
                break;
            }
        }

        // ITEMS USED

        unsigned long tmp = cost;

        for (unsigned long i = totalColumns - 1; i >= 0; i--) {
            if (i != 0
                && table[(i - 1) * totalRows + tmp] != table[i * totalRows + tmp]
                    ) {
                tmp -= bag.items[i].getCost();
                itemsFlag[i] = true;
            }

            if (i == 0) {
                if (tmp != 0) {
                    itemsFlag[0] = true;
                }
                break;
            }
        }

        delete[] table;
        resultCost = cost;
        resultWeight = weight;
    }
};


#endif //INC_01_DYNSOLVER_HPP
