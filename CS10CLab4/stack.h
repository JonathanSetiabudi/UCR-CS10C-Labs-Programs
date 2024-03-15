#pragma once

#include <stdexcept>


using std::overflow_error;
using std::runtime_error;
using std::underflow_error;



template<typename T>
class stack {
  static constexpr unsigned MAX_SIZE = 20;
  unsigned size;
  T data[MAX_SIZE];
public:
  
  stack() : size(0) {}

  void push(const T& value) {
    //checks if stack is full and calls exception if it is
    if(size == MAX_SIZE) {
      throw overflow_error("Called push on full stack.");
    }
    //adds value to the end of the stack and then post increments size
    data[size++] = value;
  }

  bool empty() const { return size == 0; }

  void pop() {
    //checks if size is 0 and throws an error if it is
    if(size == 0) {
      throw underflow_error("Called pop on empty stack.");
    }
    //decrements size by 1
    --size;
  }

  void pop_two() {
    //checks if size is 0 and throws an error if it is
    if(size == 0) {
      throw underflow_error("Called pop_two on empty stack.");
    }
    //checks if size is 1 and throws an error if it is
    if(size == 1) {
      throw underflow_error("Called pop_two on a stack of size 1.");
    }
    //decrements size by 2
    size -= 2;
  }

  T& top() {
    //checks if size is 0 and throws an error if it is
    if(size == 0) {
      throw underflow_error("Called top on empty stack.");
    }
    //return
    return data[size - 1];
  }
  const T& top() const {
    //checks if size is 0 and throws an error if it is 
    if(size == 0) {
      throw underflow_error("Called top on empty stack.");
    }
    //return
    return data[size - 1];
   }
};
