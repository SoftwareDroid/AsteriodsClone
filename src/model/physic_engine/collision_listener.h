#pragma once
#include "physic_component.h"
#include <vector>
#include <memory>
/**
 * Callback interace for collsions
 */
class CollisionListener {
public:
    /**
     * Information about a collieded object
     */
        struct Data {
        /**
         * and object idenifiert
         */
       int key;
       /**
        * the collieded object
        */
       std::shared_ptr<PhysicComponent> collisionObject;
       /**
        * information about the object type
        */
       int objectType;
    };
    
    /**
     * a collision between two objects
     */
    struct CollisionInfo{
        Data d1;
        Data d2;
    };
    virtual ~CollisionListener() = default;
    /**
     * this method is called if two object collide with each other
     * @param event information about the collision
     */
    virtual void eventCollisionCallback( CollisionInfo event) = 0;
private:
};
