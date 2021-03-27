//Darren Wu CS32 Project 3
//last uploaded 2/27 10:00
#include "Actor.h"
#include "StudentWorld.h"
#include <vector>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//All Actors
Actor::Actor(int IID,double x, double y, int dir, double size, unsigned int depth, int speed, bool alive,StudentWorld* s):GraphObject(IID, x, y,dir,size,depth)
{
    m_speed = speed;
    m_alive = true;
    m_sWorld = s;
}
double Actor::getSpeed() const{
    return m_speed;
}
void Actor::setSpeed(double speed){
    m_speed = speed;
}

bool Actor::isAlive() const{
    return m_alive;
}

void Actor::setAlive(bool b){
    m_alive = b;
}

bool Actor::isCAWActor() const{
    return m_cawActor;
}

void Actor::setCAWActor(bool b){
    m_cawActor = b;
}
bool Actor::gotSprayed(){
    return false;
}

int Actor::getHSpeed() const{   //agents have non zero horizontal speed
    return m_hSpeed;
}

void Actor::setHSpeed(int n){
    m_hSpeed = n;
}

void Actor::moveActor(){
    int vert_speed = getSpeed()-getWorld()->getGhost()->getSpeed();
    int horiz_speed = getHSpeed();
    int new_x = getX() + horiz_speed;
    int new_y = getY()+vert_speed;
    GraphObject::moveTo(new_x, new_y);
    
    if((getX()<0||getY()<0)||new_x>VIEW_WIDTH || new_y >VIEW_HEIGHT){
        setAlive(false);
    }
}
int Actor::determineCurrentLane() const{               //returns what lane an actor is in0 for left, 2 for                                                          right, 1 for middle, -1 for not in lane
    if(getX()>LEFT_EDGE && getX()<= WHITE_LEFT_EDGE){
        return 0;
    }
    else if(getX()>WHITE_LEFT_EDGE && getX()<= WHITE_RIGHT_EDGE){
        return 1;
    }
    else if(getX()>WHITE_RIGHT_EDGE && getX()<RIGHT_EDGE){
        return 2;
    }
    else{
        return -1;
    }
}


StudentWorld* Actor::getWorld(){  //returns pointer to the current world
    return m_sWorld;
}

//returns whether or not there is overlap between two actors
bool Actor::determineOverlap(Actor* top, Actor* bottom){
    int delta_x = abs(top->getX() - bottom->getX());
    int delta_y = abs(top->getY() - bottom ->getY());
    int sumRadius = top->getRadius()+bottom->getRadius();
    return (delta_x<(sumRadius*0.25)&&(delta_y<(sumRadius * 0.6)));
}

//Agents

Agent::Agent(int IID,double x, double y, int dir, double size, unsigned int depth,int speed, bool alive,StudentWorld*s):Actor(IID, x, y, dir, size, depth,speed,alive,s){
    setCAWActor(true);
}
int Agent::getHealth()const{
    return m_health;
}

void Agent::setHealth(int h){
    m_health = h;
}

void Agent::damageHealth(int n){  //subtract health, set dead if less than zero
    m_health -= n;
    if(m_health<=0){
        setAlive(false);
    }
}

int Agent::getPlan() const{
    return m_plan;
}

void Agent::setPlan(int n){
    m_plan = n;
}

//Ghost Racer
GhostRacer::GhostRacer(StudentWorld* s):Agent(IID_GHOST_RACER, 128.0, 32.0, 90, 4.0, 0,0,0,s){
    setHealth(100);
    m_sprays = 10;
    setCAWActor(true);
}

int GhostRacer::getSprays(){
    return m_sprays;
}

void GhostRacer::addSprays(int s){
    m_sprays+=s;
}

void GhostRacer::movementAlgorithm(){   //movement for ghostRacer to go left and right
    int max_shift_per_tick = 4.0;
    int direction = getDirection();
    double delta_x = (cos((direction*M_PI)/180))*max_shift_per_tick;
    double cur_x = getX();
    double cur_y = getY();
    this->moveTo(delta_x+(cur_x),cur_y);
}

