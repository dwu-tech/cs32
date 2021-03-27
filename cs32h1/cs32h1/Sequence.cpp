//
//  Sequence.cpp
//  cs32h1
//
//  Created by Darren Wu on 1/14/21.
//

#include <stdio.h>
#include <iostream>
#include "Sequence.h"

// Create an empty sequence (i.e., one with no items)
Sequence::Sequence(){
    m_nItems = 0;
}

bool Sequence::empty() const{
    return(m_nItems == 0);
}

int Sequence::size() const{
    return m_nItems;
}

int Sequence::insert(int pos, const ItemType &value){
    
    if(pos<0 || pos>size() || pos >=DEFAULT_MAX_ITEMS){
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
    
    if(m_nItems >= DEFAULT_MAX_ITEMS){
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
    for(int i = 0; (i<this->size() && i<other.size());i++){
        ItemType t = this->m_arr[i];
        this->m_arr[i] = other.m_arr[i];
        other.m_arr[i] = t;
    }
    
    if(this->size()>other.size()){
        for(int i = other.size(); i<this->size(); i++){
            other.m_arr[i] = this->m_arr[i];
        }
    }
    else if(this->size()<other.size()){
        for(int i = this->size(); i<other.size();i++){
            this->m_arr[i] = other.m_arr[i];
        }
    }
    
    int t = other.size();
    other.m_nItems = this->size();
    this->m_nItems = t;
}
void Sequence::dump() const{
    for(int i = 0; i<m_nItems;i++){
        std::cerr<<m_arr[i]<< " ";
    }
    std::cerr<<std::endl;
}

