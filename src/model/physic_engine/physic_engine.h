#pragma once
#include "physic_component.h"
#include <map>
#include <set>
#include "collision_listener.h"
#include <memory>

/**
 * this class moves all objects and callback all collions with added objects to decouble this from the rest of the system
 */
class PhysicEngine {
public:
    /**
     * creates an physic engine 
     * @param listener a class which should be notified aboud collions events
     */
    PhysicEngine(CollisionListener* listener);
    /**
     * simulates one tick in which first all objects are moved then collisons are calculated
     * @param passedTimeInSeconds the passed time in seconds
     */
    void tick(float passedTimeInSeconds);   //Wichtig ist removeObject aufzurufen
    /**
     * registers an object with the physic engine
     * @param obj the object
     * @param collType an integer for saving the type of the object. This integer will only forwared
     * @param key an key for removing the object from the physic engine later
     */
    void addObject(std::shared_ptr<PhysicComponent> obj,int collType, int key);
    /**
     * remove an object form the physic engine
     * @param key the identifier of the object set in addObject
     */
    void removeObject(int key);
private:
    /**
     * A collison callback class
     */
    CollisionListener* listener;
    /**
     * all added objects 
     */
    std::map<int,CollisionListener::Data> objects;
    /**
     * objects that are currently no longer valid
     */
    std::set<int> invalidObjects;
    /**
     * removes all invalid objects from the engine
     */
    void removeInvalidObjects();
    /**
     * moves all valid objects
     * @param passedTimeInSeconds the passed time
     */
    void moveAllObjects(float passedTimeInSeconds);
    /**
     * calculate all collisons and forwards them to the listener
     */
    void calculateCollisions();
    /**
     * checks if an object is still valid 
     * @param key the key of the checked object
     */
    bool isObjectInvalid(int key);
};
