//Darren Wu CS32 Project 3
//last uploaded 2/27 10:00
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
const int WHITE_LEFT_EDGE = LEFT_EDGE+(ROAD_WIDTH/3);
const int WHITE_RIGHT_EDGE = RIGHT_EDGE-(ROAD_WIDTH/3);

class Actor: public GraphObject{
public:

    Actor(int IID,double x, double y, int dir, double size, unsigned int depth, int speed, bool alive, StudentWorld* s);
    
    virtual void doSomething() = 0;
    virtual bool gotSprayed();
    
    double getSpeed() const;
    void setSpeed(double s);
    
    bool isAlive() const;
    void setAlive(bool b);
    
    bool isCAWActor() const;
    void setCAWActor(bool b);
    
    int getHSpeed() const;
    void setHSpeed(int n);
    
    StudentWorld* getWorld() ;
    int determineCurrentLane() const;   //returns the lane the actor who called the function is in
   
    bool determineOverlap(Actor* a, Actor* b);  //return true if two Actors overlap
    
    void moveActor();
    
private:
    
    double m_speed;
    int m_hSpeed;
    bool m_alive;
    bool m_cawActor;
    StudentWorld* m_sWorld;
   
    
};

class Agent:public Actor{
public:Agent(int IID,double x, double y, int dir, double size, unsigned int depth,int speed, bool alive,StudentWorld*s);
    
    int getHealth() const;
    void setHealth(int h);
    void damageHealth(int n);
    
    int getPlan() const;
    void setPlan(int n);

private:
    int m_health;
    int m_plan;
};

class GhostRacer: public Agent{
public:
    GhostRacer(StudentWorld* s);
    virtual void doSomething();
    
    int getSprays();
    void addSprays(int s);
    
    void slick();    //spins the Ghost Racer when it runs over oil
    void heal(int n);
    
    
private:
    void movementAlgorithm();
    int m_sprays;
};

class nCAWActor:public Actor{
public:
    nCAWActor(int IID,double x, double y, int dir, double size, unsigned int depth,int speed, bool alive,StudentWorld*s);
    virtual void doDistinctNCAWActivity() = 0;
    virtual void doSomething();
};

class BorderLine: public Actor{
public:
    BorderLine(int IID,double x, double y,StudentWorld*s);
    virtual void doSomething();
};

class Pedestrian : public Agent
{
public:
    Pedestrian(int imageID, double x, double y, double size,StudentWorld* sw);
    virtual void doSomething();
    virtual void doPedActivity() = 0;
   
private:
    void possiblyPickPlan();    // If the pedestrian doesn't go off screen and
                                // should pick a new movement plan, pick a new plan.
};

class ZombiePedestrian : public Pedestrian
{
public:
    ZombiePedestrian(double x, double y, StudentWorld* sw);
    
    void setTicks(int n);
    int getTicks();
    
    virtual bool gotSprayed();
    virtual void doPedActivity();

private:
    void grunt();
    int m_ticks;
    bool m_crossedPaths;
};

class HumanPedestrian : public Pedestrian
{
public:
    HumanPedestrian(double x, double y, StudentWorld* sw);
    virtual bool gotSprayed();
    virtual void doPedActivity();
};

class ZombieCab : public Agent
{
public:
    ZombieCab(double x, double y, int vertSpeed, StudentWorld* s);
    
    virtual void doSomething();
    
    bool didDamageGhost() const;
    void setDidDamage(bool b);
    
    virtual bool gotSprayed();
    
private:
    void checkGhostOverlap();
    bool m_damagedGhost;
    
};

class OilSlick: public nCAWActor
{
public:
    OilSlick(double x, double y,StudentWorld*s);
    virtual void doDistinctNCAWActivity();
};

class SprayableGoodie: public nCAWActor
{
public:
    SprayableGoodie(int IID,double x, double y,int dir, double size,unsigned int depth,bool alive, StudentWorld* s);
    virtual bool gotSprayed();
};

class HealingGoodie: public SprayableGoodie
{
public:
    HealingGoodie(double x, double y,StudentWorld*s);
    
    virtual void doDistinctNCAWActivity();

};

class HolyWaterGoodie: public SprayableGoodie
{
public:
    HolyWaterGoodie(double x, double y,StudentWorld*s);
    
    virtual void doDistinctNCAWActivity();

};

class SoulGoodie: public nCAWActor
{
public:
    SoulGoodie(double x, double y,StudentWorld*s);
    virtual void doDistinctNCAWActivity();
};

class HolyWaterProjectile: public Actor
{
public: HolyWaterProjectile(double x, double y, int dir, StudentWorld*s);
    virtual void doSomething();
    
    int getTravelDistance()const;
    void setTravelDistance(int n);
    
private:
    int m_travelDistance;
    
};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_

