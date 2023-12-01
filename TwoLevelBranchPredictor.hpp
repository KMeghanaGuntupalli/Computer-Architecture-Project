#ifndef TWO_LEVEL_BRANCH_PREDICTOR_HPP
#define TWO_LEVEL_BRANCH_PREDICTOR_HPP

#include <vector>

class TwoLevelBranchPredictor {
private:
    std::vector<int> bhr;
    std::vector<int> pht;

public:
    TwoLevelBranchPredictor(int bhrSize, int phtSize);

    bool predict();
    void update(bool outcome);
};

#endif // TWO_LEVEL_BRANCH_PREDICTOR_HPP
