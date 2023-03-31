#include "gtest/gtest.h"
#include "model/audio/soundmanager.h"
#include "model/audio/asteriod_sounds.h"
#include <SDL.h>


TEST(Sound, PlaySound) {

SDL_Init(SDL_INIT_AUDIO);
    SoundManager* soundManager = SoundManager::getInstance();
    assert(soundManager ==SoundManager::getInstance() );
     auto saucerSound =  soundManager->createAudio("../../assets/alarm2.wav",SDL_MIX_MAXVOLUME,true);

   soundManager->playSound(saucerSound);
   SDL_Delay(2000);
   soundManager->stopSound(saucerSound);
    SDL_Delay(100);
    SoundManager::getInstance()->shutdown();

}
