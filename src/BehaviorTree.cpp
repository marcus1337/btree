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

std::queue<std::pair<int, Node*>> BehaviorTree::getNodesBFS() {
    std::queue<std::pair<int, Node*>> bfsQueue;
    bfsQueue.push({ 0, root.get() });
    while (!bfsQueue.empty()) {
        auto [depth, node] = bfsQueue.front();
        bfsQueue.pop();
        for (Node* child : node->getChildren()) {
            bfsQueue.push({ depth + 1, child });
        }
    }
    return bfsQueue;
}

void BehaviorTree::print() {
    std::cout << "Behavior Tree:\n";
    std::cout << "================\n";
    std::queue<std::pair<int, Node*>> bfsQueue = getNodesBFS();
    std::cout << "Size: " << bfsQueue.size() << "\n";
    std::cout << "Size: " << getNodes().size() << "\n";

    while (!bfsQueue.empty()) {
        auto [depth, node] = bfsQueue.front();
        bfsQueue.pop();
        std::cout << "Node: " << node->getName();
        if (node->isTicked()) {
            std::cout << " (" << (int)node->getStatus() << ")";
        }
        std::cout << "\t";
        if (!bfsQueue.empty() && bfsQueue.front().first > depth) {
            std::cout << "\n";
        }
    }
}