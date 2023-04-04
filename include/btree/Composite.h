#ifndef BT_CONTROLNODE_H
#define BT_CONTROLNODE_H
#include "TaskStatus.h"
#include "Node.h"
#include <vector>
#include "Task.h"
#include <memory>

namespace bt {
    class Composite : public Node {
    protected:
        std::vector<std::shared_ptr<Node>> children;
    public:
        virtual TaskStatus tick() = 0;
        void addChild(std::shared_ptr<Node> node);
        virtual std::vector<Node*> getChildren() const override;
    };

    class Selector : public Composite {
        virtual TaskStatus tick();
        virtual NodeType getType() const override;
    };

    class Sequence : public Composite {
        virtual TaskStatus tick();
        virtual NodeType getType() const override;
    };
}


#endif // !BT_CONTROLNODE_H
