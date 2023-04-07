#include "BehaviorTreeBuilder.h"
#include "btree/Task.h"
#include "btree/Composite.h"

using namespace bt;

BehaviorTreeBuilder::BehaviorTreeBuilder() {
    composites.push(behaviorTree.getRoot().get());
}

void BehaviorTreeBuilder::addComposite(std::shared_ptr<Composite> composite) {
    Composite* parent = composites.top();
    parent->addLeaf(composite);
    composites.push(composite.get());
}

void BehaviorTreeBuilder::addTask(std::shared_ptr<Task> task) {
    Composite* parent = composites.top();
    parent->addLeaf(task);
}

BehaviorTreeBuilder& BehaviorTreeBuilder::Condition(std::string name, std::function<bool()> condition) {
    addTask(std::shared_ptr<Task>(new Task(name, condition)));
    return *this;
}

BehaviorTreeBuilder& BehaviorTreeBuilder::Action(std::string name, std::function<TaskStatus()> action) {
    addTask(std::shared_ptr<Task>(new Task(name, action)));
    return *this;
}

BehaviorTreeBuilder& BehaviorTreeBuilder::Sequence() {
    addComposite(std::shared_ptr<Composite>(new bt::Sequence()));
    return *this;
}

BehaviorTreeBuilder& BehaviorTreeBuilder::Selector() {
    addComposite(std::shared_ptr<Composite>(new bt::Selector()));
    return *this;
}

BehaviorTreeBuilder& BehaviorTreeBuilder::popComposite() {
    composites.pop();
    return *this;
}

BehaviorTree BehaviorTreeBuilder::build() {
    return behaviorTree;
}
