//
//  main.cpp
//  cs32hw5
//
//  Created by Darren Wu on 3/10/21.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

struct Node{
    Node* parent;
    Node* leftChild;
    Node* rightChild;
    
    int value;
};
