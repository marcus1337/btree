#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H
#include "btree/Node.h"
#include <vector>
#include "btree/CompositeNode.h"
#include "btree/Task.h"

namespace bt {
    class BehaviorTree {
        std::shared_ptr<Node> root;

    public:

        void reset();
        TaskStatus tick();

    };
}

#endif
