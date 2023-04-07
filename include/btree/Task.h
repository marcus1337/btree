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
        bool isCondition() const;
        bool isAction() const;
    public:
        Task(std::string name, std::function<bool()> condition);
        Task(std::string name, std::function<TaskStatus()> action);
        virtual std::string getName() const override;
        virtual TaskStatus tick() override;
        virtual std::vector<Node*> getLeaves() const override;
        virtual NodeType getType() const override;
        virtual std::shared_ptr<Node> clone() const override;
    };
}

#endif // !BT_TASK_H
