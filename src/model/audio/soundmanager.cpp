#include "soundmanager.h"
#include <iostream>
#include <SDL.h>
#include <assert.h>
#include <algorithm>
//NOTE need this Falgs for a working Sound under Windows (OS)
#define SDL_AUDIO_ALLOW_CHANGES SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | SDL_AUDIO_ALLOW_CHANNELS_CHANGE



SoundManager::Audio::Audio(const SoundManager::Audio& obj)
{
    this->allowedToFreeBuffer = false;
    memcpy(this, &obj, sizeof(SoundManager::Audio));
}

void SoundManager::init()
{
    this->privateAudioDevice.audioEnabled= true;
    if(!(SDL_WasInit(SDL_INIT_AUDIO) & SDL_INIT_AUDIO))
    {
      std::cerr<<"Error: SDL_INIT_AUDIO not initialized"<<std::endl; 
      return;
    }
    SDL_memset(&( this->privateAudioDevice.want), 0, sizeof( this->privateAudioDevice.want));
    
    privateAudioDevice.want.freq = 48000;
    privateAudioDevice.want.format = AUDIO_S16LSB;
    privateAudioDevice.want.channels = 2;
    privateAudioDevice.want.samples = 4096;
    privateAudioDevice.want.callback = audioCallback;
    
    privateAudioDevice.want.userdata = this;
    
    privateAudioDevice.device = SDL_OpenAudioDevice(NULL, 0, &(privateAudioDevice.want), NULL, SDL_AUDIO_ALLOW_CHANGES);
    
    
    if(privateAudioDevice.device == 0)
    {
        std::cerr<<"Error: Warning: failed to open audio device"<<std::endl; 
    }
    else
    {
        /* Set audio device enabled global flag */
        privateAudioDevice.audioEnabled = true;

        /* Unpause active audio stream */
        unpauseAudio();
    }
    
}


void SoundManager::shutdown()
{
    // Fix crash if create the logic more than once in tests
    static bool callOnce = false;
    if(callOnce)
    {
      return;  
    }
    callOnce = true;
    
    if(privateAudioDevice.audioEnabled)
    {
    //std::cout<<"Call Shutdown "<<privateAudioDevice.audioEnabled<<" "<<allSounds.size()<<std::endl;

        pauseAudio();
        for(SoundManager::Audio& sound : allSounds)
        {
            // if there are remaining sound free tme memory

            SDL_FreeWAV(sound.bufferTrue);
        }
        /* Close down audio */
        SDL_CloseAudioDevice(privateAudioDevice.device);
    }
}

void SoundManager::pauseAudio()
{
    if(privateAudioDevice.audioEnabled)
    {
        SDL_PauseAudioDevice(privateAudioDevice.device, 1);
    }
}

void SoundManager::unpauseAudio()
{
    if(privateAudioDevice.audioEnabled)
    {
        SDL_PauseAudioDevice(privateAudioDevice.device, 0);
    }
}

void SoundManager::freeSound(const Audio& audio)
{
    this->stopSound(audio);
    int oldSize = allSounds.size();
    std::remove_if(std::begin(allSounds),std::end(allSounds),[audio](SoundManager::Audio& obj){return obj.bufferTrue == audio.bufferTrue;});
    if(oldSize != allSounds.size())
    {
        SDL_FreeWAV(audio.bufferTrue);
    }
    
}

SoundManager::Audio SoundManager::createAudio(const std::string& filename, int volume, bool loop)
{
    Audio audio;
    audio.loop = loop;
    audio.allowedToFreeBuffer = true;
    audio.volume = volume;
    
    if(SDL_LoadWAV(filename.c_str(), &(audio.audio), &(audio.bufferTrue), &(audio.lengthTrue)) == NULL)
    {
        std::cerr<<"Warning: failed to open wave file "<<filename<<" "<<SDL_GetError()<<std::endl; 
        return audio;
    }
    
    audio.buffer = audio.bufferTrue;
    audio.length = audio.lengthTrue;
    (audio.audio).callback = nullptr;
    (audio.audio).userdata = nullptr;
    // Save ound in a list for freeing it later
    //std::cout<<"Create Sound "<<(void*)audio.bufferTrue<<std::endl;
    allSounds.push_back(audio);
    return audio;
}

void SoundManager::playAudio(const std::string& filename,const Audio& sound, bool loop, int volume)
{
   
    if(!this->privateAudioDevice.audioEnabled)
    {
        return;
    }
    const int MAX_SOUNDS = 15;
    if(this->currentPlayingSounds.size() > MAX_SOUNDS)
    {
      return;  
    }
    if(loop)
    {
        auto it = std::find_if (std::begin(currentPlayingSounds), std::end(currentPlayingSounds), [sound](SoundManager::Audio& obj){return obj.bufferTrue == sound.bufferTrue;}); 
        // Jeder looping SOund, kann nur einmal gleichzeitig gespielt werden
        if (it !=std::end(currentPlayingSounds))
        {
          return;  
        }
    }
    
    
    Audio newSound;
    // Load from file
    if(filename.size() > 0)
    {
        newSound = createAudio(filename,volume,sound.loop);
    }
    else
    {
        newSound = Audio(sound);
    }
    
    SDL_LockAudioDevice(privateAudioDevice.device);
    currentPlayingSounds.push_back(std::move(newSound));
    SDL_UnlockAudioDevice(privateAudioDevice.device);
}

void SoundManager::playSound(const  SoundManager::Audio& sound)
{
    //playAudio(const std::string&filename, Audio * audio, bool loop, int volume);
    playAudio("", sound, sound.loop, sound.volume);
}

void SoundManager::stopSound(const SoundManager::Audio& sound)
{
    for(auto it = currentPlayingSounds.begin(); it != currentPlayingSounds.end();++it)
    {
        if((*it).bufferTrue == sound.bufferTrue)
        {
            it->loop  = false;  // Sound will fade out instead of destroyed
        }
    }
}
