#pragma once
#include "share/math/vector2f.h"

/**
 * Inherit from this class to get physic attribute for the physic engine
 */
class PhysicComponent {
public:
    /**
     * costructs an PhysicComponent
     */
    PhysicComponent()
    : position(0,0), heading(0,0),linearVelocity(0),useFriction(false),enabledMovement(true),friction(0)
    {
        
    }
    /**
     * returns the position of the object
     *  @return the position as 2d vector
     */
    const Vector2f& getPosition() const {return position;}
    /**
     * sets the position of the object
     * @param pos the new position
     */
    void setPosition(const Vector2f& pos) {this->position = pos;}
    /**
     * returns the heading of the object
     * @return the heading as  vector
     */
    const Vector2f& getHeading() const {return heading;}
    /**
     * set the heading of the object
     * @param heading the new heading 
     */
    void setHeading(const Vector2f& heading) {this->heading = heading;}
    /**
     * returns the linear velocity of the object as scalar
     * @return a scalar 
     */
    float getLinearVelocity() const {return linearVelocity;}
    /**
     * sets the linear velocity 
     * @param v the new velocity
     */
    void setLinearVelocity(float v) {this->linearVelocity = v;}
    /**
     * is friction is enabled the object will have a negative accelartion
     */
    bool isUsingFiction() const {return useFriction;}
    /**
     * activate friction
     * @param on the friction state
     */
    void activateFriction(bool on) {this->useFriction = on;}
    /**
     * sets the power of the friction 
     * @param value the power of the friction
     */
    void setFriction(float value) {this->friction = value;}
    /**
     * returns the power of the friction
     * @returns the power as float
     */
    float getFriction() const {return friction;}
    virtual ~PhysicComponent() = default;
    /**
     * enable or disable all movements
     * @param on the movement allowing
     */
    void setMovement(bool on) {this->enabledMovement = on;}
    /**
     * returns if movement is enabled
     * @return true if the object is moved hy the physics
     */
    bool isMovementEnabled() const {return enabledMovement;}
    /**
     * override this method to return an collison radius with oter objects
     * @return the collison radius in pixel
     */
    virtual float getCollisionRadius() const = 0;
private:
    /**
     * the position of the obeject
     */
    Vector2f position;
    /**
     * the heading vector (move direction) of the object
     */
    Vector2f heading;
    /**
     * the linear veclocity in px per second
     */
    float linearVelocity;
    /**
     * is the obejct moveable
     */
    bool enabledMovement;
    /**
     * has the object friction by the movement
     */
    bool useFriction;
    /**
     * thr friction power of the object
     */
    float friction;
};
