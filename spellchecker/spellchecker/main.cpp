//
//  main.cpp
//  spellchecker
//
//  Created by Darren Wu on 3/7/21.
//

#include <iostream>
#include "StudentSpellCheck.h"
#include <string>
#include <vector>
using namespace std;

int main(){
    vector<string> vec;
    StudentSpellCheck s;
    s.load("/Users/darren/desktop/dictionary.txt");
    if(s.spellCheck("gog",10, vec)){
        cerr<<"It is  a word"<<endl;
    }
    if(!vec.empty()){
        vector<string>::iterator it;
        cerr<<"Suggestions Are "<<endl;
        for(it = vec.begin();it!=vec.end();it++){
            //cerr<<(*it)<<endl;
        }
       
    }
    else{
        cerr<<"vectempty"<<endl;
    }
    
    std::vector<SpellCheck::Position> problems;
    s.spellCheckLine("rose blaze", problems);
   
    
}
