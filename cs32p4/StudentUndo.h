#ifndef STUDENTUNDO_H_
#define STUDENTUNDO_H_

#include "Undo.h"
#include <stack>
using namespace std;

class StudentUndo : public Undo {
public:

    void submit(Action action, int row, int col, char ch = 0);
    Action get(int& row, int& col, int& count, std::string& text);
    void clear();

private:
    struct fullUndo{
        Action m_a;
        int m_row;
        int m_col;
        int m_countInserts;
        string m_s;
    };
    
    stack<fullUndo > undoStack;
    
    //int m_countInserts;
    
};

#endif // STUDENTUNDO_H_

