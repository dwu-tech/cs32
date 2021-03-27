//
//  main.cpp
//  cs32mt2p1
//
//  Created by Darren Wu on 2/23/21.
//


#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AFTER THE END OF THE removeEverySecond IMPLEMENTATION


template<template<class> class T, typename val>
void removeEverySecond(T<val> &substring, typename T<val>::iterator it){
    for(;it != substring.end();){
        it = erase(it);
        it++;
    }
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT BEFORE THE START OF THE removeEverySecond IMPLEMENTATION

int main()
{
    string a1[9] = { "30", "80", "70", "20", "60", "10", "90", "40", "50" };
    string expected1[6] = { "30", "80", "70", "60", "90", "50" };
    int a2[9] = { 30, 80, 70, 20, 60, 10, 90, 40, 50 };
    int expected2[5] = { 30, 80, 20, 10, 40 };

    vector<string> v1(a1, a1+9);  // construct v1 from the array
    //removeEverySecond(v1, v1.begin()+3);  // starting at position 3, the "20"
    assert(v1.size() == 6);
      // std::equal returns true if the values at corresponding positions
      // in the two ranges are equal
    assert(std::equal(v1.begin(), v1.end(), expected1, expected1+6));
    cout << "Passed test 1" << endl;

    vector<int> v2(a2, a2+9);
    //removeEverySecond(v2, v2.begin()+2);  // starting at position 2, the 70
    assert(v2.size() == 5);
    assert(std::equal(v2.begin(), v2.end(), expected2, expected2+5));
    cout << "Passed test 2" << endl;
    
    list<string> l1(a1, a1+9);
    list<string>::iterator p1 = l1.begin();
    for (int k = 0; k < 3; k++)
        p1++;
    //removeEverySecond(l1, p1);  // starting at position 3, the "20"
    assert(l1.size() == 6);
    assert(std::equal(l1.begin(), l1.end(), expected1, expected1+6));
    cout << "Passed test 3" << endl;
    
    list<int> l2(a2, a2+9);
    list<int>::iterator p2 = l2.begin();
    for (int k = 0; k < 2; k++)
        p2++;
    //removeEverySecond(l2, p2);  // starting at position 2, the 70
    assert(l2.size() == 5);
    assert(std::equal(l2.begin(), l2.end(), expected2, expected2+5));
    cout << "Passed test 4" << endl;
}
