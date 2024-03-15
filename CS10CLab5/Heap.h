#ifndef __HEAP_H
#define __HEAP_H

#include <stdexcept>


using std::overflow_error;
using std::runtime_error;
using std::underflow_error;

#include "PrintJob.h"

const int MAX_HEAP_SIZE = 10;

class Heap {
private:
  PrintJob* arr[MAX_HEAP_SIZE];
  int numItems;

public:
  Heap(): numItems(0) {
    //Makes sure there are no dangling pointers
    for(int i = 0; i < MAX_HEAP_SIZE; i++){
      arr[i] = nullptr;
    }
  }
  //Copy constructor
  Heap(const Heap& copy){
    //copys all the same values from the copy heap
    numItems = copy.numItems;
    for (int i = 0; i < numItems; i++){
      arr[i] = new PrintJob(copy.arr[i]->getPriority(), copy.arr[i]->getJobNumber(), copy.arr[i]->getPages());
    }
  }
  //Copy assignment operator
  Heap& operator=(const Heap& copy){
    //checks for self assignment
    if (this != &copy){
      //clears the current heap
      clear();
      //copys all the same values from the copy heap
      numItems = copy.numItems;
      for (int i = 0; i < numItems; i++){
        arr[i] = new PrintJob(copy.arr[i]->getPriority(), copy.arr[i]->getJobNumber(), copy.arr[i]->getPages());
      }
    }
    return *this;
  }
  //destructor
  ~Heap(){
    clear();
  }

  void enqueue ( PrintJob* );

  void dequeue ( );

  PrintJob* highest ( );

  void print ( );

  void printAll();

  void clear();

  
private:
  void trickleDown(int);

  void trickleUp(int);
};
#endif