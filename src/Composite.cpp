#include "btree/Composite.h"

using namespace bt;

void Composite::addChild(std::shared_ptr<Node> node) {
    children.push_back(node);
}

void Composite::insertChild(std::shared_ptr<Node> node, int index) {
    children.insert(children.begin() + index, node);
}

void Composite::removeChild(int index) {
    children.erase(children.begin() + index);
}

void Composite::replaceChild(std::shared_ptr<Node> node, int index) {
    children[index] = node;
}

void Composite::swapChildren(int index1, int index2) {
    std::swap(children[index1], children[index2]);
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

std::shared_ptr<Node> Sequence::clone() const {
    std::shared_ptr<Sequence> node = std::make_shared<Sequence>();
    for (const auto& child : getChildren()) {
        node->addChild(child->clone());
    }
    return node;
}

std::shared_ptr<Node> Selector::clone() const {
    std::shared_ptr<Selector> node = std::make_shared<Selector>();
    for (const auto& child : getChildren()) {
        node->addChild(child->clone());
    }
    return node;
}