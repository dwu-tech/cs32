#ifndef ACTOR_H_
#define ACTOR_H_

#define _USE_MATH_DEFINES
 
#include <cmath>
#include "GraphObject.h"
#include <string>
using namespace std;

class StudentWorld;

const int LEFT_EDGE = ROAD_CENTER-(ROAD_WIDTH/2);
const int RIGHT_EDGE = ROAD_CENTER + (ROAD_WIDTH/2);

class Actor: public GraphObject{
public:

    Actor(int IID,double x, double y, int dir, double size, unsigned int depth, int speed, bool alive, StudentWorld* s);
    virtual void doSomething(){
        
    };
    int getSpeed();
    void setSpeed(int s);
    bool isAlive();
    void setAlive(bool b);
    StudentWorld* getWorld();
    
private:
    
    int m_speed;
    bool m_alive;
    StudentWorld* m_sWorld;
   
    
};

class GhostRacer: public Actor{
public:
   
    GhostRacer(int IID,double x, double y, int dir, double size, unsigned int depth, int speed, bool alive, StudentWorld* s);
    virtual void doSomething();
    int getHealth();
    void setHealth(int h);
    int getSprays();
    void setSprays(int s);
    
private:
    void movementAlgorithm();
    int m_health;
    int m_sprays;
};

class BorderLine: public Actor{
public:
   
    BorderLine(int IID,double x, double y, int dir, double size, unsigned int depth,int speed, bool alive,StudentWorld*s);
    virtual void doSomething();
private:
    
};


class Pedestrian: public Actor
{
public:
    virtual void doSomething(){
        std::cout<<"ten"<<std::endl;
    }
};
class Goodie: public Actor
{
public:
    Goodie(int IID,double x, double y, int dir);

};



    


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_

