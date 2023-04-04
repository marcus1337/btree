#include "BehaviorTree.h"
#include <iostream>
#include <queue>

using namespace bt;

void BehaviorTree::reset() {
    for (Node* node : getTreeNodes()) {
        node->setTicked(false);
    }
}

TaskStatus BehaviorTree::tick() {
    if (root != nullptr)
        return root->statefulTick();
    else
        return TaskStatus::FAIL;
}

std::vector<Node*> BehaviorTree::getTreeNodes(Node* node) {
    std::vector<Node*> nodes;
    nodes.push_back(node);
    for (Node* child : node->getChildren()) {
        auto childNodes = getTreeNodes(child);
        nodes.insert(nodes.end(), childNodes.begin(), childNodes.end());
    }
    return nodes;
}

std::vector<Node*> BehaviorTree::getTreeNodes() {
    if (root == nullptr)
        return {};
    return getTreeNodes(root.get());
}

void BehaviorTree::print() {
    std::cout << "Behavior Tree:\n";
    std::cout << "================\n";

    if (root == nullptr) {
        std::cout << "Empty\n";
        return;
    }

    std::queue<std::pair<int, Node*>> bfsQueue;
    bfsQueue.push({ 0, root.get() });

    while (!bfsQueue.empty()) {
        auto [depth, node] = bfsQueue.front();
        bfsQueue.pop();
        std::cout << "Node: " << node->getName();
        if (node->isTicked()) {
            std::cout << " (" << (int)node->getStatus() << ")";
        }
        std::cout << "\t";

        for (Node* child : node->getChildren()) {
            bfsQueue.push({ depth + 1, child });
        }
        if (!bfsQueue.empty() && bfsQueue.front().first > depth) {
            std::cout << "\n";
        }
    }
}