void GhostRacer::slick(){    //if it runs over an oil slick,change direction
    int dir = randInt(5, 20);
    bool coinFlip = (randInt(0,1)==0);   //random chance to determine which way to turn
    if(coinFlip){
        if(dir+getDirection()<120){
            setDirection(dir+getDirection());
        }
        else{
            if(getDirection()-dir >60){
                setDirection(getDirection()-dir);
            }
        }
    }
    else{
        if(getDirection()-dir >60){
            setDirection(getDirection()-dir);
        }
        else{
            if(dir+getDirection()<120){
                setDirection(dir+getDirection());
            }
        }
    }
}

void GhostRacer::heal(int n){   //add health
    setHealth(getHealth() + n);
}

void GhostRacer::doSomething(){
    if(!isAlive()){
        getWorld()->setGhostDead(true);
        return;
    }
    if(getX()<=LEFT_EDGE){          //can't fall off left edge
        if(this->getDirection()>90){
            //implement damage
            this->setDirection(82);
            getWorld()->playSound(SOUND_VEHICLE_CRASH);
            damageHealth(10);
        }
        
    }
    if(getX()>=RIGHT_EDGE){        //can't fall off right edge
        if(this->getDirection()<90){
            //implement damage
            this->setDirection(98);
            getWorld()->playSound(SOUND_VEHICLE_CRASH);
            damageHealth(10);
        }
    }
    int ch;
    if(getWorld()->getKey(ch)){
        switch(ch){
            case KEY_PRESS_LEFT:
                if(this->getDirection()<114){
                    setDirection(this->getDirection()+8);
                }
                break;
            case KEY_PRESS_RIGHT:
                if(this->getDirection()>66){
                    setDirection(this->getDirection()-8);
                }
                break;
            case KEY_PRESS_UP:
                if(getSpeed()<5){
                    setSpeed(getSpeed()+1);
                }
                break;
            case KEY_PRESS_DOWN:
                if(getSpeed()>-1){
                    setSpeed(getSpeed()-1);
                }
                break;
            case KEY_PRESS_SPACE:
                if(getSprays()>0){
                    //tell world to add a water spray
                    getWorld()->addHolyWaterProj(getX(), getY()+SPRITE_HEIGHT, getDirection(), getWorld());
                    addSprays(-1);
                    getWorld()->playSound(SOUND_PLAYER_SPRAY);
                }
            default:
                break;
        }
    }
    movementAlgorithm();
}

//Borderlines
BorderLine::BorderLine(int IID,double x, double y, StudentWorld* s):Actor(IID, x, y, 0, 2, 2,-4,true,s){
    this->setCAWActor(false);
    this->setHSpeed((0));
}

void BorderLine::doSomething(){
    moveActor();
}

//Zombie Cabs
ZombieCab::ZombieCab(double x, double y, int vertSpeed, StudentWorld* s):Agent(IID_ZOMBIE_CAB, x, y, 90, 4, 0,vertSpeed,true,s){
    setHSpeed(0);
    setHealth(3);
    setPlan(0);
}

bool ZombieCab::didDamageGhost()const{  //to remember if ghostracer and cab collided
    return m_damagedGhost;
}
void ZombieCab::setDidDamage(bool b){
    m_damagedGhost = b;
}

bool ZombieCab::gotSprayed(){
    damageHealth(1);
    if(getHealth()<=0){
        setAlive(false);
        getWorld()->playSound(SOUND_VEHICLE_DIE);
        int chanceOil = randInt(1, 5);      //1/5 percent chance of dropping oil
        if(chanceOil == 1){
            getWorld()->addOil(this->getX(),this->getY(),getWorld());
        }
        getWorld()->increaseScore(200);
        return true;
    }
    else{
        getWorld()->playSound(SOUND_VEHICLE_HURT);
    }
    return true;
}

void ZombieCab::checkGhostOverlap(){
    if(determineOverlap(getWorld()->getGhost(), this)){
        if(!didDamageGhost()){
            getWorld()->playSound(SOUND_VEHICLE_CRASH);
            getWorld()->getGhost()->damageHealth(20);
            if(getX()<=getWorld()->getGhost()->getX()){   //move to left
                setHSpeed(-5);
                setDirection(120+(randInt(0,19)));    //changes direction and speed so it can fly away
            }
            else{
                setHSpeed(5);                       //go to right
                setDirection(60-(randInt(0,19)));
            }
            setDidDamage(true);
        }
    }
}

