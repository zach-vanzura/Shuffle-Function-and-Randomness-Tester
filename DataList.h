//
// Created by jack on 2/12/2024.
//
#ifndef M2AP_DATALIST_H
#define M2AP_DATALIST_H

#include <algorithm>
#include <chrono>
#include <initializer_list>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>

using namespace std;
using namespace std::chrono;
using std::scientific;
// Template class which contains a vector of the template type
// created in accordance to instruction in brightspace pdf
template<typename T>
class DataList {

private:
    vector<T> dataVec;

public:
    // Default constructor
    DataList() = default;

    // Default destructor
    ~DataList() = default;

    // Method to randomize dataVec by Jack D'Iorio
    vector<T> randomJD(vector<T> copyVec) {
        int randIndex1, randIndex2;
        T swapItem;
        vector<int> pickedNums;
        bool pickedRand1, pickedRand2;

        srand((unsigned) time(nullptr));

        // Do this half as many times as the vector has elements
        // start i at 1 so that it doesn't execute for 1 length vectors
        for (int i = 1; i <= (copyVec.size() / 2); ++i) {

            randIndex1 = rand() % copyVec.size();
            randIndex2 = rand() % copyVec.size();
            // Check if we have picked these indices already
            pickedRand1 = find(pickedNums.begin(), pickedNums.end(), randIndex1) != pickedNums.end();
            pickedRand2 = find(pickedNums.begin(), pickedNums.end(), randIndex2) != pickedNums.end();

            // While we've picked either index already or they're equal
            while (pickedRand2 || pickedRand1) {

                // If randIndex1 is picked already, pick again
                if (pickedRand2) {
                    randIndex2 = rand() % copyVec.size();
                }
                // If randIndex1 is picked already, pick again
                if (pickedRand1) {
                    randIndex1 = rand() % copyVec.size();
                }
                // Check again if we have unpicked indices
                pickedRand1 = find(pickedNums.begin(), pickedNums.end(), randIndex1) != pickedNums.end();
                pickedRand2 = find(pickedNums.begin(), pickedNums.end(), randIndex2) != pickedNums.end();
            }
            // Add selected indices to set of indices we have swapped already
            pickedNums.push_back(randIndex1);
            pickedNums.push_back(randIndex2);

            // Three line swap to swap items at each index
            swapItem = copyVec[randIndex1];
            copyVec[randIndex1] = copyVec[randIndex2];
            copyVec[randIndex2] = swapItem;
        }

        // Return randomized vector
        return copyVec;
    }

    // Method to randomize dataVec by Zach Vanzura
    vector<T> randomZV(vector<T> copyVec) {
        // split vector in half
        vector<T> firstHalfVec (copyVec.begin(), (copyVec.begin() + copyVec.size() / 2));
        vector<T> secondHalfVec (copyVec.begin() + copyVec.size() / 2, copyVec.end());
        T temp;
        // get two random numbers within the range of the sizes of the vectors
        int rand1 = getRandomNumber(firstHalfVec);
        int rand2 = getRandomNumber(secondHalfVec);

        // ensures numRepeats isn't 0
        int numRepeats = 1 + getRandomNumber(copyVec);

        // shuffles each half a random number of times up to the total size of the vector.
        for (int i = 0; i < numRepeats; ++i){
            for (int v1 = 0; v1 < firstHalfVec.size(); ++v1){
                //get two random numbers and swap the first for the second
                temp = firstHalfVec[v1];
                firstHalfVec[v1] = firstHalfVec[rand1];
                firstHalfVec[rand1] = temp;
                rand1 = getRandomNumber(firstHalfVec);
            }
            for (int v2 = 0; v2 < secondHalfVec.size(); ++v2){
                //get two random numbers and swap the first for the second
                temp = secondHalfVec[v2];
                secondHalfVec[v2] = secondHalfVec[rand2];
                secondHalfVec[rand2] = temp;
                rand2 = getRandomNumber(secondHalfVec);
            }
        }
        //puts the two half vectors back into the original vector in alternating order
        //like shuffling a deck of cards
        for (int i = 0; i < firstHalfVec.size(); ++i){
            copyVec[i * 2] = firstHalfVec[i];
            copyVec[i * 2 + 1] = secondHalfVec[i];
        }
        return copyVec;
    }

    //helper function for randomZV returns random number in range of vecor size
    int getRandomNumber(vector<T> vec){
        return rand() % vec.size();
    }

    // Sorts vector using c++ default sorting from least -> greatest
    void sortVector() {
        sort(dataVec.begin(), dataVec.end());
    }

    // Adds passed item to vector
    void addItem(T item) {
        dataVec.push_back(item);
    }

    void addVector(vector<T> copyVec) {
        dataVec = copyVec;
    }

    // Adds multiple items to vector passed as initializer_list e.g."addItems({34, 35, 47, 23})" <-notice the curly braces
    void addItems(initializer_list<T> lstItems) {
        for (T item : lstItems) {
            dataVec.push_back(item);
        }
    }

    // Returns the size of the vector
    int getSize() {
        return dataVec.size();
    }

    // Returns a boolean stating if element matching passed item was removed from vector
    // if item is not found in vector, returns false
    bool removeItem(T item) {
        int index = findItem(item);
        // if item was found at valid index
        if (index != -1) {
            dataVec.erase(dataVec.begin() + index);
            return true;
        }
        // item was not found in vector
        return false;
    }

    // Returns boolean stating if element at index was removed from vector
    // if index is invalid, returns false
    bool removeIndex(int index) {
        if (index >= 0 && index < dataVec.size()) {
            dataVec.erase(dataVec.begin() + index);
            return true;
        }
        // Index was out of bounds
        return false;
    }

    // Returns the vector's element at the passed index
    // if index is out of bounds, returns element at index 0
    T getItem(int index) {
        // Check if index in bounds
        if (index >= 0 && index < dataVec.size()) {
            return dataVec[index];
        }
        // Index was out of bounds
        return dataVec[0];
    }

    // Returns the index of the passed item in dataVec
    // if item is not found, returns -1 as a flag value
    int findItem(T item) {
        // Iterate through vector and check for item
        for (int i = 0; i < dataVec.size(); ++i) {
            if (dataVec[i] == item) {
                // Item found, return index
                return i;
            }
        }
        // Item not found, return -1
        return -1;
    }


    // Overload insertion operator for printing to cout
    friend ostream& operator<<(ostream& os, DataList const & dl) {
        stringstream returnSS;
        // Add each item and a comma to the string to be returned
        for (T item : dl.dataVec) {
            returnSS << item << ", ";
        }
        // Substring to remove last comma, looks nicer
        string returnStr = returnSS.str();
        return os << returnStr.substr(0, returnStr.length() - 2);
    }

};

#endif //M2AP_DATALIST_H
