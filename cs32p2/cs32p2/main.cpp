//
//  main.cpp
//  cs32p2
//
//  Created by Darren Wu on 1/23/21.
//

#include <iostream>
#include <cassert>
#include "Sequence.h"

int main() {
    // insert code here...
    Sequence s;
    assert(s.insert(0, "s") == 0);
    assert(s.insert(0, "y")==0);
    
    assert(s.insert(2,"4")==2);
    assert(s.insert(3,"5")==3);
    
    assert(s.insert(1,"33")==1);
    assert(s.insert(4,"233") == 4);
    
    assert(s.insert("a")==0);
    assert(s.insert("a")==0);
    
    assert(s.erase(0));
    assert(s.erase(4));
    assert(s.erase(1));
    
    
    assert(s.find("ss")== -1);
    assert(s.find("s") == 2);
    
    assert(s.insert("a")==0);  //insert with no pos
    assert(s.insert("a")==0);  //duplicate insert no pos
    s.dump();
    assert(s.remove("a")==3);
    assert(s.insert("a"));
    assert(s.remove("s")==1);
    assert(s.remove("233")==1);
    s.dump();
    
    std::string x = "ten";
    assert(s.get(0,x) && x == "33");
    
    Sequence s1;
    Sequence s2;
    
    s1.insert("a");
    s1.insert("a");
    s1.insert("a");
    s1.insert("b");
    s1.insert(3,"c");
    s1.insert("b");
    s1.insert("x");
    s1.insert("x");
    
    s2.insert("b");
    s2.insert("b");
    s2.insert(1,"c");
    
    
    s1.dump();
    s2.dump();
    
    Sequence s8;
    s8.insert(0, "paratha");
    s8.insert(0, "focaccia");
    Sequence s9;
    s9.insert(0, "roti");
    s8.swap(s9);
    assert(s8.size() == 1  &&  s8.find("roti") == 0  &&  s9.size() == 2  &&
    s9.find("focaccia") == 0  &&  s9.find("paratha") == 1);

    
    std::cerr<<subsequence(s1, s2)<<std::endl;
    std::cerr<<subsequence(s2, s1)<<std::endl;
    
    s2.insert("a");
    
    s2.dump();
    std::cerr<<subsequence(s1, s2)<<std::endl;
    
    s2.insert("dd");
  
    s2.dump();
    std::cerr<<subsequence(s1, s2)<<std::endl;
    
    Sequence s3;
    Sequence s4;
    
    for(int i = 0; i<8;i++){
        s3.insert("a");
    }
    for(int i = 0; i<2;i++){
        s4.insert("b");
    }
    interleave(s3, s4, s3 );
    s3.dump();

    
    
    
    
    
    
    
    
    
    
   
    



   
    //s.dump();
}
