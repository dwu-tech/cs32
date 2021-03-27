//
//  Sequence.h
//  cs32p2
//
//  Created by Darren Wu on 1/23/21.
//

#ifndef Sequence_h
#define Sequence_h
#include <string>
using ItemType = std::string;

class Sequence
{
  public:
    Sequence();
    Sequence(Sequence const&other);
    ~Sequence();
    
    Sequence& operator = (const Sequence &other);
    
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    
    void dump() const;
    
  private:
    struct Node {
            Node(ItemType val, Node* prevNode, Node* nextNode){
                m_value = val;
                prev = prevNode;
                next = nextNode;
            };
        
            ItemType m_value;
            Node* prev;
            Node* next;
        };
    
    Node* head;
    Node* tail;
    int m_lSize;
};



int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif /* Sequence_h */
