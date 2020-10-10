//
// Created by the on 10/10/2020.
//

#ifndef INC_01_STRATEGY_HPP
#define INC_01_STRATEGY_HPP


class Strategy {
public:
    virtual void process() {};
    bool isConfigurationPossible;

    explicit Strategy(bool isConfigurationPossible) : isConfigurationPossible(isConfigurationPossible) {}
private:

};


#endif //INC_01_STRATEGY_HPP
