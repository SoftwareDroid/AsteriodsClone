#pragma once
#include "player/spaceship.h"
#include "asteriod/asteriod.h"
#include "ufo/ufo.h"
#include "model/audio/soundmanager.h"
#include "share/timer/timer.h"
#include <map>
#include "model/physic_engine/physic_engine.h"
#include "model/physic_engine/collision_listener.h"
#include <memory>


class IView;
/**
 * This class represents the model intferace the in the mvc pattern 
 * for the view adn the controller
 */
class GameLogic: public CollisionListener {
public:
	/**
	 * The number of ms which the death message is showed (wait time) 
	 */
    static constexpr int TIME_SHOW_GAME_OVER_MESSAGE_IN_MS = 3000;
    /**
     * A wait time after the player has died
     */ 
    static constexpr int TIME_WAIT_FOR_DEATH_MESSAGE = 3000;    
    /**
     * The missle limit in the game.
     */
    static constexpr int MAX_NUMBER_OF_MISSLES = 4; 
    /**
     * The states of the game 
     */
    enum class GameState {START_SCREEN_1, START_SCREEN_PUSH_START, INGAME,WAIT_FOR_DEATH_MESSAGE, SHOW_GAME_OVER_MESSAGE,ASK_FOR_PLAYER_NAME,
       WIN_LEVEL
    };
    /**
     * has to be called before startGame. Set ups a game 
     */
    void initGame();
    /**
     *  Starts the game
     */ 
    void startGame();
    /**
     * Sets a view for callbacks
     */ 
    void setView(IView* iview);
    /**
     * Rotates the spaceship
     * @param passedTimeInSeconds the rotation time
     */ 
    void rotatePlayer(float passedTimeinSeconds);
    /**
     * accelerates the spaceship
     * @param passedTimeInSeconds the accelration time
     */ 
    void acceleratePlayer(float passedTimeinSeconds);
    /**
     * The spaceship firesif possible
     */ 
    void pressFire();
   /**
    * THe ship goes into hyperpsace
    */ 
    void pressHyperspace();
    /**
     * updates the model e.g. physic
     */ 
    void update(float passedTimeInSeconds);
    /**
     * returns the spaceship if alive else a nullptr
     * @return spaceship if alive or nullptr
     */ 
    const Spaceship* getPlayer() const 
    {
        if(player->isAlive())
        return player.get();
        else 
            return nullptr;
    }
    /**
     * returns all missles with keys
     * @return key to missles
     */ 
    const std::map<int,std::shared_ptr<Missle>>& getAllMissles() const;
    /**
     * returns all asteriods with keys
     * @return key to asteriod
     */
    const std::map<int,std::shared_ptr<Asteriod>>& getAllAsteriods() const;
    /**
     * returns all ufos with keys
     * @return key to ufo
     */ 
    const std::map<int,std::shared_ptr<Ufo>>& getAllUfos() const;
    /**
     * constructs the model
     */ 
    GameLogic();
    /**
     * destructs the model
     */ 
    ~GameLogic();
    /**
     * inits the model with the window size
     * @param the window size
     */ 
    void init(const Vector2f& windowSize);
    /**
     * returns the current game state
     * @return the current game state
     */ 
    GameState getState() const {return state;}
    /**
     * returns the score of the player
     * @return the current score
     */ 
    int getScore() const {return score;}
    /**
     * returns the remaining lifes of the player
     * @return the remaining lifes
     */ 
    int getRemainigLifes() const {return remainingLives;}
    /**
     * returns the best highscore
     * @return the best highscore
     */ 
    int getBestHighScore() const {return bestHighScore;}
private:
	/**
	 * Codes the type of collision objects
	 */ 
    enum class CollisonType {Missle = 1, Asteriod = 0, Ufo =2, Ship = 3};
    /**
     * The physic Engine controlls the movment and collisions of the game objects
     */ 
    PhysicEngine physicEngine;
    /**
     * the current state of the game
     */ 
    GameState state;
    /**
     * time transition between states
     */ 
    Timer timerBetweenStates;
    /**
     * changes the game state
     * @param s the new state
     */ 
    void changeState(GameState s);
    /**
     * a counter for counting objects uids
     */ 
    int uidCounter = 0;
    /**
     * the size of the windoow which si equal to the field size
     */ 
    Vector2f windowSize = Vector2f(0,0);
    /**
     * reference to the view for rendering callbacks
     */ 
    IView* iview;
    /**
     * the spaceship of the player
     */ 
    std::shared_ptr<Spaceship> player = std::make_shared<Spaceship>();
    /**
     * the current score
     */ 
    int score = 0;
    /**
     * the best score
     */ 
    int bestHighScore = 0;  
    /**
     * the remainig lifes of the player
     */ 
    int remainingLives = 3;
    /**
     * id's to missels
     */ 
    std::map<int,std::shared_ptr<Missle>> misseles;
    /**
     * id's to asteriods
     */ 
    std::map<int, std::shared_ptr<Asteriod>> asteriods;
    /**
     * id's to ufos
     */ 
    std::map<int,std::shared_ptr<Ufo>> ufos;
    /**
     * an counter which determines when the next ufo spawns
     */ 
    int spawnNextUfo = -1;
    /**
     * a timer which determines, when the nexr ufo spaws
     */ 
    Timer ufoSpawnTimer;
    /**
     * applies cyclic field wrapping to an object
     * @paran comp the object
     */ 
    void applyScreenWrapping(PhysicComponent* comp);
    /**
     * creates the start screen logic e.g. some asteriods
     */ 
    void startScreenLogic();
    /**
     * execute the ufo ki and logic e.g. spawning
     */ 
    void ufoLogic();    
    /**
     * updates the game state
     */ 
    void updateState();
    /**
     * updates all ufos
     */ 
    void updateUfos();
    /**
     * updates the spaceship
     * @param passedTimeInSeconds the passed time since the last call
     */ 
    void updatePlayer(float passedTimeInSeconds);
    /**
     * updates all missels
     * @param passedTimeInSeconds the passed Time since the last call
     */ 
    void updateMissles(float passedTimeInSeconds);
    /**
     * updates all asteriods
     */ 
    void updateAsteriods();
    /**
     * collison event between an asteriod and some other object
     * @param asteriod the asteriod
     * @param other the other object
     * @param type the type of the other object
     */ 
    void eventAsteriodCollison(std::shared_ptr<PhysicComponent> asteriod, std::shared_ptr<PhysicComponent> other, CollisonType type);
    /**
     * An collison event with an asteriod
     * @param event more infos about the collsion
     */ 
    void handleAsteriodCollisions(const CollisionListener::CollisionInfo& event);
    /**
     * an collsion event with an missle
     * @param event more infos about the event
     */ 
    void handleMissleCollisions(const CollisionListener::CollisionInfo& event);
    /**
     * an spaceship collsion event
     */ 
    void eventPlayerCollsion();
    /**
     * an collsion event callback
     * @param event more infos about the collision
     */ 
    void eventCollisionCallback(CollisionListener::CollisionInfo event) override;
    /**
     * starts the first level
     */ 
    void startLevel1();
    /**
     * event the player has lost all his lifes
     */ 
    void eventGameOver();
    /**
     * adds an ufo to the game
     * @param u the new ufo
     */ 
    void addUfo(Ufo& u);
    /**
     * adds an missle to the game
     * @param m the new missle
     */ 
    void addMissle(Missle& m);
    /**
     * adds an asteriod to the game
     * @param a new asteriod
     */ 
    void addAsteriod(Asteriod& a);
    /**
     * adds a spaceship to the game
     * @param s the new spaceship
     */ 
    void addSpaceship(Spaceship& s);
    /**
     * removes an ufo from the game
     * @param uid the key of the object
     * @param animation plays an destroy animation
     */ 
    void removeUfo(int uid,bool animation);
    /**
     * removes an missle from the game
     * @param uid the key of the ufo
     */ 
    void removeMissle(int uid);
       /**
     * removes an asteriod from the game
     * @param uid the key of the object
     * @param animation plays an destroy animation
     */ 
    void removeAsteriod(int uid,bool animation);
    /**
     * removes all asteriods from the game
     * @param animation play an destroy animation
     */ 
    void clearAsteriods(bool animation);
     /**
     * removes ufos asteriods from the game
     * @param animation play an destroy animation
     */ 
    void clearUfos(bool animation);
    /**
     * removes an ufo from the game
     * @param ingame are we currenty in a game
     * @param key the key (uid) of the object
     */ 
    void destroyUfo(bool ingame,int key);
    /**
     * removes an missle from the game
     * @param key the uid of the missle
     */ 
    void destroyMissle(int key);
};
