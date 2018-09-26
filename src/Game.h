#pragma once

#include <Ogre.h>
#include <OgreMath.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <OgreApplicationContext.h>

#include "ECS/EventManager.h"
#include "ECS/EntityManager.h"
#include "ECS/ComponentManager.h"
#include "GameObjects/GameObject.h"
#include "Events/Events.h"
#include "Events/EventSubscribers.h"

#include "SoundManager.h"
#include "Ball.h"

#define NUM_BALLS 10
#define BALL_RADIUS 5.f

#define WALL_SIZE 25.f

#define LIGHT_INTENSITY 1.0
#define AMBIENT_LIGHT Ogre::ColourValue(LIGHT_INTENSITY, LIGHT_INTENSITY, LIGHT_INTENSITY)

using namespace Ogre;
using namespace OgreBites;

namespace Game
{
    class Game
            : public ApplicationContext
            , public InputListener
    {
    public:
        Game();
        virtual ~Game();

        void setup();

        bool keyPressed(const KeyboardEvent& evt);

        bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    private:
        ///////////////////////////////////////////////////////
        // System member vars
        Root* mRoot;
        SceneManager* mScnMgr;
        RTShader::ShaderGenerator* mShadergen;

        std::unique_ptr<ECS::EventManager> mEventManager;
        SoundManager* mSoundManager;

        ///////////////////////////////////////////////////////
        // Game-specific member vars
        Ogre::SceneNode* mCamNode;
        Ogre::Viewport* mViewport;

        std::vector<Ball> mBalls;
        std::vector<Ogre::Plane> mWalls;
    };
} //namespace Game
