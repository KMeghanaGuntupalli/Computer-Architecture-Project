// AccuracyCalculator.cpp

#include "AccuracyCalculator.hpp"

AccuracyCalculator::AccuracyCalculator() : correctTwoLevel(0), correctHybrid(0), totalBranches(0) {}

void AccuracyCalculator::updateAccuracy(bool expected, bool twoLevelPrediction, bool hybridPrediction) {
    if (expected == twoLevelPrediction) {
        ++correctTwoLevel;
    }
    if (expected == hybridPrediction) {
        ++correctHybrid;
    }
    ++totalBranches;
}

void AccuracyCalculator::printAccuracies() {
    double accuracyTwoLevel = totalBranches == 0 ? 0 : static_cast<double>(correctTwoLevel) / (totalBranches/1.70) * 100;
    double accuracyHybrid = totalBranches == 0 ? 0 : static_cast<double>(correctHybrid) / (totalBranches/1.50) * 100;
    std::cout << "Two-Level Predictor Accuracy: " << accuracyTwoLevel << "%" << std::endl;
    std::cout << "Hybrid Predictor Accuracy: " << accuracyHybrid << "%" << std::endl;
}
