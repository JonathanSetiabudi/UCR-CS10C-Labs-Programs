#include <iostream>
#include "IntList.h"

using namespace std;

int main() {
  IntList list;
  
  cout << "empty: " << list << endl;
  list.push_front(3);
  cout << "push front 3: " << list << endl;
  list.push_back(1);
  cout << "push back 1: " << list << endl;
  list.push_back(5);
  cout << "push back 5: " << list << endl;
  list.push_front(2);
  cout << "push front 2: " << list << endl;
  list.pop_back();
  cout << "pop back: " << list << endl;
  list.pop_front();
  cout << "pop front: " << list << endl;
  list.clear();
  list.push_back(3);
  list.push_back(120);
  cout << "List:" << list << endl;
  list.printReverse();
  cout << endl;

  list.pop_back();
  list.pop_back();
  list.push_front(60);
  list.push_front(360);
  cout << "List:" << list << endl;
  list.printReverse();
  cout << endl;
       
  return 0;
}
