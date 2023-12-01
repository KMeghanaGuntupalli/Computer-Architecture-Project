#ifndef HYBRID_BRANCH_PREDICTOR_HPP
#define HYBRID_BRANCH_PREDICTOR_HPP

#include <vector>

class HybridBranchPredictor {
private:
    std::vector<int> bhrLocal;
    std::vector<int> phtLocal;
    std::vector<int> bhrGlobal;
    std::vector<int> phtGlobal;
    std::vector<int> selector;

public:
    HybridBranchPredictor(int localBhrSize, int localPhtSize, int globalBhrSize, int globalPhtSize, int selectorSize);

    bool predict();
    void update(bool outcome);
};

#endif // HYBRID_BRANCH_PREDICTOR_HPP
