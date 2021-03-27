//
//  main.cpp
//  cs32h2p3
//
//  Created by Darren Wu on 1/30/21.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <cctype>
using namespace std;

bool evalPfix(string postfix, const bool values[]);

int evaluate(string infix, const bool values[], string& postfix, bool& result){
    
    postfix = "";
    stack<char> oStack;
    int numCount = 0;
    int pCount = 0; //parentheses
    for(int i = 0; i<infix.size(); i++){
        switch (infix[i]){
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':{
                numCount++;
                int j=i;
                while(j>0 && infix[j-1] == ' '){
                    j--;
                }
                if(j>0 && ((isdigit(infix[j-1]) || infix[j-1] == ')'))){
                    return 1;
                }
                postfix+=infix[i];
                break;
            }
            case '(':{
                int j = i;
                while(j>0 && infix[j-1] == ' '){
                    j--;
                }
                if( j>0&&isdigit(infix[j-1])){
                    return 1;
                }
                oStack.push(infix[i]);
                pCount++;
                //cerr<<pCount<<endl;
                break;
            }
            case '!':{
                oStack.push(infix[i]);  //unary, can have double !!
                break;
                /*if(oStack.empty()){
                    oStack.push(infix[i]);
                    break;
                }
                while(!oStack.empty() && oStack.top()!= '('){
                    if(infix[i] == '!'){
                        if(oStack.top() == '!'){
                            postfix += oStack.top();
                            oStack.pop();
                        }
                        else{break;}
                    }
                    oStack.push(infix[i]);
                    break;
                }
            }*/
            }
            case '&':
            case '|':{
                int j = i;
                while(j>0 && (infix[j-1] == ' ' || infix[j-1] == ')')){
                    j--;
                }
               
                if(j==0 || !isdigit(infix[j-1])){
                    return 1;
                }
                
                j = i;
                
                while(j<infix.size() && (infix[j+1] == ' ' || infix[j+1] == '(' || infix[j+1] == '!' )){
                    j++;
                }
                
                if(j == infix.size() || !isdigit(infix[j+1])){
                    return 1;
                }
                if(oStack.empty()){
                    oStack.push(infix[i]);
                    break;
                }
                while(!oStack.empty() && oStack.top()!= '('){
                    if(infix[i] == '!'){
                        if(oStack.top() == '!'){
                            postfix += oStack.top();
                            oStack.pop();
                        }
                        else{break;}
                    }
                    
                   
                    
                    if(infix[i] == '&'){
                        if(oStack.top() == '!' || oStack.top() == '&'){
                            postfix += oStack.top();
                            oStack.pop();
                        }
                        else{break;}
                    }
                    if(infix[i] == '|'){
                        if(oStack.top() == '!' || oStack.top() == '&'||oStack.top() == '|'){
                            postfix += oStack.top();
                            oStack.pop();
                        }
                        else{break;}
                    }
                }
                oStack.push(infix[i]);
                break;
            }
            case ')':{
                pCount--;
                while(oStack.top()!='('){
                    postfix += oStack.top();
                    oStack.pop();
                }
            }
            case ' ':{
                break;
            }
            default:{
                return 1;
            }
        }
   
    }
    //cerr<<pCount<<endl;
    if(pCount !=0 || numCount == 0){
        
        return 1;
    }
    while(!oStack.empty()){
        if(oStack.top() == '('){
            oStack.pop();
        }
        
        else{
            postfix += oStack.top();
            oStack.pop();
        }
    }
    
    result = evalPfix(postfix, values);
    return 0;
}

 bool evalPfix(string postfix, const bool values[]){
     
    bool orand1;
    bool orand2;
    bool orand0;
    stack<bool> oStack;
    for(int i = 0; i<postfix.size();i++){
        
        if(isdigit(postfix[i])){
            oStack.push(values[postfix[i]-'0']);
        }
        
        if(postfix[i] == '!'){
            orand0 = oStack.top();
            oStack.pop();
            oStack.push(!orand0);
        }
        if(postfix[i] == '&'){
            orand2 = oStack.top();
            oStack.pop();
            orand1 = oStack.top();
            oStack.pop();
            oStack.push(orand1 && orand2);
            
        }
        if(postfix[i] == '|'){
            orand2 = oStack.top();
            oStack.pop();
            orand1 = oStack.top();
            oStack.pop();
            oStack.push(orand1 || orand2);
            
        }
        
    }
    return oStack.top();
}



int main()
       {
           bool ba[10] = {
             //  0      1      2      3      4      5      6      7      8      9
               true,  true,  true,  false, false, false, true,  false, true,  false
           };
           string pf;
           bool answer;
           
          
           assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
           assert(evaluate("8|", ba, pf, answer) == 1);
           assert(evaluate(" &6", ba, pf, answer) == 1);
           assert(evaluate("4 5", ba, pf, answer) == 1);
           assert(evaluate("01", ba, pf, answer) == 1);
           assert(evaluate("()", ba, pf, answer) == 1);
           assert(evaluate("()4", ba, pf, answer) == 1);
           assert(evaluate("2(9|8)", ba, pf, answer) == 1);
           assert(evaluate("2(&8)", ba, pf, answer) == 1);
           assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
           assert(evaluate("x+5", ba, pf, answer) == 1);
           assert(evaluate("", ba, pf, answer) == 1);
           assert(evaluate("2|3|4", ba, pf, answer) == 0
                                  &&  pf == "23|4|"  &&  answer);
           assert(evaluate("2|(3|4)", ba, pf, answer) == 0
                                  &&  pf == "234||"  &&  answer);
           assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
                                  &&  pf == "43!03&&|"  &&  !answer);
           assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
           ba[2] = false;
           ba[9] = true;
           assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
           assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
           cout << "Passed all tests" << endl;
       }
