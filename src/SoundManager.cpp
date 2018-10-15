#include "SoundManager.h"

#include "Util/Util.h"

namespace Game
{
SoundManager::SoundManager()
{
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    Mix_AllocateChannels(24);

    wallHit = Mix_LoadWAV("../media/sound/wallHit.wav");
    launchBall = Mix_LoadWAV("../media/sound/launchBall.wav");
}

void SoundManager::receive(ECS::EventManager* eventManager, const Util::PlaySoundEvent& event)
{
    switch(event.sound)
    {
    case Util::Sound::Ball:
        playBallHit();
        break;
    
    case Util::Sound::Launch:
        playBallLaunch();
        break;

    default:
        break;
    }
}

void SoundManager::playBallHit()
{
    if(!Util::Mix_Playing_Sound(Util::Sound::Ball))
    {
        Util::Mix_PlayChannel_Sound(Util::Sound::Ball, wallHit, 0);
    }
}

void SoundManager::playBallLaunch()
{
    if(!Util::Mix_Playing_Sound(Util::Sound::Launch))
    {
        Util::Mix_PlayChannel_Sound(Util::Sound::Launch, launchBall, 0);
    }
}
} // namespace Game
