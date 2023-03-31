#include "spaceship.h"
#include <assert.h>
#include "share/math/helper.h"
#include "share/math/transformation2d.h"
#include "../audio/soundmanager.h"
#include "../audio/asteriod_sounds.h"
#include "share/random.h"
#include <iostream>
#include <vector>

Spaceship::Spaceship(): screenSize(0,0)
{
    state  = State::DEAD;
    this->setHeading(Vector2f(1,0));
    this->setFriction(0.2);
    this->activateFriction(true);
    this->setLinearVelocity(0);
}

void Spaceship::init(Vector2f screenSize)
{
    this->screenSize = screenSize;
}


void Spaceship::useHyperspace()
{

    assert(this->state == State::ALIVE);
    float newX = Random::getRandomFloat(0,screenSize.x);
    float newY = Random::getRandomFloat(0,screenSize.y);
    this->setPosition(Vector2f(newX,newY));
    this->state = State::HYPERSPACE;
    hyperspaceTimer.start();
}


void Spaceship::destroyShip(bool respawn)
{
   SoundManager::getInstance()->stopSound(AsteriodSounds::asteriodSounds[AsteriodSounds::SoundName::HEARTBEAT]);
    SoundManager::getInstance()->stopSound(AsteriodSounds::asteriodSounds[AsteriodSounds::SoundName::THRUST]);
    state = (respawn) ? State::WAIT_FOR_RESPAWN : State::DEAD;
    SoundManager::getInstance()->playSound(AsteriodSounds::asteriodSounds[AsteriodSounds::SoundName::EXPLODE]);
    // Dying is lke hyperspace
    hyperspaceTimer.start();
}

void Spaceship::spawn()
{
   this->angle = 0;
   SoundManager::getInstance()->playSound(AsteriodSounds::asteriodSounds[AsteriodSounds::SoundName::HEARTBEAT]);
   this->state = State::ALIVE;  
   this->setPosition(Vector2f(screenSize.x / 2.0,screenSize.y / 2.0));
   this->setLinearVelocity(0);
   this->setHeading(Vector2f(1,0));
}

void Spaceship::accelerate(float passedTime)
{
    float accFactor = 300;
    // Create a normalized vector in the direction of travel
    const Vector2f &n =  this->getHeading();
    this->setLinearVelocity( this->getLinearVelocity()  +  accFactor * passedTime);
   
    //v += Vector2f(n.x * accFactor, n.y * accFactor) * passedTime;
    // Upper speed Limit
    if(this->getLinearVelocity() >  MAX_LINEAR_SPEED_PER_SECOND) {
        this->setLinearVelocity(MAX_LINEAR_SPEED_PER_SECOND);
    }
    accelrating = true;
}

Missle Spaceship::fire()
{
    //const Vector2f& input ,const Vector2f& translate, float rotateAngle, float scaleX, float scaleY
    const int offsetBeforeShip = 20;
    const Vector2f startPos = this->getPosition() + this->getHeading() * offsetBeforeShip;
    return Missle(startPos ,this->getHeading());
}


void Spaceship::update(float passedTimeInSeconds)
{
    this->setMovement(state == State::ALIVE);
    switch(state)
    {
        case(State::ALIVE):
        {
            break;
        }
        case (State::DEAD):
        {
            break;
        }
        case (State::WAIT_FOR_RESPAWN):
        {

          //Game Over  
          if(hyperspaceTimer.get_ticks() > RESPAWN_TIME_IN_MS)
          {
              spawn();

              
          }  
          break;  
        }
        case(State::HYPERSPACE):
        {
            // Come back of hyperspace
            if(hyperspaceTimer.get_ticks() >TIME_IN_HYPERSPACE_IN_MS)
            {
              this->state = State::ALIVE;  
            }
            break;
        }
    }
    updateThrust();
}

void Spaceship::updateThrust()
{
    
    
    // NOTE Key events come before the update event
    if(accelrating != lastFrameAccelerating)
    {
        if(accelrating)
        {
            SoundManager::getInstance()->playSound(AsteriodSounds::asteriodSounds[AsteriodSounds::SoundName::THRUST]);
        }
        else 
        {
             SoundManager::getInstance()->stopSound(AsteriodSounds::asteriodSounds[AsteriodSounds::SoundName::THRUST]);
        }
    }
    lastFrameAccelerating = accelrating;
    accelrating = false;
}


void Spaceship::setRotationSpeed(float passedTimeInSeconds)
{
    assert(passedTimeInSeconds != 0);
    float newRotation = angle + degToRad(ROTATE_SPEED_IN_DEGREE_PER_SECONDS * passedTimeInSeconds );
    this->angle = newRotation;
    this->setHeading(Transformation::rotatePoint(Vector2f(1,0),angle));
}




