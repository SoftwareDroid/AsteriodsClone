#include "gtest/gtest.h"
#include "model/asteriod/asteriod.h"
#include "model/player/spaceship.h"
#include "model/asteriod/asteriod.h"
#include "model/physic_engine/physic_engine.h"
#include "model/physic_engine/collision_listener.h"
#include "model/ufo/ufo.h"
#include "dummy_collision_listener.h"
#include <memory>

#include <vector>

TEST(Model, Asteriod) {
    Asteriod asteriod(Vector2f(0,0),Vector2f(1,0),Asteriod::Type::BIG);
    int pointsBig = asteriod.getPoints();
    auto splittedAsteriods = asteriod.split();
    //Simulate a simple split
    for(Asteriod& a : splittedAsteriods)
    {
      ASSERT_EQ(a.type,Asteriod::Type::MEDIUM); 
      ASSERT_EQ(a.getPosition().x,asteriod.getPosition().x);  
      ASSERT_EQ(a.getPosition().y,asteriod.getPosition().y);  
     ASSERT_GT(a.getPoints(), pointsBig);  

    }

}

TEST(Model, UfoBasics) {
    Ufo ufo(Vector2f(100,100),Ufo::Type::Big);
    // Test firing
    ASSERT_EQ(ufo.canFire(),false);
    ASSERT_GT(ufo.getLinearVelocity(),0);  
    ufo.update();
    Timer t;
    t.start();
    while(t.get_ticks() < 3600){}
    ASSERT_EQ(ufo.canFire(),true);
    
}

TEST(Share, Timer) {
  Timer t;
  t.start();  
  while(t.get_ticks() < 100){}
  ASSERT_GT(t.get_ticks(),99);  

  
}


TEST(Model,PhysicEngineRemoveObjects) {
    DummyPhysicListener collisionListener;
    PhysicEngine physic(&collisionListener);
    Asteriod asteriod1(Vector2f(0,0),Vector2f(0,0),Asteriod::Type::BIG);
    Asteriod asteriod2(Vector2f(0,0),Vector2f(0,0),Asteriod::Type::BIG);
    std::shared_ptr<Asteriod> a1 = std::make_shared<Asteriod>( asteriod1);
    std::shared_ptr<Asteriod> a2 = std::make_shared<Asteriod>( asteriod2);
    physic.addObject(a1,0,1);
    physic.addObject(a2,0,2);
    // After removing one Object there should be no collison
    physic.removeObject(1);
    physic.tick(1.0);
    ASSERT_EQ(collisionListener.collisionCounter,0); 
}

TEST(Model, Missle) {
  Missle missle(Vector2f(0,0),Vector2f(1,0));
  ASSERT_EQ(missle.travelLimitReached(),false);  
 Timer t;
  t.start();  
  while(t.get_ticks() < 3100){}
  ASSERT_EQ(missle.travelLimitReached(),true);  
}

TEST(Model, PhysicEngineBasicAndCollisions) {
    DummyPhysicListener collisionListener;
    PhysicEngine physic(&collisionListener);
    Asteriod asteriod1(Vector2f(200,0),Vector2f(0,0),Asteriod::Type::BIG);
    Asteriod asteriod2(Vector2f(0,0),Vector2f(1,0),Asteriod::Type::BIG);

    std::shared_ptr<Asteriod> a1 = std::make_shared<Asteriod>( asteriod1);
    std::shared_ptr<Asteriod> a2 = std::make_shared<Asteriod>( asteriod2);
    // Check some attributes
    ASSERT_EQ(a2->getHeading().x,1);  
    ASSERT_EQ(a2->getHeading().y,0);  
    ASSERT_EQ(a1->getHeading().x,0);  
    ASSERT_EQ(a1->getHeading().y,0);  
    ASSERT_GT(a2->getLinearVelocity(),0);  
    physic.addObject(a1,0,1);
    physic.addObject(a2,0,2);
    ASSERT_EQ(collisionListener.collisionCounter,0); 
    //Simulate one tick
    physic.tick(1);
    ASSERT_GT(a2->getPosition().x,0);  
    ASSERT_EQ(a2->getPosition().y,0);  
    ASSERT_EQ(a1->getPosition().x,200);  
    ASSERT_EQ(a1->getPosition().y,0);  
    //Simulate a collision

    for(int i = 0; i < 50;i++)
    {
      physic.tick(0.05);  
    }
    ASSERT_GT(a2->getPosition().x,a1->getPosition().y);  
    ASSERT_GT(collisionListener.collisionCounter,0);
    // Stop movement
    a1->setPosition(a2->getPosition());
    a2->setLinearVelocity(0);
    physic.tick(1.0);
    ASSERT_EQ(a1->getPosition().x,a2->getPosition().x);
    ASSERT_EQ(a1->getPosition().y,a2->getPosition().y);  
    
    // Test Friction
    a2->setLinearVelocity(200);
    ASSERT_EQ(a2->getLinearVelocity(),200);  
    a2->activateFriction(true);
    a2->setFriction(0.05);
    physic.tick(1.0);
    ASSERT_LT(a2->getLinearVelocity(),200);  
    for (int i = 0; i  < 500;i++)
    {
        physic.tick(1.0);
    }
    // After many time steps the velocity should be really small
    ASSERT_LT(a2->getLinearVelocity(),1);  
}


TEST(Model,SpaceshipRespawn) 
{
    Spaceship ship;
    // Destroy Ship
    ship.destroyShip(true);
    ASSERT_EQ(ship.isAlive(),false); 
    Timer t;
    t.start();
    while(t.get_ticks() < Spaceship::RESPAWN_TIME_IN_MS + 100
    ){}
    // Wait for respawn
    ship.update(3.6);
     ASSERT_EQ(ship.isAlive(),true); 
}

TEST(Model, SpaceshipBasics) {
    Spaceship ship;
    // Check Alive
    ASSERT_EQ(ship.isAlive(),false);  
    ship.spawn();
    ASSERT_EQ(ship.isAlive(),true);
    ASSERT_EQ(ship.getLinearVelocity(),0);  
    
    // Fire a missle
    auto missle = ship.fire();
    ASSERT_EQ(missle.getHeading().x,ship.getHeading().x);
    ASSERT_EQ(missle.getHeading().y,ship.getHeading().y);
    ASSERT_GT(missle.getLinearVelocity(),0);
    // Spaceship Accelerate
    ASSERT_EQ(ship.isAccelerating(),false);
    ship.accelerate(1.0);
    ASSERT_EQ(ship.isAccelerating(),true);
    ASSERT_GT(ship.getLinearVelocity(),0);
    ASSERT_EQ(ship.getLastFrameAccelrating(),false);
    ship.update(1.0);
    ASSERT_EQ(ship.getLastFrameAccelrating(),true);
    
    // Rotate Ship
   // ship.setRotationSpeed(1.0);
    ASSERT_EQ(ship.getHeading().y,0);
    ASSERT_EQ(ship.getHeading().x,1);
    ship.setRotationSpeed(1.0);
    ASSERT_LT(ship.getHeading().y,0);
    ASSERT_LT(ship.getHeading().x,1);
}

TEST(Model,SpaceshipHyperspace) {
    Spaceship ship;
    ship.spawn();
    ship.useHyperspace();
    ASSERT_EQ(ship.isAlive(),false);  
    Timer t;
    t.start();
    while(t.get_ticks() < Spaceship::TIME_IN_HYPERSPACE_IN_MS + 100){}
    ship.update(1.0);
    ASSERT_EQ(ship.isAlive(),true);  

}
