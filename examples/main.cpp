#include "BehaviorTree.h"
#include "BehaviorTreeBuilder.h"
#include "BehaviorTreeMutater.h"
#include <string>
#include <iostream>
#include "btree/TaskStatus.h"

int main(int argc, char* argv[]) {

    std::cout << "Behavior tree example-test.\n";
    bt::BehaviorTreeBuilder builder;
    bt::BehaviorTree tree = builder
        .Condition("Con1", []() {return true; })
        .Action("Act1", []() {return bt::TaskStatus::SUCCESS; })
        .Selector()
            .Action("Act2", []() {return bt::TaskStatus::SUCCESS; })
            .Action("Act3", []() {return bt::TaskStatus::SUCCESS; })
            .popComposite()
        .Action("Act4", []() {return bt::TaskStatus::SUCCESS; })
        .Selector()
            .Action("Act5", []() {return bt::TaskStatus::SUCCESS; })
            .Action("Act6", []() {return bt::TaskStatus::SUCCESS; })
            .popComposite()
        .build();

    tree.print();
    std::cout << "Num composites: " << tree.getComposites().size() << "\n";


    std::cout << "-------------- Mutation ----------------\n";
    bt::BehaviorTreeMutater mutater(tree);
    auto tree2 = mutater.mutate();
    tree2.print();

    return 0;
}