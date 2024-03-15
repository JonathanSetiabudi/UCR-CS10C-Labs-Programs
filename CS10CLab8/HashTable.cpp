#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "HashTable.h"
#include "WordEntry.h"

HashTable::HashTable (int s) {
  //set the size of the array
  size = s;
  //initialize the array of lists
  hashTable = new list<WordEntry>[s];
}

HashTable::~HashTable() {
  //delete the array of lists
  delete[] hashTable;
  //just to be safe, set it to nullptr
  hashTable = nullptr;
}


//surely this doesn't need comments(?)
int HashTable::computeHash(const string &s) const {
  int prime = 31;
  int hashvalue = 0;
  for(unsigned i = 0; i < s.length();i++)
  {
    hashvalue = (hashvalue * prime + int(s[i])) % size;
  }
  return hashvalue;
}

void HashTable::put(const string &s, int score) {
  int hash = computeHash(s);
  //search through list and see if word is already in the list
  for(auto it = hashTable[hash].begin(); it != hashTable[hash].end(); ++it)
  {
    //if we find the word, add the new appearance
    if(it->getWord() == s)
    {
      it->addNewAppearance(score);
      return;
    }
  }
  //if we get here it means we never found the word
  //add a new wordEntry to the list
  WordEntry newWord(s, score);
  hashTable[hash].push_back(newWord);
}

double HashTable::getAverage(const string &word) const {
  //get hash
  int hash = computeHash(word);
  for(auto it = hashTable[hash].begin(); it != hashTable[hash].end(); ++it)
  {
    //if found, get the average of that wordEntry
    if(it->getWord() == word)
    {
      return it->getAverage();
    }
  }
  //return a negative number if it isn't found
  return -1.0;
}

bool HashTable::contains(const string &word) const {
  //get hash
  int hash = computeHash(word);
  //for each wordEntry in hashTable[hash], check if s is in the list
  for(auto it = hashTable[hash].begin(); it != hashTable[hash].end(); ++it)
  {
    //if we find the word, return true
    if(it->getWord() == word)
    {
      return true;
    }
  }
  //if we get here, word wasn't found, return false
  return false;
}


//main given by instructor
// int main() {
// 	// declare a few needed variables for inputing the data
// 	string line;    
// 	int score;
// 	string message = " ";
	
// 	// open input file
// 	ifstream myfile("movieReviews.txt");
// 	if (myfile.fail()) {
// 	    cout << "could not open file" << endl;
// 	    exit(1);
// 	}
	
// 	//create hash table
// 	HashTable table(20071);
	
// 	while (true) {
// 	    myfile >> score;     // get score
// 	    myfile.get();        // get blank space
// 	    getline(myfile, line);
// 	    if (not myfile) {
// 	      if (myfile.eof()) break; // Doesn't return true unless we tried input
// 	      throw runtime_error("input failed");
// 	    }
// 	    int len = line.size();
// 	    while(len > 0) {     // identify all individual strings
// 	        string sub;
// 	        len = line.find(" ");
// 	        if (len > 0) {
// 	            sub = line.substr(0, len);
// 	            line = line.substr(len + 1, line.size());
// 	        }
// 	        else {
// 	            sub = line.substr(0, line.size() - 1);
// 	        }
// 	        table.put(sub, score); // insert string with the score
// 	    }
// 	}
	
// 	// after data is entered in hash function
// 	// prompt user for a new movie review
// 	while(message.length() > 0) {
// 	    cout << "enter a review -- Press return to exit: " << endl;
// 	    getline(cin, message);
	
// 	    // used for calculating the average
// 	    double sum = 0;
// 	    int count = 0;
	    
// 	    double sentiment = 0.0;
	    
// 	    size_t len = message.size();
// 	    // get each individual word from the input
// 	    while(len != string::npos) {
// 	        string sub;
// 	        len = message.find(" ");
// 	        if (len != string::npos) {
// 	            sub = message.substr(0, len);
// 	            message = message.substr(len + 1, message.size());
// 	        }
// 	        else {
// 	            sub = message;
// 	        }
// 	        // calculate the score of each word
// 	        sum += table.getAverage(sub);
// 	        ++count;
// 	    }
	
// 	    if (message.size() > 0) {
// 	    	sentiment = sum / count;
// 	        cout << "The review has an average value of " << sentiment << endl;
// 	        if (sentiment >= 3.0) {
// 	        	cout << "Positive Sentiment" << endl;
// 	        }
// 	        else if (sentiment >= 2.0) {
// 	        	cout << "Somewhat Positive Sentiment" << endl;
// 	        }
// 	        else if (sentiment >= 1.0) {
// 	        	cout << "Somewhat Negative Sentiment" << endl;
// 	        }
// 	        else {
// 	        	cout << "Negative Sentiment" << endl;
// 	        }
// 	        cout << endl;
// 	    }
// 	}
	
// 	return 0;
// }