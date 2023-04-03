#ifndef BT_TASK_H
#define BT_TASK_H
#include "TaskStatus.h"
#include <string>
#include <functional>
#include "Node.h"

namespace bt {
    class Task : public Node {
        std::string name;
        std::function<bool()> condition;
        std::function<TaskStatus()> action;
    public:
        Task(std::string name, std::function<bool()> condition);
        Task(std::string name, std::function<TaskStatus()> action);
        std::string getName() const;
        virtual TaskStatus tick() override;
        bool isCondition() const;
        bool isAction() const;
    };
}

#endif // !BT_TASK_H