void ZombieCab::doSomething(){
    if(!isAlive()){
        return;
    }
    checkGhostOverlap();
    moveActor();
    if(getSpeed() > getWorld()->getGhost()->getSpeed()){
        if(getWorld()->checkinFrontActors(this)){
            setSpeed(getSpeed()-0.5);
            //cerr<<"too close: slowing down: "<<endl;
            return;
        }
    }
    if(getSpeed() <= getWorld()->getGhost()->getSpeed()){
        if(getWorld()->checkBehindActors(this)){
            setSpeed(getSpeed()+0.5);
            //cerr<<"too close, speeding up:"<<endl;
            return;
        }
    }
    setPlan(getPlan()-1);
    //cout<<"My Plan: "<<getPlan()<<endl;
    if(getPlan()>0){
        return;
    }
    else{
        setPlan(randInt(4,32));
        setSpeed(getSpeed()+randInt(-2,2));
    }
}

//pedestrians
Pedestrian::Pedestrian(int imageID, double x, double y, double size,StudentWorld* sw):Agent(imageID, x, y, 0, size, 0,-4,true,sw){
    setHSpeed(0);
    setPlan(0);
    setHealth(2);
}

void Pedestrian::possiblyPickPlan(){
    setPlan(getPlan()-1);
    if(getPlan()>0){
        return;
    }
    
    int horiz_speed = randInt(-3, 3);
    while(horiz_speed==0){           //can't be zero
        horiz_speed = randInt(-3, 3);
    }
   
    setHSpeed(horiz_speed);
    setPlan(randInt(4,32));
    (getHSpeed()<0)?(setDirection(180)):setDirection(0);
}

void Pedestrian::doSomething(){
    if(isAlive()){
        doPedActivity();
        moveActor();
        possiblyPickPlan();
    }
}

//Zombie Peds
ZombiePedestrian::ZombiePedestrian(double x, double y, StudentWorld* sw):Pedestrian(IID_ZOMBIE_PED, x, y,3,sw){
    setTicks(0);
}

int ZombiePedestrian::getTicks(){  //ticks before next grunt
    return m_ticks;
}

void ZombiePedestrian::setTicks(int n){   //reset the ticks to n ticks
    m_ticks = n;
}
void ZombiePedestrian::grunt(){   //plays the zombie grunt noise, resets the ticks
    setTicks(getTicks()-1);
    if(getTicks()<=0){
        getWorld()->playSound(SOUND_ZOMBIE_ATTACK);
        setTicks(20);
    }
}

bool ZombiePedestrian::gotSprayed(){
    damageHealth(1);
    if(getHealth()<=0){
        setAlive(false);
        getWorld()->playSound(SOUND_PED_DIE);
        if(!determineOverlap(getWorld()->getGhost(), this)){
            int chanceHealGoodie = randInt(1,5);            //zombie dies means 1/5 chance for a healing goodie
            if(chanceHealGoodie == 1){
                getWorld()->addHealingGoodie(this->getX(),this->getY(),getWorld());
            }
            getWorld()->increaseScore(150);
        }
    }
    else{
        getWorld()->playSound(SOUND_PED_HURT);
    }
    return true;
}

void ZombiePedestrian::doPedActivity(){
    if(determineOverlap(this, getWorld()->getGhost())){
        getWorld()->getGhost()->damageHealth(5);   //damages ghost racer health by 5
        this->damageHealth(2);                     //kills zombie
        getWorld()->playSound(SOUND_PED_DIE);
        getWorld()->increaseScore(150);
        return;
    }
    int delta_x = abs(this->getX() - getWorld()->getGhost()->getX());       //if they had the same x in zombies lifetime
    int sumRadius = this->getRadius()+getWorld()->getGhost()->getRadius();
    if(delta_x<sumRadius*0.25){
        m_crossedPaths = true;
    }
    if(m_crossedPaths&&(abs(this->getX()-getWorld()->getGhost()->getX())<30)){  //within 30 and have crossed paths
        setDirection(270);
        if(getWorld()->getGhost()->getX()>this->getX()){
            setHSpeed(1);
        }
        if(getWorld()->getGhost()->getX()<this->getX()){
            setHSpeed(-1);
        }
        grunt();
    }
}

//Human Peds
HumanPedestrian::HumanPedestrian(double x, double y, StudentWorld* sw):Pedestrian(IID_HUMAN_PED, x, y, 2, sw){}

void HumanPedestrian::doPedActivity(){
    if(determineOverlap(this, getWorld()->getGhost())){
        getWorld()->setHumanContact(true);  //set a member variable in student world to true which makes move return player died
        return;
    }
}

