#pragma once

class IView;
class GameLogic;

/**
 * An interface for the controller
 */
class IController {
public:
   virtual ~IController() = default;
    /**
   * Updates the controller. In this method all relevent key board events should
   * be transformed to the model in form of actions
   * @param passedTimeinSeconds The passed time since the last call   
   */
   virtual void update(float passedTimeinSeconds) = 0;
  /**
   * A reference to the view in  the mvc pattern
   */
   IView* view;
 /**
   * A reference to the model in the mvc pattern
   */
   GameLogic* logic;
};
