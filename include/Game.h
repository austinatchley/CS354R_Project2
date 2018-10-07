#pragma once

#include <States/State.h>
#include <States/GameState.h>
#include <States/MenuState.h>

#include <GameObjects/GameObject.h>

using namespace Ogre;
using namespace OgreBites;

namespace Game {
using StateStack = std::vector<State *>;

class Game : public ApplicationContext, public InputListener {
  public:
    Game();
    virtual ~Game();

    void pushState(State *state);
    void popState();

  private:
    void setup();


    bool keyPressed(const KeyboardEvent &evt) override;
    bool mousePressed(const MouseButtonEvent &evt) override;
    bool mouseMoved(const MouseMotionEvent &evt) override;

    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;

    ///////////////////////////////////////////////////////
    // System member vars
    std::unique_ptr<ECS::EventManager> mEventManager;
    SoundManager *mSoundManager;

    StateStack mStates;
};
} // namespace Game
