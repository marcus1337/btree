#include "BehaviorTree.h"
#include <iostream>
#include "btree/Composite.h"
#include <numeric>
#include <iomanip>
#include <tuple>
#include <array>

using namespace bt;

BehaviorTree::BehaviorTree() {
    root = std::shared_ptr<Composite>(new Sequence());
}

BehaviorTree BehaviorTree::clone() const {
    BehaviorTree tree;
    for (const auto& child : root->getChildren()) {
        tree.getRoot()->addChild(child->clone());
    }
    return tree;
}

std::shared_ptr<Composite> BehaviorTree::getRoot() const {
    return root;
}

std::vector<std::pair<int, Composite*>> BehaviorTree::getCompositeLeafIndices() const {
    std::vector<std::pair<int, Composite*>> leafIndicePairs;
    for (Composite* composite : getComposites()) {
        auto leaves = composite->getChildren();
        for (int i = 0; i < leaves.size(); i++) {
            auto leaf = dynamic_cast<Composite*>(leaves[i]);
            if (leaf != nullptr) {
                leafIndicePairs.push_back({ i, composite });
            }
        }
    }
    return leafIndicePairs;
}

std::vector<Composite*> BehaviorTree::getComposites() const {
    std::vector<Composite*> result;
    for (Node* child : getNodes()) {
        auto compositeChild = dynamic_cast<Composite*>(child);
        if (compositeChild != nullptr) {
            result.push_back(compositeChild);
        }
    }
    return result;
}

void BehaviorTree::reset() {
    for (Node* node : getNodes()) {
        node->setTicked(false);
    }
}

TaskStatus BehaviorTree::tick() {
    auto status = root->statefulTick();
    if (status != TaskStatus::RUNNING)
        reset();
    return status;
}

TaskStatus BehaviorTree::statefulTick() {
    return root->statefulTick();
}

std::vector<std::pair<int, Node*>> BehaviorTree::getNodesDFS() const {
    std::vector<std::pair<int, Node*>> nodes;
    std::function<void(std::pair<int, Node*>)> addNode = [&](std::pair<int, Node*> depthAndNode) {
        nodes.push_back(depthAndNode);
        auto [depth, node] = depthAndNode;
        for (Node* child : node->getChildren()) {
            addNode({ depth + 1, child });
        }
    };
    addNode({ 0, root.get() });
    return nodes;
}

std::vector<Node*> BehaviorTree::getNodes() const {
    std::vector<Node*> nodes;
    std::function<void(Node*)> addNode = [&](Node* node) {
        nodes.push_back(node);
        auto children = node->getChildren();
        std::for_each(children.begin(), children.end(), addNode);
    };
    addNode(root.get());
    return nodes;
}

std::string BehaviorTree::getName(Node* node) const {
    if (node->getType() == bt::NodeType::SEQUENCE)
        return "->";
    if (node->getType() == bt::NodeType::SELECTOR)
        return "?";
    else
        return node->getName();
}

std::array<std::string, 2> BehaviorTree::getDelimiters(Node* node) const {
    if (node->getType() == bt::NodeType::ACTION)
        return { "<",">" };
    if (node->getType() == bt::NodeType::CONDITION)
        return { "(",")" };
    else
        return { "[", "]" };
}

void BehaviorTree::print() const {
    for (auto [depth, node] : getNodesDFS()) {
        auto delimiters = getDelimiters(node);
        std::cout << std::setw(depth * 3) << delimiters.front() << getName(node) << delimiters.back() << "\n";
    }
}