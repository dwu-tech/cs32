//Darren Wu CS32 Project 3
//last uploaded 2/27 10:00
#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include <sstream>
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

int StudentWorld::getSoulsNeeded(){
    return m_soulsNeeded;
}
int StudentWorld::getSoulsCollected(){
    return m_soulsCollected;
}

int StudentWorld::getBonusScore()const{
    return m_bonus;
}

void StudentWorld::setBonusScore(int n){
    m_bonus = n;
}
void StudentWorld::decBonus(){
    if(m_bonus>0){
        m_bonus--;
    }
}
void StudentWorld::addSoulsCollected(){
    m_soulsCollected+=1;
    m_soulsNeeded -=1;
}

void StudentWorld::resetSouls(){
    m_soulsCollected = 0;
    m_soulsNeeded = (getLevel()*2)+5;
}


bool StudentWorld::getHumanContact(){
    return m_humanContact;
}
void StudentWorld::setHumanContact(bool b){
    m_humanContact = b;
}

bool StudentWorld::getGhostDead(){
    return m_isGhostDead;
}

void StudentWorld::setGhostDead(bool b){
    m_isGhostDead = b;
}
bool StudentWorld::isLaneClearBottom(int lane){
    vector<Actor*>::iterator it;
    vector<int>::iterator intIterator;
    vector<int> v;
    int closestBottom=999;
    
    //bottom of chosen lane (0 == left, 1 for middle, 2 for right);
    for(it=m_actors.begin();it!=m_actors.end();it++){
        if((*it)->determineCurrentLane() == lane && (*it)->isCAWActor()){
            v.push_back((*it)->getY());
        }
    }
    for(intIterator = v.begin();intIterator!=v.end();intIterator++){
        if((*intIterator)<closestBottom){
            closestBottom = (*intIterator);  //saves the closest number to the bottom
        }
    }
    if(closestBottom<=VIEW_HEIGHT/3){
        //cout<<"too damn close"<<endl;
        return false;
    }
    return true;
}

bool StudentWorld::isLaneClearTop(int lane){
    vector<Actor*>::iterator it;
    vector<int>::iterator intIterator;
    vector<int> v;
    int closestTop = 0;
    
    //top of chosen lane (0 == left, 1 for middle, 2 for right);
    for(it=m_actors.begin();it!=m_actors.end();it++){
        if((*it)->determineCurrentLane() == lane && (*it)->isCAWActor()){
            v.push_back((*it)->getY());
        }
    }
    for(intIterator = v.begin();intIterator!=v.end();intIterator++){
        if((*intIterator)>closestTop){
            closestTop = (*intIterator);   //save the closest number to the top
        }
    }
    //cout<<closestTop<<endl;
    if(closestTop>=VIEW_HEIGHT*2/3){
        return false;
    }
    return true;
}

//called by holy water to find first splashable actor
bool StudentWorld::checkWaterSplash(Actor* a){
    
    vector<Actor*>::iterator it;
    for(it = m_actors.begin();it!=m_actors.end();it++){  //go through the actors and see if there is overlap
        if(a->determineOverlap(a, (*it))){
            if((*it)->gotSprayed()){  //gotSprayed is bool to let holy water know to dissolve or not
                a->setAlive(false);
                return true;
            }
        }
    }
    return false;;
}

//called by zombie cab to see actors infront of the cab in current lane
bool StudentWorld::checkinFrontActors(Actor* a){
    
    vector<Actor*>::iterator it;
    int closest = 999;
    
    for(it=m_actors.begin();it!=m_actors.end();it++){
        if(((*it)->determineCurrentLane() == a->determineCurrentLane())&&(*it)->isCAWActor()){
            if(a!=(*it) && ((*it)->getY()>(a->getY()))){
                if(closest > (*it)->getY() - a->getY()){
                    closest = (*it)->getY() - a->getY();   //saves the closest distance between the actor in question and all                                        actors in its lane ahead of it
                }
            }
        }
    }
    //cerr<<"I am traveling faster than ghost: "<<closest<<endl;
    if(closest<96){return true;}
    
    return false;
}

//called by zombie cab to see actors behind of the cab in current lane
bool StudentWorld::checkBehindActors(Actor* a){
    
    vector<Actor*>::iterator it;
    int closest = 999;
    
    for(it = m_actors.begin();it!=m_actors.end();it++){
        if(((*it)->determineCurrentLane() == a->determineCurrentLane())&&(*it)->isCAWActor()){
            if(a!=(*it) && (a->getY()>(*it)->getY())){
                if(closest > a->getY()-(*it)->getY()){
                    closest = a->getY() - (*it)->getY();  //saves the closest distance between the actor in question and all                                        actors in its lane behind it
                }
            }
        }
    }
    //cerr<<"I am traveling slower than ghost: "<<closest<<endl;
    if(closest<96){return true;}
    
    return false;
}


