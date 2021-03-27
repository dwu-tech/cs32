//
//  main.cpp
//  finalpractice
//
//  Created by Darren Wu on 3/12/21.
//

#include <vector>
#include <iostream>
#include <unordered_set>
#include <string>
#include <list>
using namespace std;






class t{
};
struct BTNode {
 string val;
 BTNode* left;
 BTNode* right;

};

list<string> leftView(BTNode* root) {
    list<string> s = list<string>();
    if(root == nullptr){
        return s;
    }
    list<string> leftV = leftView(root->left);
    list<string> rightV = leftView(root->right);
    
    s.push_back(root->val);
    return s;
    
}

