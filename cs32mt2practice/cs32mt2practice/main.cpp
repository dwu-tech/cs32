#include <iostream>
#include <string>
#include <vector>
using namespace std;

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AFTER THE END OF THE dump IMPLEMENTATION

template <typename T>
void dump(T stuff){
    cout<<"**** DUMP: "<<stuff<<endl;
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT BEFORE THE START OF THE dump IMPLEMENTATION

int fact(int n){
    if(n == 0){
        return 1;
    }
    return n*fact(n-1);
}

int sumArr(int arr[], int n){
    if(n==0){
        return 0;
    }
    cout<<arr[n-1]<<endl;
    return arr[n-1] + sumArr(arr,n-1);
    
}
struct Node{
    int val;
    Node* next;
};

int biggest(Node* n){
    if(n->next == nullptr){
        return n->val;
    }
    int rest = biggest(n->next);
    return max(rest,n->val);
}

int countNums(int arr[],int size, int target){
    if(size == 0){
        return 0;
    }
    if(arr[0] == target){
        return 1+countNums(arr+1,size-1,target);
    }
    else{
        return countNums(arr+1,size-1,target);
    }
}
int findPos(Node* n,int target){
    if(n->next == nullptr){
        return -1;
    }
    if(n->val == target){
        return 0;
    }
    
    int pos = findPos(n->next,target);
    if(pos == -1){
        return -1;
    }
    else{
        return pos+1;
    }
}
int gcd(int m, int n){
    if(n == m){
        return n;
    }
    
    n = n-m;
    if(n<m){
        return gcd(n,m);
    }
    else{
        return gcd(m,n);
    }
}

#include <stack>
using namespace std;

bool balanced(const string &exp)
{
    stack<char> s;
    for(int i = 0; i<exp.size(); i++){
        if(exp[i] == '{' || exp[i] == '(' || exp[i] == '['){
            s.push(exp[i]);
        }
        if(exp[i] == '}'|| exp[i] == ')' || exp[i] == ']'){
            if(s.empty()){
                return false;
            }
            if((s.top() == '{' && exp[i] == '}')
               ||(s.top() == '[' && exp[i] == ']')
               ||(s.top() == '(' && exp[i] == ')')){
                s.pop();
            }
            else if((s.top() == '{' && exp[i] != '}')
               ||(s.top() == '[' && exp[i] != ']')
               ||(s.top() == '(' && exp[i] != ')')){
                return false;
            }
        }
    }
    if(!s.empty()){
        return false;
    }
    
    return true;
}
int main()
{
    const string ss = "(e)";
    if(balanced(ss)){
        cout<<"true"<<endl;
    }
    cout<<gcd(12,14)<<endl;
    int men [5] = {2,4,3,3,1};
    cout<<countNums(men,5,3)<<endl;
    
    cout<<fact(4)<<endl;
    
    
    string s = "Crouching Tiger";
    double d = 7;
    dump(s);
    dump(42);
    dump(d / 2);
    dump(s.substr(2, 4));
}
