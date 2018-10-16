#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>

#include "ECS/EventManager.h"

#include "Util/Events/EventSubscribers.h"
#include "Util/Events/Events.h"

namespace Game
{
class SoundManager : public Util::PlaySoundSubscriber, public ECS::EventSubscriber<Util::ToggleSoundEvent>
{
    public:
    SoundManager();
    ~SoundManager()
    {
    }

    virtual void receive(ECS::EventManager* eventManager, const Util::PlaySoundEvent& event) override;
    virtual void receive(ECS::EventManager* eventManager, const Util::ToggleSoundEvent& event) override;

    void playBallHit();
    void playBallLaunch();

    protected:
    Mix_Chunk* wallHit;
    Mix_Chunk* launchBall;
    unsigned flags;
    bool mEnabled;
};
} // namespace Game
