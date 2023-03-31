#include "ufo.h"
#include "share/random.h"
#include <iostream>
#include <model/player/spaceship.h>
#include <cmath>
#include "share/math/transformation2d.h"
#include "share/math/helper.h"
#include <assert.h>


constexpr float Ufo::SPEED_FACTORS[];

constexpr float Ufo::DIAGONAL_LEN_OF_BOUNDING_BOX;
constexpr float Ufo::SCALE_FACTORS[];
constexpr float Ufo::CHANGE_TRAJECTARY_ZONES[];
constexpr float Ufo::FIRE_PRECISION_ANGLE_IN_DEGREE[];

Ufo::Ufo(const Vector2f& screenSize,Type t): 
type(t),
screenSize(screenSize)
{
    this->setLinearVelocity(SPEED_FACTORS[static_cast<int>(this->type)]);
    this->setHeading(Vector2f(SPEED_FACTORS[static_cast<int>(t)],0));
    this->setPosition(Vector2f(0.0,Random::getRandomFloat(0,screenSize.y)));
    // Set random spawn position
    lastZone =  getZone(this->getPosition().x);
    fireTimer.start();
    fireAtTick = 0;

}








void Ufo::update()
{
    changeDirection();
}

void Ufo::changeDirection()
{
    Vector2f pos = this->getPosition();
    Vector2f heading = this->getHeading();
    int z1 = getZone(pos.x);
    if( z1 != lastZone) {
        // Screen Wrapping is no Zone change
        if(std::abs(z1 - lastZone) == 1)
        {
         
            Ufo::TrajectoryType action = Ufo::TrajectoryType::LAST_TRAJECTORY;
            const float PROBABLITY_STRAIGHT = 0.6;
            if (Random::getRandomFloat(0,1) < PROBABLITY_STRAIGHT) {
                action = Ufo::TrajectoryType::STRAIGHT;
            } 
            else 
            {
                action = Random::getRandomFloat(0,1) > 0.5 ? Ufo::TrajectoryType::DiagonallyDown :  Ufo::TrajectoryType::DiagonallyTop;
            }
            
            switch(action) {
                case(Ufo::TrajectoryType::STRAIGHT) :
                    heading.y = 0;
                    break;
                case(Ufo::TrajectoryType::DiagonallyDown) :
                    heading.y = -heading.x;
                    break;
                case(Ufo::TrajectoryType::DiagonallyTop) :
                    heading.y = heading.x;
                    break;
                case(Ufo::TrajectoryType::LAST_TRAJECTORY) :
                    break;
            };
            this->trajectoryType = action;
            this->setHeading(heading);
            
            //std::cout<<action<<std::endl;
            // NOTE irgendein Zualls verhalten
            //Falls Gerade 60% Flugbahn beibehlaten, 20% oben, 20% unten
            // Falls Schräg 60% wiede rzu gerade 20% Schräge beibehalten, 20% schräge ändern
            //std::cout<<"Überschreite Zone => Zufallszahl => Flugbahnänderung Schräng Oben, Unten oder gerade weiter"<<std::endl;
        }
        lastZone = z1;
    }
}

Missle Ufo::fire(const Spaceship& target)
{
  assert(canFire());  
  Vector2f targetPos =  target.getPosition();
  Vector2f fireStartPos = this->getPosition();
  Vector2f trajectory = (targetPos - fireStartPos);
  trajectory /= std::sqrt(trajectory.getSquaredLen());
  const float maxAngle = degToRad(Ufo::FIRE_PRECISION_ANGLE_IN_DEGREE[static_cast<int>(type)]);
  const float randomFireAngle = Random::getRandomFloat(- maxAngle / 2.0, maxAngle / 2.0);
  trajectory = Transformation::rotatePoint(trajectory,randomFireAngle);
  // Place the missle on a circle arround the ufo, so that it won't collide with the ufo.
  float offset =   DIAGONAL_LEN_OF_BOUNDING_BOX / 2.0 * SCALE_FACTORS[static_cast<int>(type)] + 5;
  Missle m(fireStartPos + trajectory * offset,trajectory);
  fireAtTick += 2000;   //Fire every 2s
  return m;
}


