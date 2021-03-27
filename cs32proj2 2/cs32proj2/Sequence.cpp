//
//  Sequence.cpp
//  cs32p2
//
//  Created by Darren Wu on 1/23/21.
//

#include <stdio.h>
#include <iostream>
#include "Sequence.h"

Sequence::Sequence(){ //constructor
    m_lSize = 0;
    head = nullptr;
    tail = nullptr;
}

Sequence::~Sequence(){ //destructor
    
    Node *p;
    p = head;
    while(p!=nullptr){
        Node *n = p;
        p = p->next;
        delete n;
       
    }
    
}

Sequence::Sequence(Sequence const &other){ //copy constructor
    m_lSize = 0;
    head = nullptr;
    tail = nullptr;
    
    Node*t = other.head;
    for(int i = 0; t!=nullptr; t=t->next,i++){
        insert(i,t->m_value);
    }
}


Sequence& Sequence::operator=(const Sequence &other){ //assignment operator
    if(&other!=this){
        Node* t = head;
        while(t!=nullptr){
            Node* t2 = t;;
            t = t->next;
            delete t2;
        }
        m_lSize = 0;
        head = nullptr;
        tail = nullptr;
    }
    
    Node* t = other.head;
    for(int i = 0; t!=nullptr; t=t->next,i++){
        insert(i, t->m_value);
    }
    return *this;
}


bool Sequence::empty() const{
    return (head == nullptr);
}

int Sequence::size() const{
    return m_lSize;
}

int Sequence::insert(int pos, const ItemType& value){  //insert into specific index function
    
    if(pos > m_lSize || pos < 0){   //check if valid index
        return -1;
    }

    if(head == nullptr){   //if empty
        
        head = new Node(value, tail, head);  //construct new node
        
        tail = head;     //both point only element in list
        
        m_lSize++;
        return pos;
    }
    
    //insert at beginning
    if(pos == 0){
        Node* p = new Node(value, nullptr, head);  //p->prev = nullptr,  p->next = head
        
        head->prev = p;  //reroute second element->prev to first
        head = p;       //set head to top
        
        m_lSize++;
        
        return pos;
    }
   
    if(pos == m_lSize){  //insert at end
        Node* p = new Node(value, tail, nullptr);
        
        tail->next = p;  //tail becomes second last, points to node p
        tail = p;        //move tail to the end
        
        m_lSize++;
        
        return pos;
    }
   
    else{  //insert into the middle
        
        Node* t = head;
        int count = 0;
        while(t != nullptr && count != pos){  //traverse to insert position
            t = t->next;
            count++;
        }
    
        Node* latest = new Node(value, t->prev, t); //prev point to current previous, next points to t
        
        t->prev->next = latest;  //prev node next points to the new node
        t->prev = latest;        //old current prev points to new
        
        m_lSize++;
        
        return pos;
    }
    
        return pos;
}


int Sequence::insert(const ItemType &value){
    int count = 0;
    for(Node* t = head; t!=nullptr; t = t->next,count++){  //iterate, insert at lowest position
        if(value<=t->m_value){
            insert(count, value);
            return count;
        }
    }
    insert(m_lSize,value);  //insert at the end if the rest are smaller
    return m_lSize-1;
    
}

bool Sequence::erase(int pos){   //erase function
    
    if(pos<0||pos>m_lSize||m_lSize==0){
        return false;
    }
    
    if(pos == 0){   //erase the beginning node
       
        if(m_lSize == 1){   //only node in sequence
            
            delete head;  //delete only node, set head and tail to null
            head = nullptr;
            tail = nullptr;
            m_lSize--;
            return true;

        }
        else{
            
            Node* t = head->next; //temp node is set to second node
            head->prev = nullptr;
            delete head;
            head = t;
            
            m_lSize--;
            return true;
            }
            
    }
    
    if(pos == m_lSize-1){  //delete the tail
        Node* t = tail->prev; //set temp to second last
        
        delete tail;
        tail = t;
        tail->next = nullptr;
        m_lSize--;
        
        return true;
    }
    
    
    
    Node* t = head;   //delete from middle
    
    int c = 0;
    while(c!=pos){  //iterate to position of delete node
        c++;
        t = t->next;
    }
    
    Node* t2 = t->prev; //set to node before delete node
    t2->next = t->next; //set next of the node before delete to the node that the current points to
    t->next->prev = t2;  //link the node after delete node to t2
    delete t;
  
    
    m_lSize--;
    
    
    return true;
}

int Sequence::remove(const ItemType &value){ //remove uses find and erase
    
    int rCount = 0;             //counts how many removes
    while(find(value)!=-1){     //uses find to look for value and erase until no more of value is left
        erase(find(value));
        rCount++;
    }
    return rCount;
}

