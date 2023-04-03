#ifndef BT_CONTROLNODE_H
#define BT_CONTROLNODE_H
#include "TaskStatus.h"
#include "Node.h"
#include <vector>
#include "Task.h"
#include <memory>

namespace bt {
    class CompositeNode : public Node {
    protected:
        std::vector<std::shared_ptr<Node>> children;
        int nextChildIndex = 0;
    public:
        virtual TaskStatus tick() = 0;
        void addChild(std::shared_ptr<Node> node);
    };

    class Selector : public CompositeNode {
        virtual TaskStatus tick();
    };

    class Sequence : public CompositeNode {
        virtual TaskStatus tick();
    };
}


#endif // !BT_CONTROLNODE_H
