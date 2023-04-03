#ifndef BT_NODE_H
#define BT_NODE_H
#include "TaskStatus.h"

namespace bt {
    class Node {
    public:
        virtual TaskStatus tick() = 0;
    };
}

#endif // !BT_NODE_H
