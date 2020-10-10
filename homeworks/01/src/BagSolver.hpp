#ifndef MI_PAA_BAGSOLVER_HPP
#define MI_PAA_BAGSOLVER_HPP

#include <utility>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "BagSolverMethod.hpp"
#include "DecisionResult.hpp"

class BagSolver
{
public:
    BagSolver(const unsigned long id,
              std::vector<std::pair<unsigned long, unsigned long>> bag,
              unsigned long bagCapacity,
              unsigned long minimalCost,
              const BagSolverMethod method)
            : id(id),
              bag(std::move(bag)),
              bagCapacity(bagCapacity),
              minimalCost(minimalCost),
              method(method)
    {
        clear();

        for (unsigned long i = 0; i < (unsigned long)this->bag.size(); ++i)
        {
            unsigned long sum = 0;
            for (unsigned j = i + 1; j < (unsigned)this->bag.size(); ++j)
            {
                sum += this->bag[j].second;
            }
            restOfCostGreaterThanIndex.push_back(sum);
        }
    }

    // Clears all run dependent data.
    void clear()
    {
        decisionNodesVisited = 0;
    }

    DecisionResult isSolvable(bool printOutput)
    {
        clear();

        // Because the Graph doesn't have 1 root node, we well call both children and then combine them.
        auto resultWith = decisionRecursion(0, bag[0].first, bag[0].second);
        auto resultWithout = decisionRecursion(0, 0, 0);
        auto result = resultWith + resultWithout;

        result.nodesVisited = this->decisionNodesVisited;

        std::string tmpMethod = (method == BagSolverMethod::BrutalForce ? "bf" : "bnb");
        std::string tmpIsSolvable = result.isSolvable ? "yes" : "no";

        if (printOutput)
        {
            std::cout << id << " (" << tmpMethod << ") = "
                      << tmpIsSolvable
                      << " with cost = " << result.cost
                      << ", nodes = " << result.nodesVisited
                      << std::endl;
        }

        return result;
    }

private:
    const unsigned long id;
    std::vector<std::pair<unsigned long, unsigned long>> bag;
    unsigned long bagCapacity;
    unsigned long minimalCost;
    const BagSolverMethod method = BagSolverMethod::BrutalForce;
    // Precalculated array of values meaning how much can the item get by adding all next items combined.
    std::vector<unsigned long> restOfCostGreaterThanIndex;
    unsigned long decisionNodesVisited = 0;

    /**
       * Makes a decision as to whether the items fit into the backpack.
       * Uses brutal force method.
       *
       * @param index actual index
       * @param weight weight of items before this one
       * @param cost cost of items before this one
       * @return bool
       */
    DecisionResult decisionRecursion(long index, unsigned long weight, unsigned long cost)
    {
        // out of bag items
        if ((unsigned)index >= bag.size())
        {
            throw std::invalid_argument("Index of bag is out of range.");
        }

        decisionNodesVisited++;

        // If the method is BnB:
        if (method == BagSolverMethod::BnB)
        {
            // bottom
            if (restOfCostGreaterThanIndex[index] + bag[index].second < minimalCost)
            {
                return {false, cost};
            }

            // up
            if (weight + bag[index].first > bagCapacity)
            {
                return {false, cost};
            }
        }

        // This is the last item.
        // Here is computed if the series of yes/no is valid for the given bag.
        if ((unsigned)index == (bag.size() - 1))
        {
            bool with, without;

            // If we add this item:
            with = ((weight + bag[index].first) <= bagCapacity) && ((cost + bag[index].second) >= minimalCost);
            DecisionResult withResult = {with, with ? cost + bag[index].second : 0};

            // If we not add this item:
            without = (weight <= bagCapacity) && (cost >= minimalCost);
            DecisionResult withoutResult = {without, without ? cost : 0};

            //        std::cout << "FINAL: "
            //                  << with << "||" << without << " "
            //                  << weight << "/" << bagCapacity << " "
            //                  << cost << ">=" << minimalCost << std::endl;

            return withResult + withoutResult;
        }

        // Adding current item.
        DecisionResult resultWith = decisionRecursion(index + 1,
                                                      weight + bag[index].first,
                                                      cost + bag[index].second);

        // Not adding current item.
        DecisionResult resultWithout = decisionRecursion(index + 1,
                                                         weight,
                                                         cost);

        return resultWith + resultWithout;
    }
};

