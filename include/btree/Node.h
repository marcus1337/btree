#ifndef BT_NODE_H
#define BT_NODE_H
#include "TaskStatus.h"
#include <vector>
#include <string>

namespace bt {
    enum class NodeType {
        ACTION, CONDITION, SEQUENCE, SELECTOR
    };

    class Node {
    private:
        TaskStatus status = TaskStatus::FAIL;
        bool ticked = false;
    protected:
        virtual TaskStatus tick() = 0;
    public:
        TaskStatus statefulTick();
        TaskStatus getStatus() const;
        bool isTicked() const;
        void setTicked(bool _ticked);
        virtual NodeType getType() const = 0;
        virtual std::string getName() const;
        virtual std::vector<Node*> getChildren() const = 0;
    };
}

#endif // !BT_NODE_H
