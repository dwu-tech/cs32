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
    void setlastWhiteY(int n);

private:
    vector<Actor*> m_actors;
    GhostRacer* m_ghost;
    BorderLine* b;
    int m_soulsCollected;
    int m_soulsNeeded;
   
    
};

#endif // STUDENTWORLD_H_

