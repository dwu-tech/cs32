//
//  ScoreList.cpp
//  cs32h1
//
//  Created by Darren Wu on 1/15/21.
//

#include <stdio.h>

#include "ScoreList.h"
#include <limits>

ScoreList::ScoreList(){
    
}

bool ScoreList:: add(unsigned long score){
    if(score>100 || score <0 || s.size()>= DEFAULT_MAX_ITEMS){
        return false;
    }
    s.insert(score);
    return true;
}

bool ScoreList:: remove(unsigned long score){
    return (s.erase(s.find(score)));
}

int ScoreList:: size() const{
    return s.size();
}

unsigned long ScoreList::minimum() const{
    if(s.empty()){
        return NO_SCORE;
    }
    ItemType min;
    s.get(0, min);
    return min;
    
}

unsigned long ScoreList:: maximum() const{
    if(s.empty()){
        return NO_SCORE;
    }
    ItemType max;
    s.get(s.size()-1, max);
    return max;
}

