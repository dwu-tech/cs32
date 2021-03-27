//
//  testScoreList.cpp
//  cs32h1
//
//  Created by Darren Wu on 1/16/21.
//


#include <stdio.h>
#include <cassert>
#include <iostream>

#include "ScoreList.h"

using namespace std;

int main(){
    
    ScoreList s;
    
    assert(s.size() == 0);
    assert(s.add(0));
    assert(s.add(4));
    assert(s.add(8));
    assert(s.add(100));
    assert(s.add(12));
    assert(!s.add(103));
    assert(!s.add(-1));
    assert(s.size() == 5);
    assert(s.maximum() == 100);
    assert(s.minimum() == 0);
    assert(s.remove(100));
    assert(s.remove(0));
    assert(!s.remove(7));
    assert(s.maximum() == 12);
    assert(s.minimum() == 4);
    
    
    cerr << "All tests succeed" << endl;
}


