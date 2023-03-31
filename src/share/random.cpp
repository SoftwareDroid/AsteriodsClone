#include "random.h"
#include <random>


namespace helpers
{
  std::random_device random_rd;
  std::mt19937 random_gen(random_rd());
}

void Random::useFixedSeed()
{
    helpers::random_gen = std::mt19937(0);
}


Random::Random()
{

}

Random::~Random()
{

}

int Random::getRandomInt(int min, int max)
{
  std::uniform_int_distribution<> dis(min, max);
  return dis(helpers::random_gen);
}

float Random::getRandomFloat(float min, float max)
{
  std::uniform_real_distribution<> dis(min, max);
  return dis(helpers::random_gen);
}


bool Random::getRandomBool()
{
  return (bool)Random::getRandomInt(0,1);
}
