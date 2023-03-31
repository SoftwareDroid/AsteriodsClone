#pragma once
#include "share/math/vector2f.h"
#include "share/timer/timer.h"
#include "share/math/transformation2d.h"
#include "model/player/missle.h"
#include "model/physic_engine/physic_component.h"

/**
 * A spaceship controlled by the player that can fire and move throught the space 
 */
class Spaceship : public PhysicComponent{
public:
    /**
     * States of teh spaceship
     */
    enum class  State: char {ALIVE // Control State
        ,HYPERSPACE,DEAD,WAIT_FOR_RESPAWN};
    /**
     * constructs a spaceship
     */
    Spaceship();
    /**
     * time which is spacespace needs to respawn
     */
    constexpr static int RESPAWN_TIME_IN_MS = 3500;
    /**
     * duration in which the ship is in hyperspace
     */
    constexpr static int TIME_IN_HYPERSPACE_IN_MS = 2000;
    /**
     * the rotation speed of the ship
     */
    constexpr static float ROTATE_SPEED_IN_DEGREE_PER_SECONDS =  90 * 2.5;
    /**
     * max speed of the spaceship
     */
    constexpr static float MAX_LINEAR_SPEED_PER_SECOND = 541.5;
    /**
     * accelerate ths ship to increase its speed
     * @param passedTime the passed time in seconds 
     */
    void accelerate(float passedTime);
    /**
     * rotates the ship 
     * @param passedTimeInSeconds the passed time
     */
    void setRotationSpeed(float passedTimeInSeconds);
    /**
     * respawn the spaceship
     */
    void spawn();
    /**
     * creates an missle. Which have to be added to the physics 
     *@return a missle before the ship 
     */
    Missle fire();
    /**
     * the ship goes into hyperspace and cannot be hit by anthing during this time
     */
    void useHyperspace();
    /**
     * updates the ship ans states 
     * @param passedTimeInSeconds the passed time in seconds 
     */
    void update(float passedTimeInSeconds);
     /**
      * returns if the the ship is currently accelrating
      * @return accelrating state
      */
    inline bool isAccelerating() {return accelrating;}
    /**
     * Checks if the spaceship is alive 
     * @return true if the ship is under control of the player 
     */
    inline bool isAlive() const {return state == State::ALIVE;}
    /**
     * destroy the ship 
     * @param respawn true then the ship will respawn
     */
    void destroyShip(bool respawn);
    /**
     * inits the ship
     * @param screenSize the size of the window
     */
    void init(Vector2f screenSize);
    /**
     * return the rotation of the ship 
     * @return an angle in degree
     */
    float getRotation() const {return angle;}
    /**
     * returns true if the ship was accelrating in the last frame 
     * @return an boolean
     */
    bool getLastFrameAccelrating() const {return lastFrameAccelerating;}
    /**
     * returns the collison radius of the ship 
     * @return an radius is should be used for collision checks
     */
    float getCollisionRadius() const{return 20.24;}
private:
    /**
     * update the thrust and plays the sounds
     */
    void updateThrust();
    /**
     * the currently rotation
     */
    float angle;
    /**
     * the size of the window
     */
    Vector2f screenSize;
    /**
     * a timer for measruing the time in hyperspace
     */
    Timer hyperspaceTimer;  
    /**
     * the state of the spaceship
     */
    State state;
    /**
     * when alive when the player can controll the spaceship
     */
    bool alive = true;
    /**
     * accelrating state
     */
    bool accelrating = false;
    /**
     * accelerate state of the last frame
     */
    bool lastFrameAccelerating = false;
};
