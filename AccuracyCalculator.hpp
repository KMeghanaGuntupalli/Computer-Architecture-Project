// AccuracyCalculator.hpp

#ifndef ACCURACY_CALCULATOR_HPP
#define ACCURACY_CALCULATOR_HPP

#include <iostream>

class AccuracyCalculator {
private:
    int correctTwoLevel;
    int correctHybrid;
    int totalBranches;
    int probabilityaccuracy;

public:
    AccuracyCalculator();
    void updateAccuracy(bool expected, bool twoLevelPrediction, bool hybridPrediction);
    void printAccuracies();
};

#endif // ACCURACY_CALCULATOR_HPP
