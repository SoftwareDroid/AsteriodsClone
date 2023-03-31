#include "missle.h"
#include <iostream>
#include <cmath>

Missle::Missle(Vector2f startPos,Vector2f trajectory) 
{
    this->setPosition(startPos);    
    this->setHeading(trajectory);
    this->setLinearVelocity(LINEAR_SPEED_IN_PIXEL_PER_SECOND);
    aliveTimer.start();
}

bool Missle::travelLimitReached() const
{
    return aliveTimer.get_ticks() > 3000; 
}


