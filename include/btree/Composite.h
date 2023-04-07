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
        std::vector<std::shared_ptr<Node>> leaves;
    public:
        virtual TaskStatus tick() = 0;
        void addLeaf(std::shared_ptr<Node> node);
        void insertLeaf(std::shared_ptr<Node> node, int index);
        void removeLeaf(int index);
        void replaceLeaf(std::shared_ptr<Node> node, int index);
        void swapLeaves(int index1, int index2);
        virtual std::vector<Node*> getLeaves() const override;
    };

    class Selector : public Composite {
        virtual TaskStatus tick();
        virtual NodeType getType() const override;
        virtual std::shared_ptr<Node> clone() const override;
    };

    class Sequence : public Composite {
        virtual TaskStatus tick();
        virtual NodeType getType() const override;
        virtual std::shared_ptr<Node> clone() const override;
    };
}


#endif // !BT_CONTROLNODE_H
