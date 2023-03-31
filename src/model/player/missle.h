#pragma once
#include "share/math/vector2f.h"
#include "model/physic_engine/physic_component.h"
#include "share/timer/timer.h"

/**
 * A missle fired by an ufo or asteriod. 
 * It flies in a straight line til it collides or it's flight limit is reached
 */
class Missle: public PhysicComponent {
public: 
     /**
      * constructs a missle
      * @param startPos the creation position
      * @param trajectory the flight path
      */
    Missle(Vector2f startPos,Vector2f trajectory);
    /**
     * the flight speed
     */
    static constexpr float LINEAR_SPEED_IN_PIXEL_PER_SECOND = 600;
    /**
     * checks if it's flight limit reached
     * @return if true, then the missle should be removed out of the game
     */
     bool travelLimitReached() const;
     /**
      * The collision radius is 1 px
      * @return the collsion radius of the missle
      */
     float getCollisionRadius() const override {return 1;}
private:
    /**
     * timer for measuring the life time of the missle
     */
    Timer aliveTimer ;
};
