//
//  History.cpp
//  cs32
//
//  Created by Darren Wu on 1/8/21.
//

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#include "History.h"
#include "globals.h"

History::History(int rows, int cols){
    m_rows = rows;
    m_cols = cols;
    for(int i = 0; i<m_rows;i++){
        for(int j = 0; j<m_cols;j++){
            pFail[i][j] = 0;  //failed preach
        }
    }
}
bool History:: record(int r, int c){
    if(r<1||c<1||r>m_rows||c>m_cols){
        return false;
    }
    pFail[r-1][c-1] +=1; //0-n-1
    
    return true;
    
}
//finish display


void History::display() const{
   
    
    char grid[MAXROWS][MAXCOLS];
    int r, c;
   
    clearScreen();
    for(r = 0; r<m_rows; r++){
        for(c = 0; c<m_cols; c++){
            if(pFail[r][c] == 0){
                grid[r][c] = '.';
            }
            else if(pFail[r][c]<26){
                grid[r][c] = 'A'+(pFail[r][c]-1);
            }
            else{
                
                grid[r][c] = 'Z';
            }
        }
    }
    for (r = 0; r < m_rows; r++){
        for (c = 0; c < m_cols; c++){
                cout << grid[r][c];
        }
            cout << endl;
    }
    cout<< endl;

}

