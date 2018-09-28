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

#include "Events/EventSubscribers.h"
#include "Events/Events.h"
#include "GameObjects/GameObject.h"
#include "Util/GameState.h"

#include "Ball.h"
#include "SoundManager.h"

#define NUM_BALLS 10
#define BALL_RADIUS 5.f

#define WALL_SIZE 25.f

#define LIGHT_INTENSITY 1.0
#define AMBIENT_LIGHT                                                          \
    Ogre::ColourValue(LIGHT_INTENSITY, LIGHT_INTENSITY, LIGHT_INTENSITY)

using namespace Ogre;
using namespace OgreBites;

namespace Game {
using StateStack = std::vector<Util::GameState>;

class Game : public ApplicationContext, public InputListener {
  public:
    Game();
    virtual ~Game();

    void setup();

    bool keyPressed(const KeyboardEvent &evt);

    bool frameRenderingQueued(const Ogre::FrameEvent &evt);

  private:
    ///////////////////////////////////////////////////////
    // System member vars
    Root *mRoot;
    SceneManager *mScnMgr;
    RTShader::ShaderGenerator *mShadergen;

    std::unique_ptr<ECS::EventManager> mEventManager;
    SoundManager *mSoundManager;

    StateStack mGameStates;

    ///////////////////////////////////////////////////////
    // Game-specific member vars
    // MOVE THIS TO PLAYSTATE.H
    Ogre::SceneNode *mCamNode;
    Ogre::Viewport *mViewport;

    std::vector<Ball> mBalls;
    std::vector<Ogre::Plane> mWalls;
};
} // namespace Game
