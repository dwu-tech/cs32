#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int IID,double x, double y, int dir, double size, unsigned int depth, int speed, bool alive,StudentWorld* s):GraphObject(IID, x, y,dir,size,depth)
{
    m_speed = speed;
    m_alive = alive;
    m_sWorld = s;
}
int Actor::getSpeed(){
    return m_speed;
}
void Actor::setSpeed(int speed){
    m_speed = speed;
}

bool Actor::isAlive(){
    return m_alive;
}

void Actor::setAlive(bool b){
    m_alive = b;
}

StudentWorld* Actor::getWorld(){
    return m_sWorld;
}

GhostRacer::GhostRacer(int IID,double x, double y, int dir, double size, unsigned int depth, int speed, bool alive, StudentWorld* s):Actor(IID, x, y, dir, size, depth,speed,alive,s){
    m_health = 100;
    m_sprays = 10;
}

int GhostRacer::getHealth(){
    return m_health;
}

int GhostRacer::getSprays(){
    return m_sprays;
}

void GhostRacer::setHealth(int h){
    m_health = h;
}

void GhostRacer::setSprays(int s){
    m_sprays = s;
}

void GhostRacer::movementAlgorithm(){
    int max_shift_per_tick = 4.0;
    int direction = getDirection();
    double delta_x = (cos((direction*M_PI)/180))*max_shift_per_tick;
    double cur_x = getX();
    double cur_y = getY();
    //std::cout<<(cos((direction*M_PI)/180))<<" "<<cur_x<<std::endl;
    this->moveTo(delta_x+(cur_x),cur_y);
}
void GhostRacer::doSomething(){
    
    if(!isAlive()){
        return;
    }
    if(getX()<=LEFT_EDGE){
        if(this->getDirection()>90){
            //implement damage
            this->setDirection(82);
            getWorld()->playSound(SOUND_VEHICLE_CRASH);
        }
        
    }
    
    if(getX()>=RIGHT_EDGE){
        if(this->getDirection()<90){
            //implement damage
            this->setDirection(98);
            getWorld()->playSound(SOUND_VEHICLE_CRASH);
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
            default:
                break;
        }
        
    }
    
    movementAlgorithm(); 

}
BorderLine::BorderLine(int IID,double x, double y, int dir, double size, unsigned int depth,int speed, bool alive, StudentWorld* s):Actor(IID, x, y, dir, size, depth,speed,alive,s){
    
}

void BorderLine::doSomething(){
    int vert_speed = (getSpeed())-(getWorld()->getGhost()->getSpeed());
    int horiz_speed = 0;
    int new_x = getX() + horiz_speed;
    int new_y = getY()+vert_speed;
    GraphObject::moveTo(new_x, new_y);
    
    if((getX()<0||getY()<0)||new_x>VIEW_WIDTH || new_y >VIEW_HEIGHT){
        
        setAlive(false);
    }
}


