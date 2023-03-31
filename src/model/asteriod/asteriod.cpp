#include "asteriod.h"
#include <assert.h>
#include "share/random.h"
#include <iostream>
#include "share/math/transformation2d.h"

constexpr float Asteriod::SPEED_FACTORS[];

Asteriod::Asteriod(const Vector2f& startPosition, const Vector2f& trajectory, Asteriod::Type type) :  type(type)
{
    this->setHeading(trajectory);
    this->setPosition(startPosition);
    this->setLinearVelocity(SPEED_FACTORS[static_cast<int>(this->type)] * Random::getRandomFloat(0.3,1.3));
}

std::vector<Asteriod> Asteriod::split()
{
    std::vector<Asteriod> children;
    int childType = static_cast<int>(this->type);
    ++childType;
    if (childType <=static_cast<int>(Asteriod::Type::SMALL)) {
        Vector2f heading1 =  Transformation::rotatePoint(Vector2f(1,0),Random::getRandomFloat(0,6.2831));
        Vector2f heading2 =  Transformation::rotatePoint(Vector2f(1,0),Random::getRandomFloat(0,6.2831));
        children.push_back(Asteriod(this->getPosition(),heading1,static_cast<Asteriod::Type>(childType)));
        children.push_back(Asteriod(this->getPosition(),heading2,static_cast<Asteriod::Type>(childType)));
    }
    return children;
}



