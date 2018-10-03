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

#include "GameObjects/GameObject.h"
#include "Util/Events/EventSubscribers.h"
#include "Util/Events/Events.h"
#include "Util/GameState.h"

#include "../Ball.h"
#include "../SoundManager.h"

#include "Util/GameState.h"

#define NUM_BALLS 10
#define BALL_RADIUS 5.f

#define WALL_SIZE 25.f

#define LIGHT_INTENSITY 1.0
#define AMBIENT_LIGHT                                                          \
    Ogre::ColourValue(LIGHT_INTENSITY, LIGHT_INTENSITY, LIGHT_INTENSITY)

using namespace Ogre;
using namespace OgreBites;

namespace Game {
// The game state where you actually play the game
// This should handle all game-specific logic
class PlayState : public Util::GameState {
  public:
    PlayState(ECS::EventManager *eventManager, Root *root,
              Ogre::RenderWindow *renderWindow);
    virtual ~PlayState() {}

    void update(const Ogre::FrameEvent &evt) override;

    bool keyPressed(const OgreBites::KeyboardEvent &evt) override;
    bool mousePressed(const OgreBites::MouseButtonEvent &evt) override;
    bool mouseMoved(const OgreBites::MouseMotionEvent &evt) override;

  private:
    Root *mRoot;
    SceneManager *mScnMgr;
    RTShader::ShaderGenerator *mShadergen;
    Ogre::RenderWindow *mRenderWindow;

    Ogre::SceneNode *mCamNode;
    Ogre::Viewport *mViewport;

    std::vector<Ball> mBalls;
    std::vector<Ogre::Plane> mWalls;

    ECS::EventManager *mEventManager;
};
}
