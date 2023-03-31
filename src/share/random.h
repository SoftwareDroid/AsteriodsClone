#pragma once

/**
 * A class for creating random numbers
 */
class Random
{
private:
  Random();
public:
   /**
   * Sets a fixed seed for creating always the same sequence of random numbers
   */
  static void useFixedSeed();
    /**
   * returns a random number between min and max
   * @param min the minimum random number
   * @param max the maximum random number
   * @return an random integer between min and max
   */
  static int getRandomInt(int min,int max);
      /**
   * returns a random number between min and max
   * @param min the minimum random number
   * @param max the maximum random number
   * @return an random flaot between min and max
   */
  static float getRandomFloat(float min, float max);
  /**
   * Returns an random boolean
   * @return a random boolean value
   */
  static bool getRandomBool();
  ~Random();
};

