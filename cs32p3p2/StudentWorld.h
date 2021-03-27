//Darren Wu CS32 Project 3
//last uploaded 2/27 10:00
#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_


#include "Actor.h"
#include "GameWorld.h"
#include <string>
#include <vector>

using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    GhostRacer* getGhost();
    
    void addHolyWaterProj(double x, double y, int dir,StudentWorld* s);    //functions for actors to add new actors
    void addHealingGoodie(double x, double y, StudentWorld*s);
    void addOil(double x, double y, StudentWorld* s);
    
    void setHumanContact(bool b);
    void addSoulsCollected();
    void setGhostDead(bool b);
    
    bool checkWaterSplash(Actor* a);    //functions where you need to traverse the vector of Actor pointers
    bool checkBehindActors(Actor* a);
    bool checkinFrontActors(Actor* a);

private:
    void setlastWhiteY(int n);
    
    int determineCurrentLane();      //helper functions to add zombiecab
    bool isLaneClearBottom(int lane);
    bool isLaneClearTop(int lane);
    void tryAddZombieCab();
    
    void addZombieCab();
   
    void addHumanPed();
    void addZombiePed();
    bool getHumanContact();
    bool getGhostDead();
    
    void addOil();             //add goodies + slick
    void addHolyWaterGoodie();
    void addLostSoul();
    
    int getSoulsNeeded();    //functions dealing with actual game (levels, souls needed, score)
    int getSoulsCollected();
    int endLevel();
    void resetSouls();
    void setBonusScore(int n);
    int  getBonusScore() const;
    void decBonus();
    
    vector<Actor*> m_actors;
    GhostRacer* m_ghost;
    BorderLine* b;
    
    int m_soulsCollected;
    int m_soulsNeeded;
    bool m_humanContact;
    bool m_isGhostDead;
    int m_bonus;
   
    
};
#endif // STUDENTWORLD_H_

