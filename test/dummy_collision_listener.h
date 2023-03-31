#pragma once
#include "model/physic_engine/collision_listener.h"
#include <iostream>
/**
 * A Dummy collsion Listener for couting collsions
 */
class DummyPhysicListener : public CollisionListener{
public:
    /**
     * number of occured collsions
     */
    int collisionCounter = 0;
    /**
     * Gets called by every collsion
     * @param event more data about the collision
     */
    void eventCollisionCallback( CollisionInfo event) 
    {
        collisionCounter++;
    }
};
