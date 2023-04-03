#include "btree/CompositeNode.h"

using namespace bt;

void CompositeNode::addChild(std::shared_ptr<Node> node) {
    children.push_back(node);
}

TaskStatus Selector::tick() {
    for (int i = nextChildIndex; i < children.size(); i++) {
        auto result = children[i]->tick();
        if (result == TaskStatus::RUNNING) {
            nextChildIndex = i;
            return result;
        }
        else if (result == TaskStatus::SUCCESS) {
            nextChildIndex = 0;
            return result;
        }
    }
    return TaskStatus::FAIL;
}

TaskStatus Sequence::tick() {
    for (int i = nextChildIndex; i < children.size(); i++) {
        auto result = children[i]->tick();
        if (result == TaskStatus::RUNNING) {
            nextChildIndex = i;
            return result;
        }
        else if (result == TaskStatus::FAIL) {
            nextChildIndex = 0;
            return result;
        }
    }
    nextChildIndex = 0;
    return TaskStatus::SUCCESS;
}
