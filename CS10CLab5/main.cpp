#include <iostream>
#include "Heap.h"

#include <stdexcept>


using std::overflow_error;
using std::runtime_error;
using std::underflow_error;

using namespace std;

int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout 
    << "1. Enqueue" << endl
    << "2. Print" << endl
    << "3. Dequeue" << endl
    << "4. Quit" << endl;
  cin >> choice;

  cin.clear();
  cin.ignore(256, '\n');
  return choice;
}

int main(){
    Heap max_heap;

    int choice = menu();

    while (choice != 4) {

    if (choice == 1) {
      int priority, jobNumber, numPages;
      cout << "Enter print job to enqueue (priority, job Number, number of pages): ";
      cin>>priority>>jobNumber>>numPages;
      cout << endl;
      try{
        max_heap.enqueue(new PrintJob(priority, jobNumber, numPages));
      }
      catch(underflow_error & e){
        cout << e.what() << endl;
      }
      catch(overflow_error & e){
        cout << e.what() << endl;
      }
      catch(out_of_range & e){
        cout << e.what() << endl;
      }
    } 
    else if (choice == 2) {
      try{
        max_heap.print();
      }
      catch(underflow_error & e){
        cout << e.what() << endl;
      }
      catch(overflow_error & e){
        cout << e.what() << endl;
      }
      catch(out_of_range & e){
        cout << e.what() << endl;
      }
    }
    else if (choice == 3) {
      try{
        max_heap.dequeue();
      }
      catch(underflow_error & e){
        cout << e.what() << endl;
      }
      catch(overflow_error & e){
        cout << e.what() << endl;
      }
      catch(out_of_range & e){
        cout << e.what() << endl;
      }
    }
    choice = menu();
    }
    return 0;
}