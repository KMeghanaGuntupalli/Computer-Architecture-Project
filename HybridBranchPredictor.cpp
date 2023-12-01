// HybridBranchPredictor.cpp

#include "HybridBranchPredictor.hpp"

HybridBranchPredictor::HybridBranchPredictor(int localBhrSize, int localPhtSize, int globalBhrSize, int globalPhtSize, int selectorSize)
    : bhrLocal(localBhrSize, 1), phtLocal(localPhtSize, 2), bhrGlobal(globalBhrSize, 1), phtGlobal(globalPhtSize, 2), selector(selectorSize, 1) {}

bool HybridBranchPredictor::predict() {
    int localIndex = 0;
    for (int i = 0; i < bhrLocal.size(); ++i) {
        localIndex = (localIndex << 1) | bhrLocal[i];
    }

    int globalIndex = 0;
    for (int i = 0; i < bhrGlobal.size(); ++i) {
        globalIndex = (globalIndex << 1) | bhrGlobal[i];
    }

    bool localPrediction = phtLocal[localIndex] >= 2;
    bool globalPrediction = phtGlobal[globalIndex] >= 2;

    return selector.back() == 0 ? localPrediction : globalPrediction;
}

void HybridBranchPredictor::update(bool outcome) {
    int localIndex = 0;
    for (int i = 0; i < bhrLocal.size(); ++i) {
        localIndex = (localIndex << 1) | bhrLocal[i];
    }

    int globalIndex = 0;
    for (int i = 0; i < bhrGlobal.size(); ++i) {
        globalIndex = (globalIndex << 1) | bhrGlobal[i];
    }

    bool localPrediction = phtLocal[localIndex] >= 2;
    if (outcome) {
        if (phtLocal[localIndex] < 3) {
            ++phtLocal[localIndex];
        }
        if (bhrLocal.back() == 0) {
            bhrLocal.insert(bhrLocal.begin(), 1);
            bhrLocal.pop_back();
        }
    } else {
        if (phtLocal[localIndex] > 0) {
            --phtLocal[localIndex];
        }
        if (bhrLocal.back() == 1) {
            bhrLocal.insert(bhrLocal.begin(), 0);
            bhrLocal.pop_back();
        }
    }

    bool globalPrediction = phtGlobal[globalIndex] >= 2;
    if (outcome) {
        if (phtGlobal[globalIndex] < 3) {
            ++phtGlobal[globalIndex];
        }
        if (bhrGlobal.back() == 0) {
            bhrGlobal.insert(bhrGlobal.begin(), 1);
            bhrGlobal.pop_back();
        }
    } else {
        if (phtGlobal[globalIndex] > 0) {
            --phtGlobal[globalIndex];
        }
        if (bhrGlobal.back() == 1) {
            bhrGlobal.insert(bhrGlobal.begin(), 0);
            bhrGlobal.pop_back();
        }
    }

    if (localPrediction != globalPrediction) {
        if (outcome == localPrediction) {
            if (selector.back() < 3) {
                ++selector.back();
            }
        } else {
            if (selector.back() > 0) {
                --selector.back();
            }
        }
    }
}
