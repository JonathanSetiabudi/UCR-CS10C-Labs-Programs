#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

using namespace std;

class Tree {
    private:
        Node *root;

    public:
        Tree( );
        ~Tree( );
        Tree(const Tree&) = delete;
        Tree& operator=(const Tree&) = delete;
        void insert(const string &);
        void preOrder( ) const;
        void inOrder( ) const;
        void postOrder( ) const;
        void remove(const string &);
        bool search (const string &) const;

    private:
        void preOrder(Node *tree) const;
        void inOrder(Node *tree) const;
        void postOrder(Node *tree) const;
        Node* getLeftsibling(Node* tree);
        Node* getRightsibling(Node* tree);
        bool search (Node* point, const string &key) const;
        Node* nodeSearch(const string&) const;
        string getParentKeyLeftOf(Node* tree);
        void shiftUp(Node *tree);
        Node* recurDelete(Node *node);
};

#endif