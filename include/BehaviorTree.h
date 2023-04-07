#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H
#include "btree/Node.h"
#include <vector>
#include "btree/Composite.h"
#include "btree/Task.h"
#include <queue>
#include <array>

namespace bt {
    class BehaviorTree {
        std::shared_ptr<Composite> root;
        std::vector<Node*> getNodes() const;
        std::string getName(Node* node) const;
        std::array<std::string, 2> getDelimiters(Node* node) const;

    public:
        BehaviorTree();
        void reset();
        TaskStatus tick();
        TaskStatus statefulTick();
        std::vector<std::pair<int, Node*>> getNodesDFS() const;
        void print() const;
        std::shared_ptr<Composite> getRoot() const;
        std::vector<Composite*> getComposites() const;
        std::vector<std::pair<int, Composite*>> getCompositeLeafIndices() const; //returns detachable subbranches
        BehaviorTree clone() const;
    };
}

#endif
