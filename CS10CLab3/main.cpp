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
T getElement(vector<T> vals, int index);

vector<char> createVector();

template <typename T>
void display(vector<T> vals);


int main(){
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    unsigned index;
    int numOfRuns = 10;
    while(--numOfRuns >= 0){
        cout << "Enter a number: " << endl;

        if(!(cin >> index)){
            throw runtime_error("Incorrect input for Index");
        }
        //range checking
        try{
            if(index < 0 || index >= vals.size()){
                throw out_of_range("std::outofrange");
            }
            curChar = getElement(vals,index);
            cout << "Element located at " << index << ": is " << curChar << endl;
        }
        catch (exception& excpt){
            cout << "out of range exception occured" << endl;
        }
    }
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
T getElement(vector<T> vals, int index){
    return vals.at(index);
}

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

template <typename T>
void display(vector<T> vals){
    for(unsigned i = 0; i < vals.size(); i++){
        cout << vals.at(i) << " ";
    }
    cout << endl;
}