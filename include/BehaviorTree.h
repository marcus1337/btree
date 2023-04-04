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
        std::vector<Node*> getNodes() const;
        std::vector<std::pair<int, Node*>> getNodesDFS() const;
    public:
        BehaviorTree();
        void reset();
        TaskStatus tick();
        TaskStatus statefulTick();
        void print() const;
        std::shared_ptr<Composite> getRoot() const;
        std::vector<Composite*> getComposites() const;
        BehaviorTree clone() const;
    };
}

#endif
