#ifndef BT_BEHAVIOR_TREE_BUILDER_H
#define BT_BEHAVIOR_TREE_BUILDER_H
#include "BehaviorTree.h"
#include "btree/Task.h"
#include "btree/Composite.h"
#include <stack>

namespace bt {
    class BehaviorTreeBuilder {
        BehaviorTree behaviorTree;
        std::stack<Composite*> composites;
        void addComposite(std::shared_ptr<Composite> composite);
        void addTask(std::shared_ptr<Task> task);
    public:
        BehaviorTreeBuilder();
        BehaviorTreeBuilder& Condition(std::string name, std::function<bool()> condition);
        BehaviorTreeBuilder& Action(std::string name, std::function<TaskStatus()> action);
        BehaviorTreeBuilder& Sequence();
        BehaviorTreeBuilder& Selector();
        BehaviorTreeBuilder& popComposite();
        BehaviorTree build();
    };
}

#endif