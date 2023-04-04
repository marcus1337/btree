#ifndef BEHAVIOR_TREE_MUTATER_H
#define BEHAVIOR_TREE_MUTATER_H
#include "BehaviorTree.h"
#include <tuple>
#include <vector>

namespace bt {
	class BehaviorTreeMutater {
		BehaviorTree treeTemplate, mutation;
		void swapSubtrees(int index1, int index2);
		std::vector<std::pair<int, int>> branchPairs;
		int mutateCounter = 0;
		void swapMutate();

	public:
		BehaviorTreeMutater(const BehaviorTree& treeTemplate);
		void setTreeTemplate(const BehaviorTree& treeTemplate);
		BehaviorTree mutate();
	};
}

#endif

