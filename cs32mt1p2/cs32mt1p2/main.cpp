//
//  main.cpp
//  cs32mt1p2
//
//  Created by Darren Wu on 1/28/21.
//

#include <iostream>
#include <cassert>
using namespace std;

class Num
{
  public:
    Num(int i) : m_i(i) {
        
    }
    int geti() const {
        return m_i;
        
    }
  private:
    int m_i;
};

class Blah
{
  public:
    Blah(int i);
    ~Blah();
    Blah(const Blah& other);
  private:
    Num* m_num;
    int m_ii;
    int* m_eyes;
};
  
Blah::Blah(int i)
{
  m_num = new Num(i);
  m_ii = 2 * i;
  m_eyes = &m_ii;
}

Blah::~Blah(){
    delete m_num;
}

Blah::Blah(const Blah& other){
    this->m_num =  new Num(other.m_ii/2);
    this->m_ii = other.m_ii;
    this->m_eyes = other.m_eyes;
}
// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AFTER THE END OF THE DESTRUCTOR AND COPY CONSTRUCTOR
// IMPLEMENTATIONS



// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT BEFORE THE START OF THE DESTRUCTOR AND COPY CONSTRUCTOR
// IMPLEMENTATIONS

void test()
{
  Blah b1(3);
  Blah b2(b1);
}

int main()
{
  test();
  cout << "All tests succeeded" << endl;
}