//helper functions to add actors
void StudentWorld::tryAddZombieCab(){
    bool addBottom = false;
    bool addTop = false;
    
    int choseLane = randInt(0,2);
    for(int i = 0;i<2;i++){      //3 iterations only
        if(isLaneClearBottom(choseLane%3)){  //mod three as choselane could start at 2,increment to 4
            addBottom = true;
            break;
        }
        if(isLaneClearTop(choseLane%3)){
            addTop= true;
            break;
        }
        choseLane++;
    }
    if((addBottom == false) && (addTop == false)){  //fails if statement either was set true earlier
        return;
    }
    
    int y_pos = 0;
    (addBottom)?y_pos = (SPRITE_HEIGHT/2):y_pos = VIEW_HEIGHT-(SPRITE_HEIGHT/2); //addBottom is false so addTop is true,set y_pos
    
    //conditional for speed based on adding to top or bottom
    int vert_speed = randInt(2,4);
    (addBottom)?vert_speed += getGhost()->getSpeed():vert_speed = getGhost()->getSpeed() - vert_speed;
    
    int x_pos = 0;
    switch (choseLane%3) {  //set the x for cab based off of the chosen lane
        case 0:
            x_pos = ROAD_CENTER-(ROAD_WIDTH/3);
            break;
        case 1:
            x_pos = ROAD_CENTER;
            break;
        default:
            x_pos = ROAD_CENTER+(ROAD_WIDTH/3);
            break;
    }
    
    if(choseLane%3 == getGhost()->determineCurrentLane() && addBottom){  //don't add where a ghostracer is
        return;
    }
    m_actors.push_back(new ZombieCab(x_pos,y_pos,vert_speed,this));
}

// helpers functions to add actors
void StudentWorld::addZombieCab(){
    int chanceVehicle = max(100-(getLevel()*10),20);
    if(randInt(0,chanceVehicle-1)==0){
        tryAddZombieCab();
    }
}
void StudentWorld::addOil(){
    int chanceOil = max(150-(getLevel()*10),40);
    int x_pos = randInt(LEFT_EDGE, RIGHT_EDGE-1);
    if(randInt(0, chanceOil-1) == 0 ){
        m_actors.push_back(new OilSlick(x_pos,VIEW_HEIGHT,this));
    }
}
void StudentWorld::addOil(double x, double y, StudentWorld*s){
    m_actors.push_back(new OilSlick(x,y,s));
}

void StudentWorld::addHolyWaterGoodie(){
    int chanceHolyWater = 100 + (10*getLevel());
    int x_pos = randInt(LEFT_EDGE, RIGHT_EDGE-1);
    if(randInt(0, chanceHolyWater-1) == 0 ){
        m_actors.push_back(new HolyWaterGoodie(x_pos,VIEW_HEIGHT,this));
    }
}

void StudentWorld::addLostSoul(){
    int chanceLostSoul = 100;
    int x_pos = randInt(LEFT_EDGE, RIGHT_EDGE-1);
    if(randInt(0, chanceLostSoul-1) == 0 ){
        m_actors.push_back(new SoulGoodie(x_pos,VIEW_HEIGHT,this));
    }
}

void StudentWorld::addHumanPed(){
    int chanceHumanPed = max(200-(getLevel()*10),30);
    int x_pos = randInt(LEFT_EDGE, RIGHT_EDGE-1);
    if(randInt(0,chanceHumanPed-1)==0){
        m_actors.push_back(new HumanPedestrian(x_pos,VIEW_HEIGHT,this));
    }
}
void StudentWorld::addZombiePed(){
    int chanceZombiePed= max(100-(getLevel()*10),20);
    int x_pos = randInt(LEFT_EDGE, RIGHT_EDGE-1);
    if(randInt(0,chanceZombiePed-1)==0){
        m_actors.push_back(new ZombiePedestrian(x_pos,VIEW_HEIGHT,this));
    }
}

void StudentWorld::addHolyWaterProj(double x, double y, int dir, StudentWorld *s){
    m_actors.push_back(new HolyWaterProjectile(x,y,dir,s));
}

void StudentWorld::addHealingGoodie(double x, double y,StudentWorld *s){
    m_actors.push_back(new HealingGoodie(x,y,s));
}

