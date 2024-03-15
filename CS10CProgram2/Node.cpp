#include "Node.h"

#include <iostream>

using namespace std;

Node::Node()
    : count(0),left(nullptr),right(nullptr)
{
}

Node::Node(const string& s)
    : key(s),count(1),left(nullptr),right(nullptr)
{
}

// Tear down my left and right subtrees when deleted
Node::~Node() {
  // delete is safe on a nullptr.  No need to check
  delete left;
  delete right;
}

Node::Node(const Node& other) {
  key = other.key;
  count = other.count;
  left = other.left;
  right = other.right;
}

Node& Node::operator=(const Node &rhs){
  key = rhs.key;
  count = rhs.count;
  left = rhs.left;
  right = rhs.right;
  return *this;
}

ostream& operator<< ( ostream &os, const Node &a ) {
  os << a.key << "(" << a.count << ")";
  return os;
}

