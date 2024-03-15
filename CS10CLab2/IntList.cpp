#include "IntList.h"

#include <iostream>
#include <exception>

using namespace std;

#include <iostream>
ostream & operator<<(ostream &out, const IntList &rhs) {
  IntNode* currNode = rhs.dummyHead.next;
  //Runs until currNode is the dummyTail
  while (currNode != &(rhs.dummyTail)){
    out << currNode->data;
    if(currNode->next != &(rhs.dummyTail)){
      out << " ";
    }
    currNode = currNode->next;
  }
  return out;
}

IntList& IntList::operator=(const IntList& copy){
  clear();
  IntNode* currNode = copy.dummyHead.next;
  while(currNode != &(copy.dummyTail)){
    this->push_back(currNode->data);
    currNode = currNode->next;
  }
  return *this;
}

IntList::~IntList() {
  clear();
}

void IntList::clear(){
  //Runs until currNode is the dummyTail
  while (dummyHead.next != &dummyTail){
    pop_front();
  }
}

void IntList::push_front(int value) {
  //Creates new node
  IntNode* newNode = new IntNode(value);
  //points the new node's next pointer to previous head
  newNode->next = dummyHead.next;
  //points the previous head's prev pointer to the new node
  dummyHead.next->prev = newNode;
  //points the dummy head's next pointer to the new node
  dummyHead.next = newNode;
  //points the new node's prev pointer to the dummy head
  newNode->prev = &dummyHead;
}

void IntList::pop_front() {
  if(!empty()){
    //Creates pointer to node to be deleted
    IntNode* oldNode = dummyHead.next;
    //points dummy head's next pointer to the node after the head
    dummyHead.next = oldNode->next;
    //points the new head's prev node to the dummy head
    oldNode->next->prev = &dummyHead;
    //Deletes the old head
    delete oldNode;
  }
}

void IntList::push_back(int value) {
  //Creates new node
  IntNode* newNode = new IntNode(value);
  //points the last node's next pointer to the new node
  dummyTail.prev->next = newNode;
  //points new node's previous pointer to the old tail
  newNode->prev = dummyTail.prev;
  //points the dummy tail's previous pointer to newNode
  dummyTail.prev = newNode;
  //points new node's next to the address of dummyTail
  newNode->next = &dummyTail;
}

void IntList::pop_back() {
  if(!empty()){
    //creates pointer to tail
    IntNode* oldNode = dummyTail.prev;
    //changes the next pointer of the node before oldNode to dummyTail
    oldNode->prev->next = &dummyTail;
    //changes the dummyTail's previous pointer to point to the new tail
    dummyTail.prev = oldNode->prev;
    //delete old node
    delete oldNode;
  }
}

bool IntList::empty() const {
  return dummyHead.next == &dummyTail;
}

void IntList::printReverse() const {
  IntNode* currNode = dummyTail.prev;
  //Runs until currNode is the dummyHead
  while (currNode != &dummyHead){
    cout << currNode->data;
    if(currNode->prev != &dummyHead){
      cout << " ";
    }
    currNode = currNode->prev;
  }
}