bool Sequence::get(int pos, ItemType &value) const{
    if(pos<0 || pos>m_lSize){
        return false;
    }
    int pCount = 0;
    for(Node* t = head; t!=nullptr; t = t->next,pCount++){  //exit loop after getting value at pos
        if(pCount == pos){
            value = t->m_value;
            break;
        }
    }
    return true;
}

bool Sequence::set(int pos, const ItemType &value){
    if(pos<0 || pos> m_lSize){
        return false;
    }
    int pCount = 0;
    for(Node*t = head; t!=nullptr; t=t->next,pCount++){  //exits loop after setting value at pos
        if(pCount == pos){
            t->m_value = value;
            break;
        }
    }
    return true;
}

int Sequence::find(const ItemType &value) const{
    int count = 0;
    for(Node* t = head; t!=nullptr; t=t->next,count++){  //iterates through loop until value matches
        if(t->m_value == value){
            return count;
        }
    }
    return -1;
}

void Sequence::swap(Sequence &other){
    //swap uses temp variable to swap
    
    int tSize = m_lSize;
    this->m_lSize = other.m_lSize;
    other.m_lSize = tSize;
    
    Node*tHead = head;
    this->head = other.head;
    other.head = tHead;
    
    Node*tTail = tail;
    this->tail = other.tail;
    other.tail = tTail;
    
}
//non member functions

int subsequence(const Sequence& seq1, const Sequence& seq2){
    if(seq2.size() == 0 || seq1.size() == 0){  //either are empty
        return -1;
    }
    if(seq2.size()>seq1.size()){
        return -1;
    }
    ItemType seq1Val;
    ItemType seq2Val;
    
    for(int i = 0; i<seq1.size();i++){
        if(i+seq2.size()>seq1.size()){  //size2 +current index of size 1 is too big
            break;
        }
        
        int streak = 0;
        for(int j = 0; j<seq2.size();j++){  //iterate through seq2
            seq2.get(j,seq1Val);
            seq1.get(i+j, seq2Val);
            
            //std::cerr<<i+j<<" "<<j<<" "<<std::endl;
            //std::cerr<<seq2Val<<" "<<seq1Val<<std::endl;
            
            if(seq2Val!=seq1Val){
                streak = 0;
                break;
            }
            else if(seq2Val==seq1Val){
                //std::cerr<<streak<<std::endl;
                streak++;
                //std::cerr<<streak<<std::endl;
            }
        }
        if(streak == (seq2.size())){  //full subsequence found
            return i;
        }
    }
    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result){
    Sequence s;  //temp sequence to set to result at end
    
    int c1 = 0;  //count for both sequences
    int c2 = 0;
    
    if(seq1.empty()){
        result = seq2;
    }
    if(seq2.empty()){
        result = seq1;
    }
    
    //std::cerr<<seq1.size()<<" "<<seq2.size()<<std::endl;
    
    int seqCount = 0;
    while(c1<seq1.size()&&c2<seq2.size()){  //alternate inserting one by one until smaller of two is completed
        ItemType t1;
        ItemType t2;
        if(seq1.get(c1,t1)){
            s.insert(seqCount,t1);
            seqCount++;
            c1++;
        }
        if(seq2.get(c2,t2)){
            s.insert(seqCount,t2);
            seqCount++;
            c2++;
        }
       
        //std::cerr<<c1<< " "<<c2<<std::endl;
    }
    if(seq1.size()>seq2.size()){  //take larger of two and copy the rest over
        while(c1<seq1.size()){
            ItemType t1;
            if(seq1.get(c1,t1)){
                s.insert(seqCount,t1);
                seqCount++;
                c1++;
            }
            
        }
    }
    if(seq2.size()>seq1.size()){
        while(c2<seq2.size()){
            ItemType t2;
            if(seq1.get(c2,t2)){
                s.insert(seqCount,t2);
                seqCount++;
                c2++;
            }
            
        }
    }
    result = s;  //set result to temp variable
   
    
}

void Sequence::dump() const{
    std::cerr << "Start" << std::endl;
    std::cerr <<std::endl;
    
    Node* t = head;
    int count = 0;
    
    while(t != nullptr){
        std::cerr <<count << ": " << t->m_value << std::endl;
        t = t->next;
        count++;
    }
    
    std::cerr<<std::endl;
    std::cerr << "Size: " << m_lSize << std::endl;
    std::cerr<<std::endl;
    
   /* Node* temp2 = tail;    //check if tail nodes are linked, prev
    int count2 = 0;
    while(temp2!=nullptr){
        std::cerr<<count2 << ": " << temp2->m_value << std::endl;
        temp2 = temp2->prev;
        count2++;
    }*/
    
    std::cerr << "End" << std::endl << std::endl;
}