bool HumanPedestrian::gotSprayed(){
    setHSpeed(getHSpeed()*-1);
    (getDirection()==0)?setDirection(180):setDirection(0);  //turns human around
    getWorld()->playSound(SOUND_PED_HURT);
    
    return true;
}

nCAWActor::nCAWActor(int IID,double x, double y, int dir, double size, unsigned int depth,int speed, bool alive,StudentWorld*s):Actor(IID, x, y, dir, size, depth,speed,alive,s){
    this->setCAWActor(false);
    this->setHSpeed((0));
}

void nCAWActor::doSomething(){
    moveActor();
    doDistinctNCAWActivity();
}

//Oil Slicks
OilSlick::OilSlick(double x, double y, StudentWorld* s):nCAWActor(IID_OIL_SLICK, x, y, 0, randInt(2, 5), 2,-4,true,s){}

void OilSlick::doDistinctNCAWActivity(){
    if(determineOverlap(getWorld()->getGhost(), this)){
        getWorld()->playSound(SOUND_OIL_SLICK);
        getWorld()->getGhost()->slick();
    }
}

//SprayableGoodies
SprayableGoodie::SprayableGoodie(int IID,double x, double y,int dir, double size,unsigned int depth,bool alive, StudentWorld* s):nCAWActor(IID, x, y, dir, size, depth, -4, true, s){
    
}

bool SprayableGoodie::gotSprayed(){
    setAlive(false);         //remove if sprayed
    return true;
}

//HealingGoodie
HealingGoodie::HealingGoodie(double x, double y,StudentWorld* s):SprayableGoodie(IID_HEAL_GOODIE, x, y, 0, 1, 2,true,s){}

void HealingGoodie::doDistinctNCAWActivity(){
    if(determineOverlap(getWorld()->getGhost(), this)){
        if(!((getWorld()->getGhost()->getHealth()+10)>100)){  //increase health by ten health up to 90
            getWorld()->getGhost()->heal(10);
        }
        else{
            getWorld()->getGhost()->setHealth(100);   //set to 100 so it doesn't go over
        }
        this->setAlive(false);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->increaseScore(250);
    }
}

//HolyWaterGooodie
HolyWaterGoodie::HolyWaterGoodie(double x, double y, StudentWorld* s):SprayableGoodie(IID_HOLY_WATER_GOODIE, x, y, 90, 2, 2,true,s){}


void HolyWaterGoodie::doDistinctNCAWActivity(){
    if(determineOverlap(getWorld()->getGhost(), this)){
        getWorld()->getGhost()->addSprays(10);    //give more sprays to the ghost racer
        this->setAlive(false);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->increaseScore(50);
    }
}

//Soul Goodie
SoulGoodie::SoulGoodie(double x, double y,StudentWorld* s):nCAWActor(IID_SOUL_GOODIE, x, y, 0, 4, 2, -4,true,s){}

void SoulGoodie::doDistinctNCAWActivity(){
    if(determineOverlap(getWorld()->getGhost(), this)){
        getWorld()->addSoulsCollected();    //tell world to increase the amount of souls collected
        this->setAlive(false);
        getWorld()->playSound(SOUND_GOT_SOUL);
        getWorld()->increaseScore(100);
    }
    this->setDirection(getDirection()+10);  //rotate everytick
}

//HolyWaterProjectile
HolyWaterProjectile::HolyWaterProjectile(double x, double y, int dir,StudentWorld*s):Actor(IID_HOLY_WATER_PROJECTILE, x, y, dir, 1.0, 1.0, 0, true, s){
    setTravelDistance(160);
}

int HolyWaterProjectile::getTravelDistance()const{
    return m_travelDistance;
}
void HolyWaterProjectile::setTravelDistance(int n){
    m_travelDistance = n;
}

void HolyWaterProjectile::doSomething(){
    if(isAlive()){
        if(getWorld()->checkWaterSplash(this)){
            return;
        }
        moveForward(SPRITE_HEIGHT);
        if((getX()<0||getY()<0)||getX()>VIEW_WIDTH || getY() >VIEW_HEIGHT){
            setAlive(false);
        }
        setTravelDistance(getTravelDistance()-SPRITE_HEIGHT);
        if(getTravelDistance()<=0){  //traveled more than 160 px
            setAlive(false);
            return;
        }
    }
}
