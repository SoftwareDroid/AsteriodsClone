#pragma once
#include <map>
#include "letter_line.h"
#include "share/timer/timer.h"
#include <iostream>

/**
 * cummulates all showed Text in the game
 */
class AsteriodsHub
{
public:
 /**
 * How many ms of 1000 should a text in visible phase if it is blinking
 */
    static constexpr int PHASE_A_VISIBLE_TEXT = 500;
    /**
     * Keys for the text line positsions
     */
    enum class LineKey  {RemainingLifes, Points, BEST_HIGH_SCORE,DEBUG,GAME_OVER_MESSAGE,
        ONE_COIN_ONE_PLAY,
        PUSH_START,
        ASK_FOR_PLAYER_NAME1,   // 4 Linien
        ASK_FOR_PLAYER_NAME2,
        ASK_FOR_PLAYER_NAME3,
        ASK_FOR_PLAYER_NAME4};
    /**
   *Returns all text lines in a map
    * @return line key to content
   */
    std::map<LineKey,LetterLine> getAllLines() 
    {
      if(this->phaseTimer.get_ticks() >   PHASE_A_VISIBLE_TEXT)
      {
        this->phaseA = (phaseA)?false:true;
        this->phaseTimer.start();
        
      }
      std::map<LineKey,LetterLine> tmp = lines;
      // Remove all blinking Text in phaseA
      if(phaseA)
      {
          tmp.erase(LineKey::PUSH_START);
      }

      return tmp;
    }
   /**
   * set up the hub 
   * @param screenSize the size of the rendering window
   */
    void init(Vector2f screenSize) {this->screenSize = screenSize;phaseTimer.start();}
    /**
   * sets the number of lifes which will be rendered as spaceships
   * @param number the number of lifes
   */
    void setRemainingLifes(int number);
    /**
   * sets the highscore text
   * @param number the highscore
   */
    void setBestHighScore(int number);
    /**
   * sets the  player score text
   * @param number the new score
   */
    void setPoints(int points);
    /**
   * Creates and shows the game over message
   */
    void showGameOverMessage();
    /**
   * Creates and shows the ask for player name message
   */
    void askForPlayerNameMessage();
    /**
   * Creates and shows the insert one coin message
   */
    void setInsertOneCoinMessage();
    /**
   * Destroys all lines which are part of the startscreen
   */
    void destroyStartscreenGUI();
    /**
   * Creates and shows the push to start message, which is part of the start screen
   */
    void setPushStartMessage();
private:
    /**
   * A timer for measuring the blinking phase
   */
    Timer phaseTimer;
    /**
   * The current blinking phase
   */
    bool phaseA;
    /**
   * the size of the rendering window
   */
    Vector2f screenSize = Vector2f(0,0);
    /**
   * all active text lines
   */
    std::map<LineKey,LetterLine> lines;
};
