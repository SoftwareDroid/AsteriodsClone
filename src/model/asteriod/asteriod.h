#pragma once
#include "share/math/vector2f.h"
#include <vector>
#include "model/physic_engine/physic_component.h"


/**
 * An asteriod in the game with velocity, position, size and so on
 */
class Asteriod: public PhysicComponent {
public:
    /**
     * different speed factors. Smaller Asteriods are faster
     */
    constexpr static float SPEED_FACTORS[] = {135,270,405};
    /**
     * Different size types
     */
    enum class Type {BIG = 0,MEDIUM = 1,SMALL = 2};
    /**
     * Returns the points for destroying the asteriod
     */
       inline int getPoints() const {
         switch(type)
         {
             case(Asteriod::Type::BIG):
             {
               return 20;  
             }
             case(Asteriod::Type::MEDIUM):
             {
               return 50;  
             }
             case(Asteriod::Type::SMALL):
             {
               return 100;  
             }
             
         };
         return 0;
       }
    /**
     * constructs an asteriod
     * @param startPosition the start pos 
     * @param trajectory the trajectory of teh asteriod
     * @param type the size of the asteriod
     */
    Asteriod(const Vector2f& startPosition, const Vector2f& trajectory, Type type);
    /**
     * Splitts the asteriod in two smaller asteriods and returns them
     * @return two smaller asteriods 
     */
    std::vector<Asteriod> split();
    const Type type;
        float getCollisionRadius() const override 
        {
         switch(type)
         {
             case(Asteriod::Type::BIG):
             {
               return 61.61;  
             }
             case(Asteriod::Type::MEDIUM):
             {
               return 30.5;  
             }
             case(Asteriod::Type::SMALL):
             {
               return 15.12;  
             }
         };
         return 0;
        }
};
