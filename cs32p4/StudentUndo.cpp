#include "StudentUndo.h"
#include <stack>
#include <iostream>
using namespace std;
//hello
Undo* createUndo()
{
    return new StudentUndo;
}

void StudentUndo::submit(const Action action, int row, int col, char ch) {
    // TODO
    fullUndo f;       //create struct with information from parameters
    f.m_a = action;
    f.m_row = row;
    f.m_col = col;
    f.m_s = ch;
    f.m_countInserts = 0;
    
    
    if(undoStack.empty() && f.m_a == Undo::Action::INSERT){    //if insert and first operation
        f.m_countInserts++;
        undoStack.push(f);
    }
    else if(f.m_a == Undo::Action::INSERT && ch == ' '){  //space as a seperator, new line
        //f.m_countInserts = 0;
        f.m_countInserts++;
        undoStack.push(f);
    }
    //if inserting, and previous stack top of stack was insert, add on to count delete
    else if(f.m_a == Undo::Action::INSERT && !undoStack.empty() && undoStack.top().m_a == Undo::Action::INSERT){
        undoStack.top().m_countInserts++;
    }
    /*else if(f.m_a == Undo::Action::DELETE && !undoStack.empty() && undoStack.top().m_a == Undo::Action::DELETE){
        undoStack.top().m_s = undoStack.top().m_s +f.m_s;
    }*/
    
    else{
        undoStack.push(f);
    }
    
  
    //undoStack.push(f);
    
}

StudentUndo::Action StudentUndo::get(int& row, int& col, int& count, std::string& text) {
    if(undoStack.empty()){
        return Undo::Action::ERROR;
    }
    fullUndo temp_f = undoStack.top();
  
    row = temp_f.m_row;
    col = temp_f.m_col;
    switch (temp_f.m_a) {
        case Undo::INSERT:
            
            text  = "";
            count = temp_f.m_countInserts;
            undoStack.pop();
            
            return Undo::Action::DELETE;
            break;
        case Undo::SPLIT:
            count = 1;
            text = "";
            undoStack.pop();
            return Undo::Action::JOIN;
            break;
        case Undo::DELETE:
            count = 1;
            text = temp_f.m_s;
            undoStack.pop();
            return Undo::Action::INSERT;
            break;
        case Undo::JOIN:
            count = 1;
            text = "";
            undoStack.pop();
            return Undo::Action::SPLIT;
            break;
            
        default:
            return Undo::Action::ERROR;
            break;
    }
    
    return Action::ERROR;
}

void StudentUndo::clear() {
    while(!undoStack.empty()){
        undoStack.pop();        //clear undo stack
    }
    
}


