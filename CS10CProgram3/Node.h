#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node {
    public:
        friend class Tree;
        string small;
        string large;
        int numKeys;

        Node *left = nullptr;
        Node *middle = nullptr;
        Node *right = nullptr;
        Node *parent;
        
        Node(const string& small, Node *parent);
};
#endif