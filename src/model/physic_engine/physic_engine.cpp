#include "physic_engine.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <assert.h>

PhysicEngine::PhysicEngine(CollisionListener* listener) : listener(listener)
{
}

void PhysicEngine::addObject(std::shared_ptr<PhysicComponent> obj,int collType, int key)
{
    auto it = objects.find(key);
    assert(it == objects.end());
    objects.insert(std::make_pair(key,CollisionListener::Data{key,obj,collType}));
}


void PhysicEngine::removeObject(int key)
{
    assert(this->objects.find(key) != this->objects.end());
    invalidObjects.insert(key);
}

void PhysicEngine::removeInvalidObjects()
{
    for(auto obj : invalidObjects)
    {
        auto it = this->objects.find(obj);
        if (it != this->objects.end())
        {
            this->objects.erase(obj);
        }
    }
    invalidObjects.clear();
}



void PhysicEngine::tick(float passedTimeInSeconds)
{    
    removeInvalidObjects();
    moveAllObjects(passedTimeInSeconds);
    calculateCollisions();
}

bool PhysicEngine::isObjectInvalid(int key)
{
    auto it = invalidObjects.find(key);
    return it != invalidObjects.end();
}


void PhysicEngine::calculateCollisions()
{
    for(auto& pair : objects)
    {
        for(auto& pair2 : objects)
        {
           const bool objectsRemoved = isObjectInvalid(pair.first) || isObjectInvalid(pair2.first);
           // We don't want self collisons and there are no double collisons
           if (!objectsRemoved && (pair.second.key != pair2.second.key))
           {
               const float r1 = pair.second.collisionObject->getCollisionRadius();
               const float r2 = pair2.second.collisionObject->getCollisionRadius();
               const float sqDistance = (pair.second.collisionObject->getPosition() - pair2.second.collisionObject->getPosition()).getSquaredLen();


               if (sqDistance < (r1 * r1) + (r2 * r2) || (sqDistance < (r1 * r1) || sqDistance < (r2 * r2)))
               {
                   // CollionsDetection
                   CollisionListener::CollisionInfo collision {pair.second,pair2.second};
                   listener->eventCollisionCallback(collision);
               }
           }
        }
    }
}


void PhysicEngine::moveAllObjects(float passedTimeInSeconds)
{
    for(auto& pair : objects)
    {             
        PhysicComponent* component = pair.second.collisionObject.get();
        if (component->isMovementEnabled())
        {
           // Simple linear movement 
           Vector2f newPos = component->getPosition();
           newPos += (component->getHeading() * passedTimeInSeconds * component->getLinearVelocity());
           component->setPosition(newPos);
           // friction
           if (component->isUsingFiction())
           {
               float dragFactor = component->getFriction() * passedTimeInSeconds;
               float v = component->getLinearVelocity();
               v -= v  * dragFactor;
               component->setLinearVelocity(v);
           }
        }
    }
}
