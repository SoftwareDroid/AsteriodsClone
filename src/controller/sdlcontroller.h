#pragma once
#include "icontroller.h"

/**
 * The controller in the mvc pattern as a SDLController
 */
class SDLController : public IController {
public:
  /**
   * Updates the controller. In this method all relevent key board events should
   * be transformed to the model in form of actions
   * @param passedTimeinSeconds The passed time since the last call   
   */
    void update(float passedTimeinSeconds) override;
private:
  /**
   * is the accelerating key is down
   */
    bool accelerate = false;
   /**
   * is the rotate key is down
   */
    int rotateFactor = false;
};
