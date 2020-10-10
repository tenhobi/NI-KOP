//
// Created by the on 10/14/2019.
//

#ifndef MI_PAA_DECISIONRESULT_HPP
#define MI_PAA_DECISIONRESULT_HPP

class DecisionResult
{
public:
    const bool isSolvable;
    const unsigned cost;
    unsigned long nodesVisited = 0;

    DecisionResult(const bool isSolvable, const unsigned long cost) : isSolvable(isSolvable),
                                                                      cost(cost) {}

    DecisionResult operator+(DecisionResult &other) const
    {
        bool tmpIsSolvable = false;
        unsigned long tmpCost = 0;

        if (isSolvable && other.isSolvable)
        {
            tmpIsSolvable = true;
            if (cost > other.cost)
            {
                tmpCost = cost;
            }
            else
            {
                tmpCost = other.cost;
            }
        }
        else if (isSolvable && !other.isSolvable)
        {
            tmpIsSolvable = true;
            tmpCost = cost;
        }
        else if (!isSolvable && other.isSolvable)
        {
            tmpIsSolvable = true;
            tmpCost = other.cost;
        }
        else if (!isSolvable && !other.isSolvable)
        {
            tmpIsSolvable = false;
            tmpCost = 0;
        }

        return {tmpIsSolvable, tmpCost};
    }
};

#endif //MI_PAA_DECISIONRESULT_HPP
