#ifndef INC_01_SOLVERRESULT_HPP
#define INC_01_SOLVERRESULT_HPP


class SolverResult {
public:
    SolverResult(double averageTime, double maxTime) : averageTime(averageTime), maxTime(maxTime) {}

    double getAverageTime() const {
        return averageTime;
    }

    double getMaxTime() const {
        return maxTime;
    }

private:
    double averageTime;
    double maxTime
};


#endif //INC_01_SOLVERRESULT_HPP
