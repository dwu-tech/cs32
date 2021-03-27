//
//  main.cpp
//  cs32h2p1
//
//  Created by Darren Wu on 1/29/21.
//

#include <iostream>
#include <stack>
using namespace std;

class Coord
        {
          public:
            Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
            int r() const { return m_row; }
            int c() const { return m_col; }
          private:
            int m_row;
            int m_col;
        };

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    Coord start(sr, sc);
    Coord end(er, ec);
    stack<Coord> list;
    list.push(start);
    maze[sr][sc] = '#';
    
    while(!list.empty()){
        Coord temp = list.top();
        list.pop();
        if(temp.r() == er && temp.c() == ec){
            return true;
        }
        if(maze[temp.r()-1][temp.c()] == '.'){
            list.push(Coord(temp.r()-1,temp.c()));
            maze[temp.r()-1][temp.c()] = '#';
        }
        if(maze[temp.r()][temp.c()+1] == '.'){
            list.push(Coord(temp.r(),temp.c()+1));
            maze[temp.r()][temp.c()+1] = '#';
        }
        if(maze[temp.r()+1][temp.c()] == '.'){
            list.push(Coord(temp.r()+1,temp.c()));
            maze[temp.r()+1][temp.c()] = '#';
            
        }
        if(maze[temp.r()][temp.c()-1] == '.'){
            list.push(Coord(temp.r(),temp.c()-1));
            maze[temp.r()][temp.c()-1] = '#';
            
        }
    }
    return false;
}



int main()
        {
            string maze[10] = {
                "XXXXXXXXXX",
                "X........X",
                "XX.X.XXXXX",
                "X..X.X...X",
                "X..X...X.X",
                "XXXX.XXX.X",
                "X.X....XXX",
                "X..XX.XX.X",
                "X...X....X",
                "XXXXXXXXXX"
            };

            if (pathExists(maze, 10,10, 6,4, 1,1))
                cout << "Solvable!" << endl;
            else
                cout << "Out of luck!" << endl;
        }
