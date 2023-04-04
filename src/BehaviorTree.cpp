#include "BehaviorTree.h"
#include <iostream>
#include "btree/Composite.h"
#include <numeric>

using namespace bt;

BehaviorTree::BehaviorTree() {
    root = std::shared_ptr<Composite>(new Sequence());
}

std::shared_ptr<Composite> BehaviorTree::getRoot() {
    return root;
}

void BehaviorTree::reset() {
    for (Node* node : getNodes()) {
        node->setTicked(false);
    }
}

TaskStatus BehaviorTree::tick() {
    return root->statefulTick();
}

std::vector<std::pair<int, Node*>> BehaviorTree::getNodesDFS() {
    std::vector<std::pair<int, Node*>> nodes;
    std::function<void(std::pair<int, Node*>)> addNode = [&](std::pair<int, Node*> depthAndNode) {
        nodes.push_back(depthAndNode);
        auto [depth, node] = depthAndNode;
        for (Node* child : node->getChildren()) {
            addNode({ depth + 1, child });
        }
    };
    addNode({0, root.get() });
    return nodes;
}

std::vector<Node*> BehaviorTree::getNodes() {
    std::vector<Node*> nodes;
    std::function<void(Node*)> addNode = [&](Node* node) {
        nodes.push_back(node);
        auto children = node->getChildren();
        std::for_each(children.begin(), children.end(), addNode);
    };
    addNode(root.get());
    return nodes;
}

std::vector<std::pair<int, Node*>> BehaviorTree::getNodesTickOrder() {
    std::vector<std::pair<int, Node*>> orderedNodes;
    std::queue<std::pair<int, Node*>> bfsQueue;
    bfsQueue.push({ 0, root.get() });
    while (!bfsQueue.empty()) {
        auto [depth, node] = bfsQueue.front();
        orderedNodes.push_back({ depth, node });
        bfsQueue.pop();
        for (Node* child : node->getChildren()) {
            bfsQueue.push({ depth + 1, child });
        }
    }
    return orderedNodes;
}

void BehaviorTree::print() {
    for (auto [depth, node] : getNodesDFS()) {
        for (int i = 0; i < depth; i++) {
            std::cout << "   ";
        }
        if (node->getType() == NodeType::CONDITION) {
            std::cout << "(" << node->getName() << ")\n";
        }
        else if (node->getType() == NodeType::ACTION) {
            std::cout << "<" << node->getName() << ">\n";
        }
        else {
            std::cout << "[" << node->getName() << "]\n";
        }
    }
}