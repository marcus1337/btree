#include "btree/Node.h"

using namespace bt;

TaskStatus Node::statefulTick() {
    if (isTicked() && getStatus() != TaskStatus::RUNNING)
        return getStatus();
    else {
        setTicked(true);
        status = tick();
        return getStatus();
    }
}

bool Node::isTicked() const {
    return ticked;
}

TaskStatus Node::getStatus() const {
    return status;
}

std::string Node::getName() const {
    return "";
}

void Node::setTicked(bool _ticked) {
    ticked = _ticked;
}