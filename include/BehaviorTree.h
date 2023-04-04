#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H
#include "btree/Node.h"
#include <vector>
#include "btree/Composite.h"
#include "btree/Task.h"
#include <queue>

namespace bt {
    class BehaviorTree {
        std::shared_ptr<Composite> root;
        std::vector<Node*> getNodes();
        std::vector<std::pair<int, Node*>> getNodesDFS();
    public:
        BehaviorTree();
        void reset();
        TaskStatus tick();
        void print();
        std::shared_ptr<Composite> getRoot();
    };
}

#endif
