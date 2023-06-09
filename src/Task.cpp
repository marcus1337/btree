#include "btree/Task.h"

using namespace bt;

Task::Task(std::string name, std::function<bool()> condition) : name(name), condition(condition) {
}

Task::Task(std::string name, std::function<TaskStatus()> action) : name(name), action(action) {
}

std::string Task::getName() const {
    return name;
}

TaskStatus Task::tick() {
    if (isAction())
        return action();
    else if (condition())
        return TaskStatus::SUCCESS;
    else
        return TaskStatus::FAIL;
}

bool Task::isCondition() const {
    return static_cast<bool>(condition);
}

bool Task::isAction() const {
    return static_cast<bool>(action);
}

std::vector<Node*> Task::getLeaves() const {
    return {};
}

NodeType Task::getType() const {
    if (isAction())
        return NodeType::ACTION;
    else
        return NodeType::CONDITION;
}

std::shared_ptr<Node> Task::clone() const {
    if (isAction()) {
        return std::shared_ptr<Task>(new Task(getName(), action));
    }
    else {
        return std::shared_ptr<Task>(new Task(getName(), condition));
    }
}