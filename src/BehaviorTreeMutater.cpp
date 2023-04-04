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
    const auto composites = this->treeTemplate.getComposites();
    for (int i = 0; i < composites.size(); i++) {
        for (int j = i; j < composites.size(); j++) {
            branchPairs.push_back({ i,j });
        }
    }
}

void BehaviorTreeMutater::swapSubtrees(int index1, int index2) {
    auto composites = mutation.getComposites();
    //TODO: implement
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