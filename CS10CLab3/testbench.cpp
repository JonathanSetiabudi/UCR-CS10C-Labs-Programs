#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index);

template <typename T>
void selection_sort(vector<T> &vals);

template <typename T>
void display(vector<T> vals)



int main(){
    vector<int> vals1;
    vector<string> vals2;
    vector<double> vals3;
    vals1.push_back(7);
    vals1.push_back(5);
    vals1.push_back(25);
    vals1.push_back(-3);
    vals1.push_back(1);
    vals2.push_back("hello");
    vals2.push_back("xylophone");
    vals2.push_back("apple");
    vals2.push_back("banana");
    vals2.push_back("triangle");
    vals2.push_back("helicopter");
    vals3.push_back(4.5);
    vals3.push_back(6.7);
    vals3.push_back(1.2);
    vals3.push_back(3.4);
    vals3.push_back(9.8);
    selection_sort(vals1);
    selection_sort(vals2);
    selection_sort(vals3);
    display(vals1);
    display(vals2);
    display(vals3);
    return 0;
}

template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index){
    unsigned minIndex = index;
    for(unsigned i = index; i < vals.size(); i++){
        if(vals.at(i) < vals.at(minIndex)){
            minIndex = i;
        }
    }
    return minIndex;
}

template <typename T>
void selection_sort(vector<T> &vals){
    unsigned minIndex;
    for(unsigned i = 0; i < vals.size(); i++){
        minIndex = min_index(vals,i);
        swap(vals.at(i),vals.at(minIndex));
    }
}

template <typename T>
void display(vector<T> vals){
    for(unsigned i = 0; i < vals.size(); i++){
        cout << vals.at(i) << " ";
    }
    cout << endl;
}