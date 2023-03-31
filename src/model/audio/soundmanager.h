#pragma once
#include <string>
#include <SDL_audio.h>

#include <list>

/**
 * This class can play sdl sounds
 * command for creating valid playable sounds ffmpeg -i in.mp3 -acodec pcm_s16le -ac 2 -ar 48000 out.wav
 */
class SoundManager {
public:
    /**
     * Singleton pattern to get an instance to this class
     */
    static SoundManager* getInstance()
        {
            static SoundManager    instance; // Guaranteed to be destroyed.
            return &instance; // Instantiated on first use.
        }
    /**
     * A loaded sound
     */
    struct Audio 
    {
        /**
         * The remaining length 
         */
        uint32_t length;
        /**
         * The full length
         */
        uint32_t lengthTrue;
        /**
         * The full buffer
         */
        uint8_t * bufferTrue;
        /**
         * the remaining buffer
         */
        uint8_t * buffer;
        /**
         * should the sound be played in loop mode
         */
        bool loop;
        /**
         * is the dound allowed to be freed
         */
        bool allowedToFreeBuffer;
        /**
         * the sound volume
         */
        uint8_t volume;
        /**
         * constructs an empty audio
         */
        Audio(){}
        /**
         * copy constructs an audio
         */
        Audio(const Audio& obj);    //Create a copy
        /**
         * meta data about the sound
         */
        SDL_AudioSpec audio;
    };
    SoundManager(SoundManager const&) = delete;              // Don't Implement
    void operator=(SoundManager const&) = delete; // Don't implement
    /**
     * stops an playing sound with a the same buffer
     * @param sound the sound which should be stopped
     */
    void stopSound(const Audio& sound);
    /**
     * creates a sound directyl from a file name
     * @param filename the path to the file
     * @param volume the sound volume
     * @param loop loop mode
     */
    Audio createAudio(const std::string& filename,int volume, bool loop);
    /**
     * start playing a sound
     * @param sound the sound which should be played
     */
    void playSound(const Audio& sound);
    /**
     * free a sound file. All not freed sound files are freed in the shutdown method
     * @param audio the sound which should be freed
     */
    void freeSound(const Audio& audio);
    /**
     * frees all sounds and memory
     */
    void shutdown();
    /**
     * pause all audio
     */
    void pauseAudio();
    /**
     * unpauses all audio
     */
    void unpauseAudio();

private:
    /**
     * callback from sdl for playing sounds
     * @param userdata the sound here
     * @param stream all sound currently played
     * @param len the remaining lenghth
     */
    static inline void audioCallback(void * userdata, uint8_t * stream, int len)
    {
            SoundManager* self = static_cast<SoundManager*>(userdata);

    /* Silence the main buffer */
    SDL_memset(stream, 0, len);
    for(auto it = self->currentPlayingSounds.begin(); it != self->currentPlayingSounds.end();)
    {
        Audio& audio = (*it);
        if(audio.length > 0) 
        {
            int tempLength = 0;
            {
                tempLength  = (len > audio.length) ? audio.length :  len;
            }
            SDL_MixAudioFormat(stream, audio.buffer, AUDIO_S16LSB, tempLength, audio.volume);
            audio.buffer += tempLength;
            audio.length -= tempLength;
            ++it;   // Next Element
        }
        // Restart Looping sounds
        else if(audio.loop)
        {
            audio.buffer = audio.bufferTrue;
            audio.length = audio.lengthTrue;
        }
        else
        {
            // Sound is finished remove it
            it = self->currentPlayingSounds.erase(it);
        }
    }
    }
    /**
     * constructs a soundmanager
     */
    SoundManager() {init();} 
    /**
     * A audiodevice for playing sounds
     */
    struct PrivateAudioDevice
    {
        /**
         * id of the device
         */
        SDL_AudioDeviceID device;
        /**
         * specification of the device 
         */
        SDL_AudioSpec want;
        /**
         * is sound enabled
         */
        bool audioEnabled;
    };
    /**
     * all loaded sounds 
     */
    std::list<Audio> allSounds;
    /**
     * all currently played sounds
     */
    std::list<Audio> currentPlayingSounds; 
    /**
     * an audio device for playing sounds
     */
    PrivateAudioDevice privateAudioDevice;
    /**
     * inits this class
     */
    void init();
    /**
     * frees the memory of an audio file
     */
    void freeAudio(Audio* audio);
    /**
     * play an audio 
     * @param filename the filepath is no longer used
     * @param sound the sound 
     * @param volume the sound volume
     */
    void playAudio(const std::string&filename,const Audio& sound, bool loop, int volume);
};
