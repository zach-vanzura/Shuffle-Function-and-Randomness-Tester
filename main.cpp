//
// Created by Zach Vanzura on 2/8/24.
//

// This already brings in std namespace and <iostream> (and other stuff)
#include <algorithm>
#include <vector>
#include "DataList.h"

bool testDataList();
template<typename T>
void testRandomness(vector<T> origVec);

int main() {

    if (testDataList()) {
        cout << "All tests passed for DataList class" << endl;
    }

    vector<int> myVec = {1,2,3,4,5,6,7,8,9,10};

    testRandomness<int>(myVec);

    return 0;
}

// Method for testing randomness
template<typename T>
void testRandomness(vector<T> origVec){
    DataList<T> dl;
    vector<T> dataVecCopyJD = origVec;
    vector<T> dataVecCopyZV = origVec;
    vector<T> rotatedVec;
    // Vector of 0s, same size as vector passed as argument
    // Type is 'long long' to account for possible huge values
    vector<long long> sameIndexCountsJD(origVec.size(), 0);
    vector<long long> sameIndexCountsZV(origVec.size(), 0);
    int rotatedJD = 0;
    int rotatedZV = 0;

    // Runs 1,000,000 times, 1e6 takes about 1 minute to run but does work.
    for (int i = 0; i < 1e6; ++i){
        //Jacks Random function
        dataVecCopyJD = dl.randomJD(dataVecCopyJD);
        // count amount of times each index is in its actual location
        for (int j = 0; j < dataVecCopyJD.size(); ++j){
            if (origVec[j] == dataVecCopyJD[j]){
                sameIndexCountsJD[j]++;
            }
        }

        rotatedVec = dataVecCopyJD;
        for (int k = 0; k < dataVecCopyJD.size(); ++k){
            rotate(dataVecCopyJD.begin(),dataVecCopyJD.begin() + k, dataVecCopyJD.end());
            if (origVec == rotatedVec) {
                ++rotatedJD;
            }
        }

        // repeating testing on ZV random function
        dataVecCopyZV = dl.randomZV(dataVecCopyZV);
        for (int j = 0; j < dataVecCopyZV.size(); ++j){
            if (origVec[j] == dataVecCopyZV[j]){
                sameIndexCountsZV[j]++;
            }
        }

        rotatedVec = dataVecCopyZV;
        for (int k = 0; k < dataVecCopyZV.size(); ++k){
            rotate(dataVecCopyZV.begin(),dataVecCopyZV.begin() + k, dataVecCopyZV.end());
            if (origVec == rotatedVec) {
                ++rotatedZV;
            }
        }
    }

    int index = 1;
    cout << "Jack's Shuffle Function:" << endl;
    for (int item : sameIndexCountsJD) {
        cout << "Index " << index << ": " << item << endl;
        ++index;
    }
    cout << "Times Jack's Vector was rotated: " << rotatedJD;
    cout << endl << endl;

    index = 1;
    cout << "Zach's Shuffle Function:" << endl;
    for (int item : sameIndexCountsZV) {
        cout << "Index " << index << ": " << item << endl;
        ++index;
    }
    cout << "Times Zach's Vector was rotated: " << rotatedZV;
    cout << endl;
}

bool testDataList() {
    bool passed = true;

    DataList<string> dl;

    // Add 4 items and ensure size
    dl.addItems({"test1","test0","test4","test2"});
    if (dl.getSize() != 4) {
        cout << "FAILED addItems method" << endl;
        passed = false;
    }

    // Add item and ensure size
    dl.addItem("test3");
    if (dl.getSize() != 5) {
        cout << "FAILED addItem (singular) method" << endl;
        passed = false;
    }

    // Ensure sorting by checking first and last element
    dl.sortVector();
    if (dl.getItem(0) != "test0" && dl.getItem(4) != "test4") {
        cout << "FAILED sortVector method" << endl;
        passed = false;
    }

    // Check for invalid finding and valid finding
    if(dl.findItem("dogfish") != -1 && dl.findItem("test0") != 0) {
        cout << "FAILED findItem method" << endl;
        passed = false;
    }

    // Check if removing at bad index works
    if(dl.removeIndex(100)) {
        cout << "FAILED passed bad index to removeIndex method" << endl;
        passed = false;
    }

    // Check if removing valid element works
    if(!dl.removeItem("test4")) {
        cout << "FAILED removeItem method couldnt remove valid item from vector" << endl;
        passed = false;
    }

    return passed;
}