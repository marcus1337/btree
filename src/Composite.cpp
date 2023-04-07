#include "btree/Composite.h"

using namespace bt;

void Composite::addLeaf(std::shared_ptr<Node> node) {
    leaves.push_back(node);
}

void Composite::insertLeaf(std::shared_ptr<Node> node, int index) {
    leaves.insert(leaves.begin() + index, node);
}

void Composite::removeLeaf(int index) {
    leaves.erase(leaves.begin() + index);
}

void Composite::replaceLeaf(std::shared_ptr<Node> node, int index) {
    leaves[index] = node;
}

void Composite::swapLeaves(int index1, int index2) {
    std::swap(leaves[index1], leaves[index2]);
}

std::vector<Node*> Composite::getLeaves() const {
    std::vector<Node*> nodes;
    for (std::shared_ptr<Node> child : leaves) {
        nodes.push_back(child.get());
    }
    return nodes;
}

TaskStatus Selector::tick() {
    for (int i = 0; i < leaves.size(); i++) {
        auto result = leaves[i]->statefulTick();
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
    for (int i = 0; i < leaves.size(); i++) {
        auto result = leaves[i]->statefulTick();
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
    for (const auto& child : getLeaves()) {
        node->addLeaf(child->clone());
    }
    return node;
}

std::shared_ptr<Node> Selector::clone() const {
    std::shared_ptr<Selector> node = std::make_shared<Selector>();
    for (const auto& child : getLeaves()) {
        node->addLeaf(child->clone());
    }
    return node;
}