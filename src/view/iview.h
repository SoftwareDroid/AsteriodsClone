#pragma once

/**
 * The Interface of the View in the MVC Pattern
 * Most of the methods are events which are called from the backend
 */
class IView {
public:
   virtual ~IView() = default;
   /**
    * An method which should perdioiclly renders the window content
    */
   virtual void update() = 0;
   /**
    * Is called before the detroying of the view
    */
   virtual void shutdown() = 0;
   /**
    * This method is called by the creation for every asteriod 
    * @param uid the identifier of the asteriod
    */
   virtual void eventCreateAsteriod(int uid) = 0;
   /**
    * This method is called before the destroying of an asteriod
    * @param uid the identifier of the asteriod 
    * @param destroyAnimation should a destroy animation be played
    */
   virtual void eventDestroyAsteriod(int uid, bool destroyAnimation) = 0;
   /**
   * This method is called, by the creation of a new missle
   * @param uid The identifier of the object to receive more information
   */
   virtual void eventCreateMissle(int uid) = 0;
  /**
   * This method is called, by the destruction of a missle
   * @param uid The identifier of the object to receive more information
   */
  virtual void eventCreateUfo(int uid) = 0;
  /**
   * This method is called before the destroying of a missle
   * @param uid the identifier of the missle
   */
 virtual void eventDestroyMissle(int uid) = 0;
 /**
  * This method is called before the destroying of an ufo 
  * @param uid the identifier of ufo 
  * @param destroyAnimation should a destroy animation be player 
  */
  virtual void eventDestroyUfo(int uid,bool destroyAnimation) = 0;
  /**
   * This method is called before the destroying of the players spaceship 
   */
  virtual void eventDestroySpaceship() = 0;  //NOTE Always with Animation
  
  /**
   * Event for creating the Push To Start GUI Message
   */
  virtual void setPushStartMessage() = 0;
  /**
   * Set the points in th gui 
   * @param points new the score
   */
  virtual void setPoints(int points) = 0;
  /**
   * Sets the remaining lifes in the gui 
   * @param lifes the new lifes count
   */
  virtual void setRemainingLifes(int lifes) = 0;
  /**
   * Set the best highscore message 
   * @param score the new highscore 
   */
  virtual void setBestHighScore(int score) = 0;
  /**
   * Destroys all gui elements before the real game starts
   */
  virtual void destroyStartscreenGUI() = 0;
  /**
   * Shows the game over gui message
   */
  virtual void showGameOverMessage() = 0;
  /**
   * Ask the player for his name
   */
  virtual void askForPlayerName() = 0;
};
