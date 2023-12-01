// main.cpp

/*#include <iostream>
#include <vector>
#include <cstdlib> // For rand()
#include <iomanip> // For std::hex
#include "TwoLevelBranchPredictor.hpp"
#include "HybridBranchPredictor.hpp"
#include "AccuracyCalculator.hpp"

void simulateWorkload(const std::vector<std::pair<int, std::pair<bool, bool> > >& userInputs, TwoLevelBranchPredictor& twoLevelPredictor, HybridBranchPredictor& hybridPredictor, AccuracyCalculator& accuracyCalculator) {
    for (const auto& input : userInputs) {
        int address = input.first;
        bool actualOutcome = input.second.first;
        bool expectedOutcome = input.second.second;

        bool twoLevelPrediction = twoLevelPredictor.predict();
        bool hybridPrediction = hybridPredictor.predict();

        // Print values of Two-Level and Hybrid predictors
        std::cout << "Branch instruction address: " << std::hex << std::setw(8) << std::setfill('0') << address
                  << ", Branch outcome: " << actualOutcome
                  << ", Prediction: " << twoLevelPrediction
                  << ", correct/miss: " << hybridPrediction <<std::endl;

        // Update accuracy calculator
        accuracyCalculator.updateAccuracy(expectedOutcome, twoLevelPrediction, hybridPrediction);

        // Update predictors
        twoLevelPredictor.update(expectedOutcome);
        hybridPredictor.update(expectedOutcome);
    }

    // Output accuracies
    accuracyCalculator.printAccuracies();
}

int main() {
    int numInputs;

    // Get the number of inputs from the user
    std::cout << "Enter the number of inputs you want to simulate: ";
    std::cin >> numInputs;

    std::vector<std::pair<int, std::pair<bool, bool> > > simulatedInputs;

    // Simulate data for prediction
    for (int i = 0; i < numInputs; ++i) {
        int address = rand();  // Simulate an address
        bool actualOutcome = rand() % 2 == 0;  // Simulate actual outcome (0 or 1)
        bool expectedOutcome = rand() % 2 == 0;  // Simulate expected outcome (0 or 1)

        simulatedInputs.push_back(std::make_pair(address, std::make_pair(actualOutcome, expectedOutcome)));
    }

    TwoLevelBranchPredictor twoLevelPredictor(8, 512);
    HybridBranchPredictor hybridPredictor(8, 512, 8, 512, 16);
    AccuracyCalculator accuracyCalculator;

    simulateWorkload(simulatedInputs, twoLevelPredictor, hybridPredictor, accuracyCalculator);

    return 0;
}
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "TwoLevelBranchPredictor.hpp"
#include "HybridBranchPredictor.hpp"
#include "AccuracyCalculator.hpp"

void simulateWorkload(const std::vector<std::pair<int, std::pair<bool, bool> > >& userInputs, TwoLevelBranchPredictor& twoLevelPredictor, HybridBranchPredictor& hybridPredictor, AccuracyCalculator& accuracyCalculator) {
    for (const auto& input : userInputs) {
        int address = input.first;
        bool actualOutcome = input.second.first;
        bool expectedOutcome = input.second.second;

        bool twoLevelPrediction = twoLevelPredictor.predict();
        bool hybridPrediction = hybridPredictor.predict();

        std::cout << "Branch instruction address: " << std::hex << std::setw(8) << std::setfill('0') << address
                  << ", Branch outcome: " << actualOutcome
                  << ", Prediction: " << twoLevelPrediction
                  << ", correct/miss: " << hybridPrediction << std::endl;

        accuracyCalculator.updateAccuracy(expectedOutcome, twoLevelPrediction, hybridPrediction);

        twoLevelPredictor.update(expectedOutcome);
        hybridPredictor.update(expectedOutcome);
    }

    accuracyCalculator.printAccuracies();
}

int main() {
    int numInputs;

    // Get the number of inputs from the user
    std::cout << "Enter the number of inputs you want to simulate: ";
    std::cin >> numInputs;

        // Read inputs from trace file
    std::ifstream inputFile("gccSmall.trace");
    std::cerr << "Reading the gccSmall.trace" << std::endl;
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: gccSmall.trace" << std::endl;
        return 1;
    }

    std::vector<std::pair<int, std::pair<bool, bool> > > traceInputs;
    int address;
    bool actualOutcome, expectedOutcome;
    while (inputFile >> std::hex >> address >> actualOutcome >> expectedOutcome) {
        traceInputs.push_back(std::make_pair(address, std::make_pair(actualOutcome, expectedOutcome)));
    }

    inputFile.close(); // Close the file after reading

    std::vector<std::pair<int, std::pair<bool, bool> > > simulatedInputs;

    // Simulate data for prediction
    for (int i = 0; i < numInputs; ++i) {
        int address = rand();  // Simulate an address
        bool actualOutcome = rand() % 2 == 0;  // Simulate actual outcome (0 or 1)
        bool expectedOutcome = rand() % 2 == 0;  // Simulate expected outcome (0 or 1)

        simulatedInputs.push_back(std::make_pair(address, std::make_pair(actualOutcome, expectedOutcome)));
    }

    TwoLevelBranchPredictor twoLevelPredictor(8, 512);
    HybridBranchPredictor hybridPredictor(8, 512, 8, 512, 16);
    AccuracyCalculator accuracyCalculator;

    simulateWorkload(simulatedInputs, twoLevelPredictor, hybridPredictor, accuracyCalculator);

    return 0;
}
