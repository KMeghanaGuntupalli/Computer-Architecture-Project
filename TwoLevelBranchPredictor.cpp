// TwoLevelBranchPredictor.cpp

#include "TwoLevelBranchPredictor.hpp"

TwoLevelBranchPredictor::TwoLevelBranchPredictor(int bhrSize, int phtSize) : bhr(bhrSize, 1), pht(phtSize, 2) {}

bool TwoLevelBranchPredictor::predict() {
    int index = 0;
    for (int i = 0; i < bhr.size(); ++i) {
        index = (index << 1) | bhr[i];
    }
    return pht[index] >= 2;
}

void TwoLevelBranchPredictor::update(bool outcome) {
    int index = 0;
    for (int i = 0; i < bhr.size(); ++i) {
        index = (index << 1) | bhr[i];
    }

    if (outcome) {
        if (pht[index] < 3) {
            ++pht[index];
        }
        if (bhr.back() == 0) {
            bhr.insert(bhr.begin(), 1);
            bhr.pop_back();
        }
    } else {
        if (pht[index] > 0) {
            --pht[index];
        }
        if (bhr.back() == 1) {
            bhr.insert(bhr.begin(), 0);
            bhr.pop_back();
        }
    }
}
