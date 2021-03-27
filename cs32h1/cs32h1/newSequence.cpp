//
//  newSequence.cpp
//  cs32h1
//
//  Created by Darren Wu on 1/16/21.
//

#include <stdio.h>
#include <iostream>
#include "newSequence.h"
using namespace std;

Sequence::Sequence(){
    m_arr = new ItemType[DEFAULT_MAX_ITEMS];
    m_nItems = 0;
    m_max = DEFAULT_MAX_ITEMS;
}
Sequence::Sequence(int s){
    m_arr = new ItemType[s];
    m_nItems = 0;
    m_max = s;
}
Sequence::~Sequence(){
    delete[] m_arr;
}
Sequence& Sequence::operator=(const Sequence& seq){
    if(this != &seq){
        delete[] m_arr;
        m_max = seq.m_max;
        m_nItems = seq.size();
        m_arr = new ItemType[size()];
        for(int i = 0; i<m_nItems;i++){
            this->m_arr[i] = seq.m_arr[i];
        }
    }
    return *this;
}

Sequence:: Sequence(const Sequence& seq){
    m_max = seq.m_max;
    m_nItems = seq.size();
    m_arr = new ItemType[size()];
    for(int i = 0; i<m_nItems;i++){
        this->m_arr[i] = seq.m_arr[i];
    }
}


bool Sequence::empty() const{
    return(m_nItems == 0);
}

int Sequence::size() const{
    return m_nItems;
}

int Sequence::insert(int pos, const ItemType &value){
    
    if(pos<0 || pos>size() || pos >= m_max){
       return -1;
    }
    else{
        for(int i = size(); i>pos; i--){
            m_arr[i] = m_arr[i-1];
        }
        m_arr[pos] = value;
        m_nItems++;
        return pos;
    }
}

int Sequence::insert(const ItemType &value){
    
    if(m_nItems >= m_max){
        return -1;
    }
    
    
    for(int p = 0; p<m_nItems;p++){
        if(value<=m_arr[p]){
            insert(p,value);
            return p;
        }
    }
    int pos = size();
    insert(pos,value);
    return pos;
}

bool Sequence::erase(int pos){
    if(0<=pos && pos<size()){
        for(int i = pos; i<size()-1;i++){
            m_arr[i] = m_arr[i+1];
        }
        m_nItems--;
        return true;
    }
    return false;
}

int Sequence::remove(const ItemType &value){
    int c = 0;
    for(int i = 0; i<size(); i++){
        if(m_arr[i] == value){
            erase(i);
            i--;
            c++;
        }
    }
    return c;
}

bool Sequence::get(int pos, ItemType &value) const{
    if(0<=pos&& pos<size()){
        value = m_arr[pos];
        return true;
    }
    return false;
}

bool Sequence::set(int pos, const ItemType &value){
    if(0<=pos&& pos<size()){
        m_arr[pos] = value;
        return true;
    }
    return false;
}

int Sequence::find(const ItemType &value) const{
    for(int i = 0; i<size(); i++){
        if(m_arr[i] == value){
            return i;
        }
    }
    return -1;
}

void Sequence::swap(Sequence &other){
    ItemType* t;
    t = other.m_arr;
    other.m_arr = this->m_arr;
    this->m_arr = t;
    
    int tSize = other.size();
    other.m_nItems = this->size();
    this->m_nItems = tSize;
    
    int tMax = other.m_max;
    other.m_max = this->m_max;
    this->m_max = tMax;
    
}
void Sequence::dump() const{
    //cerr<<m_nItems<<endl;
    //cerr<<m_max<<endl;
    for(int i = 0; i< m_nItems;i++){
        cerr<<m_arr[i];
    }
    
}

