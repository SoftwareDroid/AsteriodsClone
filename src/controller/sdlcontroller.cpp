#include "sdlcontroller.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <iostream>
#include "../view/iview.h"
#include "../model/game_logic.h"

void SDLController::update(float passedTimeinSeconds)
{
    const bool isPlayerAlive = this->logic->getPlayer() != nullptr;
    //TODO Problem das Key Down event wird nicht in jedem Frame emitiert
    SDL_Event event;
    /* Poll for events. SDL_PollEvent() returns 0 when there are no  */
    /* more events on the event queue, our while loop will exit when */
    /* that occurs.           */
    while( SDL_PollEvent( &event ) ){
        /* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
        
        switch( event.type ){
        case SDL_KEYDOWN:
        { 
            switch( event.key.keysym.sym )
            {
                case (SDLK_5):
                {
                    if(this->logic->getState() == GameLogic::GameState::START_SCREEN_1)
                    {
                        this->view->setPushStartMessage();
                        logic->initGame();
                    }
                    break;
                }
                case(SDLK_1):
                {
                  if(this->logic->getState() == GameLogic::GameState::START_SCREEN_PUSH_START)
                  {
                    this->view->destroyStartscreenGUI();
                    logic->startGame(); 
                  }
                  break;
                }
                case SDLK_LEFT:
                {
                    rotateFactor = 1;
                    break;

                }
                case SDLK_RIGHT:
                {
                    rotateFactor = -1;
                    break;
                }
                 case SDLK_LALT:
                    this->accelerate = true;
                break;
                case SDLK_LCTRL:
                {
                    if(isPlayerAlive)
                    {
                        this->logic->pressFire();
                        break;
                    }
                }
                case SDLK_SPACE:
                {
                    if(isPlayerAlive)
                    {
                        this->logic->pressHyperspace();
                        break;
                    }
                }
            }
            break;
        }
        case SDL_KEYUP:
        { 
            switch( event.key.keysym.sym )
            {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    rotateFactor = 0;
                break;
            case SDLK_LALT:
                    this->accelerate = false;
            break;
            }
            break;
        }
        case(SDL_QUIT):
            this->view->shutdown();
        default:
            break;
        }
    }
    
    if(isPlayerAlive)
    {
        if (rotateFactor != 0) {
            logic->rotatePlayer(passedTimeinSeconds * rotateFactor);
        }
        if(this->accelerate) {
            logic->acceleratePlayer(passedTimeinSeconds);
        } 
    }
    logic->update(passedTimeinSeconds);
}



