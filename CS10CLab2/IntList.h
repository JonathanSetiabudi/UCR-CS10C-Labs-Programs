#pragma once

#include <iostream>

struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(nullptr), next(nullptr) {}
};

class IntList {
private:
  IntNode dummyHead;
  IntNode dummyTail;
public:
  IntList()
    : dummyHead(-1),
      dummyTail(-1)
  {
    // The dummy head points to dummy tail
    dummyHead.prev = nullptr;
    dummyHead.next = &dummyTail;

    // The dummy tail points back at head
    dummyTail.prev = &dummyHead;
    dummyTail.next = nullptr;
  }

  IntList(const IntList &copy):
    dummyHead(-1),
    dummyTail(-1)
    {
    IntNode* currNode = copy.dummyHead.next;
    while(currNode != &(copy.dummyTail)){
      this->push_back(currNode->data);
      currNode = currNode->next;
    }
  }
  ~IntList();

  IntList& operator=(const IntList& copy);

  void push_front(int value);

  void pop_front();

  void push_back(int value);

  void pop_back();

  bool empty() const;

  void clear();

  friend std::ostream & operator<<(std::ostream &out, const IntList &rhs);

  // This function does NOT send to the stream a newline
  // or space at the end.
  void printReverse() const;
};
