#pragma once

#include "Node.h"

class AVLTree{
    Node* root;

    public:
        AVLTree();
        ~AVLTree();
        AVLTree(const AVLTree &) = delete;
        AVLTree& operator=(const AVLTree &) = delete;
        void insert(const string &);
        int balanceFactor(Node* );
        void printBalanceFactors();

    private:
        void rotateLeft(Node*);
        void rotateRight(Node*);
        void balance(Node*);
        int height(Node*);
        void printBalanceFactors(Node *);
        //SetChild will literally not work if the string is passed by reference
        void SetChild(Node*parent, string whichChild, Node* child);
        void ReplaceChild(Node* parent, Node* currentChild, Node* newChild);
};