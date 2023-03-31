#pragma once
#include "soundmanager.h"
#include <map>

/**
 * This class make it easier to find and load the asteriod sound files for the soundmanager 
 */
class AsteriodSounds {
public:
    /**
     * All sound names in the game
     */
    enum class SoundName : char {EXPLODE,FIRE,LIFE,LSAUCER,SSAUCER,THRUST,HEARTBEAT};
    /**
     * load all sounds from the disk
     */
    static void loadAllSounds()
    {
      static bool needInit = true;
      if(needInit)
      {
        auto i = SoundManager::getInstance();
        asteriodSounds.insert(std::make_pair(SoundName::EXPLODE,i->createAudio("../../assets/EXPLODE1.WAV",SDL_MIX_MAXVOLUME,false)));  
        asteriodSounds.insert(std::make_pair(SoundName::FIRE,i->createAudio("../../assets/FIRE2.WAV",SDL_MIX_MAXVOLUME,false)));
        asteriodSounds.insert(std::make_pair(SoundName::LIFE,i->createAudio("../../assets/LIFE.WAV",SDL_MIX_MAXVOLUME,false)));
        asteriodSounds.insert(std::make_pair(SoundName::SSAUCER,i->createAudio("../../assets/alarm2.wav",SDL_MIX_MAXVOLUME,true)));
        asteriodSounds.insert(std::make_pair(SoundName::LSAUCER,i->createAudio("../../assets/alarm2.wav",SDL_MIX_MAXVOLUME,true)));
        asteriodSounds.insert(std::make_pair(SoundName::THRUST,i->createAudio("../../assets/THRUST2.WAV",SDL_MIX_MAXVOLUME,true)));
        asteriodSounds.insert(std::make_pair(SoundName::HEARTBEAT,i->createAudio("../../assets/tone1.wav",SDL_MIX_MAXVOLUME,true)));
        needInit = false;  
      }
        
    }
    /**
     * all sound files. This map can be used for playing sounds with the soundmanager
     */
    static std::map<SoundName,SoundManager::Audio> asteriodSounds;
    
};
