#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using std::cout;
using std::endl;

using std::clock_t;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds

#include <chrono>
using std::chrono::steady_clock;
using std::chrono::microseconds;
using std::chrono::time_point;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::sort;

const int NUMBERS_SIZE = 50000;

// Provided by zybooks
int genRandInt(int low, int high) {
  return low + rand() % (high - low + 1);
}

// Provided by zybooks
void fillArrays(int arr1[], int arr2[],int arr3[]) {
  for(int i = 0; i < NUMBERS_SIZE; ++i){
    arr1[i] = genRandInt(0,NUMBERS_SIZE);
    arr2[i] = arr1[i];
    arr3[i] = arr1[i];
  }
}

int QPartition(int numbers[], int low, int high) {
  //find midpoint of array
  int midpoint = low + (high-low)/2;
  //set pivot to the midpoint value
  int pivot = numbers[midpoint];
  bool done = false;
  while(!done){
    //find the values in the left partition that are greater than the pivot
    while (numbers[low] < pivot) {
      low += 1;
    }
    //find the values in the right partition that are less than the pivot
    while (pivot < numbers[high]) {
      high -= 1;
    }
    //if low and high have crossed, the partition is done
    if(low >= high) {
      done = true;
    } 
    //low and high are still not crossed, swap values
    else 
    {
      std::swap(numbers[low], numbers[high]);
      low += 1;
      high -= 1;
    }
  }
  return high;
}

void Quicksort_midpoint(int numbers[], int low, int high){
  //if the array has 1 or 0 elements, then it is already sorted
  //and we can just return
  if (low >= high) {
    return;
  }
  //call quick partition
  int lowEndIndex = QPartition(numbers, low, high);
  //sort left partition
  Quicksort_midpoint(numbers, low, lowEndIndex);
  //sort right partition
  Quicksort_midpoint(numbers, lowEndIndex + 1, high);
}

int Quickpart3(int numbers[], int low, int high){
  //get value at low index
  int atLow = numbers[low];
  //get value at high index
  int atHigh = numbers[high];
  //get value at middle index
  int atMid = numbers[low + (high-low)/2];
  //instantiate pivot
  int pivot = 0;
  //if atLow is the smallest and atHigh is the largest, then atMid is the median
  if(atLow <= atMid && atMid <= atHigh){
    pivot = atMid;
  }
  //if atMid is the smallest and atHigh is the largest, then atLow is the median
  else if(atMid <= atLow && atMid <= atHigh)
  {
    pivot = atLow;
  }
  //otherwise it must be the atHigh
  else
  {
    pivot = atHigh;
  }
  bool done = false;
  while(!done){
    //find the values in the left partition that are greater than the pivot
    while (numbers[low] < pivot) {
      low += 1;
    }
    //find the values in the right partition that are less than the pivot
    while (pivot < numbers[high]) {
      high -= 1;
    }
    //if low and high have crossed, the partition is done
    if(low >= high) {
      done = true;
    } 
    //low and high are still not crossed, swap values
    else 
    {
      std::swap(numbers[low], numbers[high]);
      low += 1;
      high -= 1;
    }
  }
  //return the high index where the partitions are split
  return high;
}
void Quicksort_medianOfThree(int numbers[], int low, int high){
  if (low >= high){
    return;
  }
  //partition the array
  int lowEndIndex = Quickpart3(numbers, low, high);
  //sort left partition
  Quicksort_medianOfThree(numbers, low, lowEndIndex);
  //sort the right partition
  Quicksort_medianOfThree(numbers, lowEndIndex + 1, high);
}

void InsertionSort(int numbers[], int numbersSize) {
  for(int i = 1; i < numbersSize; ++i){
    int j = i;
    //insert numbers[i] into sorted part
    //stopping once numbers[i] is in the correct position
    //shifting down initial number[j] to its correct slot in the sorted part
    while(j > 0 && numbers[j] < numbers[j - 1]){
      //swap numbers[j] and numbers[j-1]
      std::swap(numbers[j],numbers[j-1]);
      --j;
    }
  }
}

// A helper function that will let us know if we have sorted
// everything
static bool is_sorted(int numbers[], int numbersSize) {
  if (numbersSize <= 0) return true;
  int last = numbers[0];
  for(int i=0; i < numbersSize; ++i) {
    int curr = numbers[i];
    if (curr < last) return false;
    last = curr;
  }
  return true;
}

static void copy_vector_into_array(const std::vector<int>& source, int array[]) {
  for(int i=0;i<static_cast<int>(source.size()); ++i) {
    array[i] = source[i];
  }
}

//main given to us by instructor
int main() {
  std::vector<int> sample;
  sample.reserve(NUMBERS_SIZE);
  for(int i=0; i<NUMBERS_SIZE; ++i) {
    sample.push_back(rand() % (NUMBERS_SIZE + 1));
  }
  
  int test_sizes[4] = { 10, 100, 1000, 50000 };
  int test_array[NUMBERS_SIZE];
  for(int i=0; i<4; ++i) {
    int size = test_sizes[i];
    cout << endl;
    cout << "-------------------- size " << size << " --------------------" << endl;

    // QUICK SORT
    {
      copy_vector_into_array(sample, test_array);
      auto start = high_resolution_clock::now();
      Quicksort_midpoint(test_array, 0, size-1);
      auto stop = high_resolution_clock::now();
      microseconds duration = duration_cast<microseconds>(stop - start);
      cout << duration.count() << " ms for quick sort " << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
    // QUICKM SORT
    {
      copy_vector_into_array(sample, test_array);
      auto start = high_resolution_clock::now();
      Quicksort_medianOfThree(test_array, 0, size-1);
      auto stop = high_resolution_clock::now();
      microseconds duration = duration_cast<microseconds>(stop - start);
      cout << duration.count() << " ms for quickm sort " << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
    // INSERTION SORT
    {
      copy_vector_into_array(sample, test_array);
      auto start = high_resolution_clock::now();
      InsertionSort(test_array, size);
      auto stop = high_resolution_clock::now();
      microseconds duration = duration_cast<microseconds>(stop - start);
      cout << duration.count() << " ms for insertion sort " << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
  }
 
  return 0;
}