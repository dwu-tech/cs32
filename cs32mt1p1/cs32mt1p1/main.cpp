//
//  main.cpp
//  cs32mt1p1
//
//  Created by Darren Wu on 1/28/21.
//

#include <iostream>
#include <cassert>
using namespace std;

class StringList
{
  public:
    StringList();
    // You may declare other member functions for your test code to call
    int insert(char c);
    void eraseEvens();
    void dump();
  private:
    struct Node
    {
      char  value;
      Node* next;
    };
    Node* head;  // points to first Node in the list
};

StringList::StringList()
{
  head = nullptr;
}

int StringList::insert(char c){
    if(head == nullptr){
        Node* temp = new Node();
        temp->value = c;
        temp->next = nullptr;
        head = temp;
        
    }
    else{
        Node* temp = new Node();
        temp->value = c;
        temp->next = head;
        head = temp;
    }
    
    return 0;
}
void StringList::dump(){
    Node* temp = head;
        int count = 0;
        
        while(temp != nullptr){
            std::cerr << "Node " << count << ": " << temp->value << std::endl;
            temp = temp->next;
            count++;
        }
}
// You may implement other member functions here for test purposes,
// but you will not turn them in as part of your submission.

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AFTER THE END OF THE eraseEvens IMPLEMENTATION

void StringList::eraseEvens(){
    if(head == nullptr){
        return;
    }
    if(head->next->next == nullptr){
        return;
    }
    if(head->next == nullptr){
        return;
    }
    
    int i = 0;
    int size = 0;
    for(Node* t = head; t!=nullptr&&t->next !=nullptr; t = t->next){
        size++;
    }
    for(Node* t = head; t!=nullptr&&t->next !=nullptr; t = t->next){
        
       
        if(size%2 ==1){
            Node* t2 = t->next;
            t->next = t2->next;
            delete t2;
            i--;
        }
        i++;
        if(size%2 ==0){
            
            
            Node* t2 = t->next;
            t->next = t2->next;
            delete t2;
            i--;
            }
            i++;
    }
}



// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT BEFORE THE START OF THE eraseEvens IMPLEMENTATION

int main()
{
  // You may put some code here for test purposes
    StringList* s = new StringList();
    s->insert('d');
    s->insert('a');
    s->insert('d');
    s->insert('a');
    s->insert('d');
    s->insert('a');
    
    
    s->eraseEvens();
    
    s->dump();
  cout << "All tests succeeded" << endl;
}
