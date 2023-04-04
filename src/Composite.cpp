#include "btree/Composite.h"

using namespace bt;

void Composite::addChild(std::shared_ptr<Node> node) {
    children.push_back(node);
}

std::vector<Node*> Composite::getChildren() const {
    std::vector<Node*> nodes;
    for (std::shared_ptr<Node> child : children) {
        nodes.push_back(child.get());
    }
    return nodes;
}

TaskStatus Selector::tick() {
    for (int i = 0; i < children.size(); i++) {
        auto result = children[i]->statefulTick();
        if (result == TaskStatus::RUNNING) {
            return result;
        }
        else if (result == TaskStatus::SUCCESS) {
            return result;
        }
    }
    return TaskStatus::FAIL;
}

TaskStatus Sequence::tick() {
    for (int i = 0; i < children.size(); i++) {
        auto result = children[i]->statefulTick();
        if (result == TaskStatus::RUNNING) {
            return result;
        }
        else if (result == TaskStatus::FAIL) {
            return result;
        }
    }
    return TaskStatus::SUCCESS;
}

NodeType Sequence::getType() const {
    return NodeType::SEQUENCE;
}

NodeType Selector::getType() const {
    return NodeType::SELECTOR;
}