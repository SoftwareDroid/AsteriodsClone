#pragma once
#include "iview.h"
#include "model/game_logic.h"
#include "objects/asteriod_renderable.h"
#include "objects/ufo_renderable.h"
#include "objects/spaceship_renderable.h"
#include "objects/explosion_renderable.h"
#include "gui/asteriods_hub.h"

class IController;
class SDL_Renderer;
/**
 * A view which is a sdl widnwos and the default sdl renderer
 */

class SDLView : public IView {
public:
      /**
     * The size of the window in px
     */
    static const int WIN_SIZE_X = 1400;
    /**
     * The size of window in px
     */
    static const int WIN_SIZE_Y = 900;
    /**
     * Constructs the View 
     * @param logic a logic which represents the model 
     * @param controller a controller which is responsible for the user input
     */
    SDLView(GameLogic* logic, IController* controller);
    /**
     * Runs the view. This method runs til the window is closed
     */
    void run();
    /**
     * Gets all game obejects and renders them in the window
     */
    void update() override;
    /**
    * Destroys the view. This is finihs the game.
    */
    void shutdown() override;
private:
    /**
     * A counter of new object ids
     */
    int uidCounter = 0;
    /**
     * All grafic asteriod objects
     */
    std::map<int,AsteriodRenderable> asteriods;
    /**
     * All grafic ufo objects
     */
    std::map<int,UfoRenderable> ufos;
    /**
     * All grafic explosions objects
     */
    std::map<int,ExplosionRenderable> explosions;
    /**
     * The gui for managing showed text
     */
    AsteriodsHub gui;   //The GUI in the game
    /**
     * The grafic of the spaceship
     */
    SpaceshipRenderable spaceship;
    /**
     * the sdl renderer
     */
    SDL_Renderer* renderer = nullptr;
    /**
     * a reference to the mvc controller
     */
    IController*  controller;
    /**
     * A reference to the mvc model
     */
    GameLogic* game_logic;
    /**
     * renders all game obejcts and the gui
     */
    void renderAll();
    /**
     * renders a geometry 
     * @param g the geometry which will be rendered
     */
    void renderGeometry(const Geometry& g);
   /**
    * renders all missels
    */
    void renderMissles();
    /**
     * renders all asteriods
     */
    void renderAsteriods();
    /**
     * renders all explosions
     */
    void renderExplosions();
    /**
     * renders all text
     */
    void renderText();
    /**
     * renders all ufos
     */
    void renderUfos();
    bool isRunning;

   void eventCreateAsteriod(int uid) override;
   /**
    * destroy an asteriod 
    * @param uid the asteriod id
    * @param destroyAnimation with destroy animation
    */
   void eventDestroyAsteriod(int uid,bool destroyAnimation) override;
   /**
    * event for creating a missle 
    * @param uid the id of the missle
    */
   void eventCreateMissle(int uid) override;
   /**
    * event for destroying an missle 
    * @param uid the id of the missle
    */
   void eventDestroyMissle(int uid) override;
   /**
    * Event for creating an ufo 
    * @param uid the id of the new ufo 
    */
   void eventCreateUfo(int uid) override;
   /**
    * Event for destroying an ufo 
    * @param uid the ufo id
    * @param destroyAnimation with destroy animation
    */
   void eventDestroyUfo(int uid,bool destroyAnimation) override;  
    /**
     * create the push to start gui message
     */
    void setPushStartMessage() override;
    /**
     * sets the point in the gui 
     * @param points the new points
     */
   void setPoints(int points) override;
   /**
    * sets the new remaining lifes in the gui 
    * @param lifes the new lifes count
    */
   void setRemainingLifes(int lifes) override;
   /**
    * Sets the new best highscore in the gui 
    * @param score the new score
    */
   void setBestHighScore(int score) override;
   /**
    * Destroy all gui elements before the palyer takes control
    */
   void destroyStartscreenGUI() override;
   /**
    * Shows the gui game over message
    */
   void showGameOverMessage() override;
   /**
    * gui for asking the player for his name
    */
   void askForPlayerName() override;
   /**
    * is called before destroying the space ship
    */
   void eventDestroySpaceship() override;
};
