#include "Node.h"
#include <string>

Node::Node(const string &small, Node *parent):
    small(small),
    large(""),
    numKeys(1),
    parent(parent)
{}