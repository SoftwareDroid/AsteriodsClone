#pragma once

#include "view/iview.h"
/**
 * A view which doesn't do anything. It's needed is some tests
 * @see sdl_view for method comments
 */
class DummyView: public IView {
    void update() {}
   void shutdown() {};
   void eventCreateAsteriod(int uid) {};
   void eventDestroyAsteriod(int uid, bool destroyAnimation) {};
    void eventCreateMissle(int uid) {};
   void eventCreateUfo(int uid) {};
 void eventDestroyMissle(int uid)  {};
  void eventDestroyUfo(int uid,bool destroyAnimation) {};
  void eventDestroySpaceship() {}; 
  void setPushStartMessage() {};
   void setPoints(int points) {};
   void setRemainingLifes(int lifes) {};
   void setBestHighScore(int score) {};
   void destroyStartscreenGUI() {};
   void showGameOverMessage() {};
   void askForPlayerName() {};
};
