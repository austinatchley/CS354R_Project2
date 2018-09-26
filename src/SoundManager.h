#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_audio.h>

#include "ECS/EventManager.h"
#include "Events/EventSubscribers.h"

namespace Game
{
    class SoundManager
        : public PlaySoundSubscriber
    {
    public:
        SoundManager();
       ~SoundManager() {}

        virtual void receive(ECS::EventManager* eventManager, const PlaySoundEvent& event) override;

        void playBallHit();

    protected:
        Mix_Chunk* wallHit;
        unsigned flags;
    };
}
