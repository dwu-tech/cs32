#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp.

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_soulsCollected = 0;
    m_soulsNeeded = (getLevel()*2)+5;
}

GhostRacer* StudentWorld::getGhost(){
    return m_ghost;
}


int StudentWorld::init()
{
    int n = VIEW_HEIGHT/SPRITE_HEIGHT;
    int m = VIEW_HEIGHT/(4*SPRITE_HEIGHT);
    const int LEFT_EDGE = ROAD_CENTER-(ROAD_WIDTH/2);
    const int RIGHT_EDGE = ROAD_CENTER + (ROAD_WIDTH/2);
    
    for(int i = 0; i<n;i++){
        BorderLine* leftB = new BorderLine(IID_YELLOW_BORDER_LINE,LEFT_EDGE,i*SPRITE_HEIGHT,0,2,2,-4,true,this);
        BorderLine* rightB = new BorderLine(IID_YELLOW_BORDER_LINE,RIGHT_EDGE,i*SPRITE_HEIGHT,0,2,2,-4,true,this);
        m_actors.push_back(leftB);
        m_actors.push_back(rightB);
    }
    
    for(int j = 0;j<m;j++){
        BorderLine* leftB = new BorderLine(IID_WHITE_BORDER_LINE,LEFT_EDGE + ROAD_WIDTH/3,j*(4*SPRITE_HEIGHT),0,2,2,-4,true,this);
        BorderLine* rightB = new BorderLine(IID_WHITE_BORDER_LINE,RIGHT_EDGE - ROAD_WIDTH/3,j*(4*SPRITE_HEIGHT),0,2,2,-4,true,this);
        m_actors.push_back(leftB);
        m_actors.push_back(rightB);
        b = leftB;
    }
    
    m_ghost = new GhostRacer(IID_GHOST_RACER,128.0,32.0,90,4.0,0,0,true,this);
    
    return GWSTATUS_CONTINUE_GAME;
    
}
int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    vector<Actor*>::iterator it;
    
    for(it = m_actors.begin();it != m_actors.end();){
        (*it)->doSomething();
        //cout<<(*it)->getSpeed()<<endl;
        it++;
    }
    int new_border_y = (VIEW_HEIGHT-SPRITE_HEIGHT);
    int delta_y = (new_border_y-b->getY());
    const int LEFT_EDGE = ROAD_CENTER-(ROAD_WIDTH/2);
    const int RIGHT_EDGE = ROAD_CENTER + (ROAD_WIDTH/2);

    if((delta_y)>=SPRITE_HEIGHT){
        BorderLine* leftB = new BorderLine(IID_YELLOW_BORDER_LINE,LEFT_EDGE,new_border_y,0,2,2,-4,true,this);
        BorderLine* rightB = new BorderLine(IID_YELLOW_BORDER_LINE,RIGHT_EDGE,new_border_y,0,2,2,-4,true,this);
        m_actors.push_back(leftB);
        m_actors.push_back(rightB);
    }
    
    
    if(delta_y>=(4*SPRITE_HEIGHT)){
        BorderLine* leftB = new BorderLine(IID_WHITE_BORDER_LINE,LEFT_EDGE + ROAD_WIDTH/3,new_border_y,0,2,2,-4,true,this);
        BorderLine* rightB = new BorderLine(IID_WHITE_BORDER_LINE,RIGHT_EDGE - ROAD_WIDTH/3,new_border_y,0,2,2,-4,true,this);
        m_actors.push_back(leftB);
        m_actors.push_back(rightB);
        b = leftB;
    }
    
    m_ghost->doSomething();
    
    for(it = m_actors.begin();it!=m_actors.end();){
        if(!(*it)->isAlive()){
            delete (*it);
            it = m_actors.erase(it);
        }
        else{
            it++;
        }
    }
    
    
    //cout<<m_ghost->getSpeed()<<endl;
    decLives();
    
    return GWSTATUS_CONTINUE_GAME;
    
}

void StudentWorld::cleanUp()
{
    delete m_ghost;
    vector<Actor*>::iterator it;
    for(it = m_actors.begin();it!=m_actors.end();){
            delete (*it);
            it = m_actors.erase(it);
    }
}
StudentWorld::~StudentWorld(){
    this->cleanUp();
}
