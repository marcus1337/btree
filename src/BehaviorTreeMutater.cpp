#include "BehaviorTreeMutater.h"
#include <iostream>

using namespace bt;

BehaviorTreeMutater::BehaviorTreeMutater(const BehaviorTree& treeTemplate) {
    setTreeTemplate(treeTemplate);
}

void BehaviorTreeMutater::setTreeTemplate(const BehaviorTree& treeTemplate) {
    this->treeTemplate = treeTemplate.clone();
    if (treeTemplate.getComposites().size() <= 2) {
        std::cout << "Warning: BehaviorTreeMutater wont function with this tree template. Add more composite nodes.\n";
    }
    const auto subbranches = this->treeTemplate.getCompositeLeafIndices();
    for (int i = 0; i < subbranches.size(); i++) {
        for (int j = i+1; j < subbranches.size(); j++) {
            branchPairs.push_back({ i,j });
        }
    }
}

void BehaviorTreeMutater::swapSubtrees(int i1, int i2) {
    auto subbranches = mutation.getCompositeLeafIndices();
    auto subbranch1 = subbranches[i1];
    auto subbranch2 = subbranches[i2];
    int leafIndex1 = subbranch1.first;
    int leafIndex2 = subbranch2.first;
    auto root1 = subbranch1.second;
    auto root2 = subbranch2.second;
    auto leaf1 = root1->getChildren()[leafIndex1]->clone();
    auto leaf2 = root2->getChildren()[leafIndex2]->clone();
    root1->replaceChild(leaf2, leafIndex1);
    root2->replaceChild(leaf1, leafIndex2);
}

void BehaviorTreeMutater::swapMutate() {
    auto branchPair = branchPairs[mutateCounter % branchPairs.size()];
    swapSubtrees(branchPair.first, branchPair.second);
}

BehaviorTree BehaviorTreeMutater::mutate() {
    if (treeTemplate.getComposites().size() <= 2) {
        std::cerr << "Error: BehaviorTreeMutater wont function with this tree template. Add more composite nodes.\n";
        return treeTemplate.clone();
    }
    mutation = treeTemplate.clone();
    swapMutate();
    mutateCounter++;
    return mutation.clone();
}