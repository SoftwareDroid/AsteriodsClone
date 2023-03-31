#pragma once
#include "share/math/vector2f.h"
#include "share/timer/timer.h"
#include "../player/missle.h"
#include "model/physic_engine/physic_component.h"


class Spaceship;
/**
 * An enemy which fires randomly at the ship and can change it's flight path
 */

class Ufo: public PhysicComponent { 
public:
/**
 * The flight path of the ufo
 */
  enum class TrajectoryType {STRAIGHT = 0,DiagonallyTop = 1,DiagonallyDown = 2, LAST_TRAJECTORY = 3};
/**
 * diagonal length of the ufo bounding box
 */
  constexpr static float DIAGONAL_LEN_OF_BOUNDING_BOX = 65;  //sqrt(56^2 + 33^2)
/**
 * perectages of the window width where the ufo can change it's flight path
 */
  constexpr static float CHANGE_TRAJECTARY_ZONES[] = {0.0,0.33,0.5,0.66,1.0};
/**
 * The speed factor for the different ufo sizes
 */
   constexpr static float SPEED_FACTORS[] = {20,30}; 
/**
 * the scale factors for the different ufo sizes
 */
   constexpr static float SCALE_FACTORS[] = {1.0,0.512f};    
/**
 * the max error angle by firing
 */
   constexpr static float FIRE_PRECISION_ANGLE_IN_DEGREE[] = {30,15};    
/**
 * the different types of the ufo
 */
   enum class Type {Big = 0,Small = 1};
/**
 * returns the points of the ufo
 * @return the points depending of the size
 */
   int getPoints() const { return type == Type::Small ? 1000 : 500;}
/**
 * costructs an ufo
 * @param screenSize the size of the window
 * @param t the size type
 */
  Ufo(const Vector2f& screenSize, Type t);
/**
 * updates the ufo e.g. flight path
 */
   void update();
/**
 * creates a missle which flies toward a spaceship with a error
 * qparam target the target spaceship
 * @return A Missle which have to be added to the physic
 */
   Missle fire(const Spaceship& target);
/**
* Checks if he ufo can fire a missle
* @return a boolean
*/
   inline bool canFire() {return fireTimer.get_ticks() > fireAtTick;}
/**
* The size type of the ufo
*/
    const Type type;
/**
* Returns the collision radius of the ufo
* @returns the size if depending of the ufo size
*/
    float getCollisionRadius() const override {return type == Type::Small?21.96:44;}
 
private:
/**
* A timer for a reload tme
*/
    Timer fireTimer;
/**
* The ufo fires at the passing of this variable (unit is ms)
*/
    int fireAtTick;
/**
* codes the posistion is used for changing the flight path
*/
    int lastZone;
/**
* The current flight path
*/
    TrajectoryType trajectoryType = TrajectoryType::STRAIGHT;
/**
* the size window
*/
    const Vector2f& screenSize;
    /**
    * Changes the flight direction
    * @param x the current x coordinate of the spaceship
    */
    void changeDirection();
    int getZone(int x) {
        
        for(int n = 0; n < 3;n++) {
            int start = CHANGE_TRAJECTARY_ZONES[n] * screenSize.x;
            int end = CHANGE_TRAJECTARY_ZONES[n + 1] * screenSize.x;
            if (x > start && x <= end) {
                return n;
            }
        }
        return 0;
    }
};