#endif //MI_PAA_BAGSOLVER_HPP//
// Created by the on 10/14/2019.
//

#ifndef MI_PAA_BAGSOLVER_HPP
#define MI_PAA_BAGSOLVER_HPP

#include <utility>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "BagSolverMethod.hpp"
#include "DecisionResult.hpp"

class BagSolver
{
public:
  BagSolver(const unsigned long id,
            std::vector<std::pair<unsigned long, unsigned long>> bag,
            unsigned long bagCapacity,
            unsigned long minimalCost,
            const BagSolverMethod method)
      : id(id),
        bag(std::move(bag)),
        bagCapacity(bagCapacity),
        minimalCost(minimalCost),
        method(method)
  {
    clear();

    for (unsigned long i = 0; i < (unsigned long)this->bag.size(); ++i)
    {
      unsigned long sum = 0;
      for (unsigned j = i + 1; j < (unsigned)this->bag.size(); ++j)
      {
        sum += this->bag[j].second;
      }
      restOfCostGreaterThanIndex.push_back(sum);
    }
  }

  // Clears all run dependent data.
  void clear()
  {
    decisionNodesVisited = 0;
  }

  DecisionResult isSolvable(bool printOutput)
  {
    clear();

    // Because the Graph doesn't have 1 root node, we well call both children and then combine them.
    auto resultWith = decisionRecursion(0, bag[0].first, bag[0].second);
    auto resultWithout = decisionRecursion(0, 0, 0);
    auto result = resultWith + resultWithout;

    result.nodesVisited = this->decisionNodesVisited;

    std::string tmpMethod = (method == BagSolverMethod::BrutalForce ? "bf" : "bnb");
    std::string tmpIsSolvable = result.isSolvable ? "yes" : "no";

    if (printOutput)
    {
      std::cout << id << " (" << tmpMethod << ") = "
                << tmpIsSolvable
                << " with cost = " << result.cost
                << ", nodes = " << result.nodesVisited
                << std::endl;
    }

    return result;
  }

private:
  const unsigned long id;
  std::vector<std::pair<unsigned long, unsigned long>> bag;
  unsigned long bagCapacity;
  unsigned long minimalCost;
  const BagSolverMethod method = BagSolverMethod::BrutalForce;
  // Precalculated array of values meaning how much can the item get by adding all next items combined.
  std::vector<unsigned long> restOfCostGreaterThanIndex;
  unsigned long decisionNodesVisited = 0;

  /**
     * Makes a decision as to whether the items fit into the backpack.
     * Uses brutal force method.
     *
     * @param index actual index
     * @param weight weight of items before this one
     * @param cost cost of items before this one
     * @return bool
     */
  DecisionResult decisionRecursion(long index, unsigned long weight, unsigned long cost)
  {
    // out of bag items
    if ((unsigned)index >= bag.size())
    {
      throw std::invalid_argument("Index of bag is out of range.");
    }

    decisionNodesVisited++;

    // If the method is BnB:
    if (method == BagSolverMethod::BnB)
    {
      // bottom
      if (restOfCostGreaterThanIndex[index] + bag[index].second < minimalCost)
      {
        return {false, cost};
      }

      // up
      if (weight + bag[index].first > bagCapacity)
      {
        return {false, cost};
      }
    }

    // This is the last item.
    // Here is computed if the series of yes/no is valid for the given bag.
    if ((unsigned)index == (bag.size() - 1))
    {
      bool with, without;

      // If we add this item:
      with = ((weight + bag[index].first) <= bagCapacity) && ((cost + bag[index].second) >= minimalCost);
      DecisionResult withResult = {with, with ? cost + bag[index].second : 0};

      // If we not add this item:
      without = (weight <= bagCapacity) && (cost >= minimalCost);
      DecisionResult withoutResult = {without, without ? cost : 0};

      //        std::cout << "FINAL: "
      //                  << with << "||" << without << " "
      //                  << weight << "/" << bagCapacity << " "
      //                  << cost << ">=" << minimalCost << std::endl;

      return withResult + withoutResult;
    }

    // Adding current item.
    DecisionResult resultWith = decisionRecursion(index + 1,
                                                  weight + bag[index].first,
                                                  cost + bag[index].second);

    // Not adding current item.
    DecisionResult resultWithout = decisionRecursion(index + 1,
                                                     weight,
                                                     cost);

    return resultWith + resultWithout;
  }
};

#endif //MI_PAA_BAGSOLVER_HPP
