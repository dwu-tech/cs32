//
//  main.cpp
//  cs32testmt1
//
//  Created by Darren Wu on 1/28/21.
//

#include <iostream>
#include <cassert>
using namespace std;

class Triangle {
public:
 Triangle() {
 p = new Point[3];
 }
 Triangle(int x1,int y1,int x2, int y2,int x3,int y3) {
     p = new Point[3];
     p[0].x = x1; p[0].y = y1;
     p[1].x = x2; p[1].y = y2;
     p[2].x = x3; p[2].y = y3;
 }
~Triangle() {
    delete [] p;
    
}
    Triangle(Triangle& t){
        p = new Point[3];
        for(int i = 0;i<3;i++){
            p[i] = t.p[i];
        }
    }
    Triangle& operator=(const Triangle& t){
        Point* s = new Point[3];
        for(int i = 0; i<3;i++){
            s[i] = t.p[i];
        }
        return *this;
    }
    private:
    struct Point {
 int x,y;
 Point(int px=0,int py=0): x(px), y(py) { }
 };
 Point *p;
};
int main() {
 Triangle *array[3];
 array[0] = new Triangle(1,1,1,3,3,1);
 array[1] = new Triangle(2,2,2,6,6,2);
 array[2] = new Triangle(3,3,3,9,9,3);
 Triangle c2 = *array[0];
 c2 = *array[1];
 for(int i=0;i<3;i++)
 delete array[i];
    cerr<<"we good"<<endl;
}



