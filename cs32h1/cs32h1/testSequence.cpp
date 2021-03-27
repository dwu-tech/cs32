//
//  testSequence.cpp
//  cs32h1
//
//  Created by Darren Wu on 1/14/21.
//


#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;


int main()
{
    Sequence s;
    assert(s.insert(0, 10) == 0);
    assert(s.insert(0, 20)==0);
    assert(s.insert(3) == 0);
    assert(s.size() == 3);
    s.dump();
    ItemType x = 999;
    s.set(0,x);
    s.dump();
    assert(s.find(x) == 0);
    assert(s.get(0,x));
    assert(s.get(0, x) && x == 999);
    assert(s.get(1, x) && x == 20);
    ItemType t = 20;
    assert(s.remove(t) == 1);
    assert(s.erase(0) == true);
    s.dump();
 
 
     Sequence s1;
     s1.insert(0, 1);
     s1.insert(1, 3);
     s1.insert(2, 4);
     s1.insert(3, 2);
     s1.insert(4, 5);

     Sequence s2;
     s2.insert(17);
     s2.insert(26);
     s2.insert(2);

     s1.swap(s2);

     s1.dump();
     cerr << endl;
     s2.dump();
     cerr << "Passed all tests" << endl;
}
  