//Non helper functions
int StudentWorld::init()
{
    setBonusScore(5000);
    resetSouls();
    setHumanContact(false);
    setGhostDead(false);
    
    int n = VIEW_HEIGHT/SPRITE_HEIGHT;
    int m = VIEW_HEIGHT/(4*SPRITE_HEIGHT);
    const int LEFT_EDGE = ROAD_CENTER-(ROAD_WIDTH/2);
    const int RIGHT_EDGE = ROAD_CENTER + (ROAD_WIDTH/2);
    
    //add border lines
    for(int i = 0; i<n;i++){
        BorderLine* leftB = new BorderLine(IID_YELLOW_BORDER_LINE,LEFT_EDGE,i*SPRITE_HEIGHT,this);
        BorderLine* rightB = new BorderLine(IID_YELLOW_BORDER_LINE,RIGHT_EDGE,i*SPRITE_HEIGHT,this);
        m_actors.push_back(leftB);
        m_actors.push_back(rightB);
    }
    
    for(int j = 0;j<m;j++){
        BorderLine* leftB = new BorderLine(IID_WHITE_BORDER_LINE,LEFT_EDGE + ROAD_WIDTH/3,j*(4*SPRITE_HEIGHT),this);
        BorderLine* rightB = new BorderLine(IID_WHITE_BORDER_LINE,RIGHT_EDGE - ROAD_WIDTH/3,j*(4*SPRITE_HEIGHT),this);
        m_actors.push_back(leftB);
        m_actors.push_back(rightB);
        b = leftB;
    }
    
    m_ghost = new GhostRacer(this);
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    vector<Actor*>::iterator it;
    for(it = m_actors.begin();it!=m_actors.end();){  //remove all dead actors
        if(!(*it)->isAlive()){
            delete (*it);
            it = m_actors.erase(it);
        }
        else{
            it++;
        }
    }
    
    for(it = m_actors.begin();it != m_actors.end();){
        (*it)->doSomething();               //call every actors do Something
        //cout<<(*it)->getSpeed()<<endl;
        it++;
    }
    
    //add new borders every tick
    int new_border_y = (VIEW_HEIGHT-SPRITE_HEIGHT);
    int delta_y = (new_border_y-b->getY());
    const int LEFT_EDGE = ROAD_CENTER-(ROAD_WIDTH/2);
    const int RIGHT_EDGE = ROAD_CENTER + (ROAD_WIDTH/2);

    if((delta_y)>=SPRITE_HEIGHT){
        BorderLine* leftB = new BorderLine(IID_YELLOW_BORDER_LINE,LEFT_EDGE,new_border_y,this);
        BorderLine* rightB = new BorderLine(IID_YELLOW_BORDER_LINE,RIGHT_EDGE,new_border_y,this);
        m_actors.push_back(leftB);
        m_actors.push_back(rightB);
    }
    
    
    if(delta_y>=(4*SPRITE_HEIGHT)){
        BorderLine* leftB = new BorderLine(IID_WHITE_BORDER_LINE,LEFT_EDGE + ROAD_WIDTH/3,new_border_y,this);
        BorderLine* rightB = new BorderLine(IID_WHITE_BORDER_LINE,RIGHT_EDGE - ROAD_WIDTH/3,new_border_y,this);
        m_actors.push_back(leftB);
        m_actors.push_back(rightB);
        b = leftB;
    }
    
    m_ghost->doSomething();
    
    addOil();
    addHolyWaterGoodie();
    addLostSoul();
    addHumanPed();
    addZombiePed();
    addZombieCab();

    
    //cout<<m_ghost->getSpeed()<<endl;
    if(getHumanContact()||getGhostDead()){   //if health <=0 or Ghost Ran over a human
        decLives();
        playSound(SOUND_PLAYER_DIE);
        return GWSTATUS_PLAYER_DIED;
    }
    if(getSoulsNeeded()==0){   //condition for completing a level
        increaseScore(getBonusScore());
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    decBonus();   //decrease bonus points
    
    ostringstream oss;

    oss.fill('0');
    oss << "Score: ";
    oss <<setw(6)<< getScore() << "  ";

    oss << "Level: ";
    oss << getLevel() << "  ";

    oss << "Souls2Save: ";
    oss << getSoulsNeeded() << "  ";
    
    oss << "Lives: ";
    oss << getLives() << "  ";
    
    oss << "Health: ";
    oss << getGhost()->getHealth()<<"  ";
    
    oss << "Sprays: ";
    oss << getGhost()->getSprays()<<"  ";
    
    oss << "Bonus: ";
    oss << getBonusScore()<<"  ";
    
    setGameStatText(oss.str());
    return GWSTATUS_CONTINUE_GAME;
    
}

void StudentWorld::cleanUp()
{
    delete m_ghost;
    m_ghost = nullptr;
    vector<Actor*>::iterator it;
    for(it = m_actors.begin();it!=m_actors.end();){
            delete (*it);
            it = m_actors.erase(it);
    }
}
StudentWorld::~StudentWorld(){
    this->cleanUp();
}
