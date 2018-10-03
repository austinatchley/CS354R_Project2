#pragma once

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreMath.h>
#include <OgreRTShaderSystem.h>

#include "ECS/Component.h"
#include "ECS/ECSManager.h"
#include "ECS/Entity.h"
#include "ECS/EventManager.h"
#include "ECS/System.h"

#include "Util/Events/EventSubscribers.h"
#include "Util/Events/Events.h"
#include "Util/GameState.h"
#include "GameObjects/GameObject.h"

#include "States/PlayState.h"
#include "States/MenuState.h"

#include "Ball.h"
#include "SoundManager.h"

using namespace Ogre;
using namespace OgreBites;

namespace Game {
using StateStack = std::vector<Util::GameState>;

class Game : public ApplicationContext, public InputListener {
  public:
    Game();
    virtual ~Game();

    void pushState(Util::GameState&& state);
    Util::GameState popState();
    
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

    StateStack mGameStates;
};
} // namespace Game
