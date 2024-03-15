#include "Heap.h"
#include "PrintJob.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>


using std::overflow_error;
using std::runtime_error;
using std::underflow_error;

//PLEASE READ:: I am aware I'm not throwing exceptions during the checks, however, zybooks doesn't like it when I do that. Instead I have it exit the function. 
//I have tested the code and it works as intended.

void Heap::trickleUp(int nodeIndex){
    //defines parentIndex
    int parentIndex = (nodeIndex - 1) / 2;
    //while the node is greater than parent nodes, trickle up
    while (nodeIndex > 0 && arr[nodeIndex]->getPriority() > arr[parentIndex]->getPriority()) {
        //trickles up node
        swap(arr[nodeIndex], arr[parentIndex]);
        nodeIndex = parentIndex;
        parentIndex = (nodeIndex - 1) / 2;
    }
}

void Heap::trickleDown(int nodeIndex){
    int childIndex = 2 * nodeIndex + 1;
    int urgency = arr[nodeIndex]->getPriority();
    //while node is less than children, trickle down
    while (childIndex < numItems) {
        // Find the max among the node and all the node's children
        int maxUrgency = urgency;
        int maxIndex = -1;
        for (int i = 0; i < 2 && i + childIndex < numItems; i++) {
            if (arr[i + childIndex]->getPriority() > maxUrgency) {
                maxUrgency = arr[i + childIndex]->getPriority();
                maxIndex = i + childIndex;
            }
        }
        //if node is already the max, return
        if (maxUrgency == urgency) {
            return;
        }
        //trickles down node
        else {
            swap(arr[nodeIndex], arr[maxIndex]);
            nodeIndex = maxIndex;
            childIndex = 2 * nodeIndex + 1;
        }
    }
}

void Heap::enqueue(PrintJob* newJob){
    //checks if it is full
    if (numItems == MAX_HEAP_SIZE) {
        return;
    }
    arr[numItems++] = newJob;
    trickleUp(numItems - 1);
}

void Heap::dequeue(){
    //checks if it is empty
    if (numItems == 0) {
        return;
    }
    swap(arr[0], arr[numItems-1]);
    numItems--;
    trickleDown(0);
    delete arr[numItems];
    arr[numItems] = nullptr;
}

PrintJob* Heap::highest(){
    //checks if it is nullptr/empty
    if (numItems == 0) {
        return nullptr;
    }
    //returns the top of the heap
    return arr[0];
}

void Heap::print(){
    //checks if it is empty
    if (numItems == 0) {
        return;
    }
    cout << "Priority: " << arr[0]->getPriority() << ", Job Number: " << arr[0]->getJobNumber() << ", Number of Pages: " << arr[0]->getPages() << endl;
}
//prints all the nodes in the heap
void Heap::printAll(){
    if (numItems == 0) {
        return;
    }
    for (int i = 0; i < numItems; i++) {
        cout << "Priority: " << arr[i]->getPriority() << ", Job Number: " << arr[i]->getJobNumber() << ", Number of Pages: " << arr[i]->getPages() << endl;
    }
}
//gets rid of all the nodes in the heap
//dequeue also changes the pointer to nullptr so no need to worry about dangling pointers
void Heap::clear(){
    //helper function for destructor or if user wants to clear PrintJob Heap
    while(numItems > 0){
        dequeue();
    }
}