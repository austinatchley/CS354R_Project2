#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>

#include "ECS/EventManager.h"
#include "Util/Events/EventSubscribers.h"

namespace Game {
class SoundManager : public Util::PlaySoundSubscriber {
  public:
    SoundManager();
    ~SoundManager() {}

    virtual void receive(ECS::EventManager *eventManager,
                         const Util::PlaySoundEvent &event) override;

    void playBallHit();

  protected:
    Mix_Chunk *wallHit;
    unsigned flags;
};
}
