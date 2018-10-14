#pragma once

#include <OgreTrays.h>
#include <OgreOverlaySystem.h>
#include <States/GameState.h>
#include <States/MenuState.h>
#include <States/State.h>

#include <GameObjects/GameObject.h>

using namespace Ogre;
using namespace OgreBites;

namespace Game
{
using StateStack = std::vector<State*>;

class Game : public ApplicationContext, public InputListener, public TrayListener
{
    public:
    Game ();
    virtual ~Game ();

    void pushState (State* state);
    void popState ();

    private:
    void setup ();

    bool keyPressed (const KeyboardEvent& evt) override;
    bool mousePressed (const MouseButtonEvent& evt) override;
    bool mouseMoved (const MouseMotionEvent& evt) override;
    bool mouseReleased (const OgreBites::MouseButtonEvent& evt) override;
    void buttonHit (OgreBites::Button* button) override;

    bool frameRenderingQueued (const Ogre::FrameEvent& evt) override;

    ///////////////////////////////////////////////////////
    // System member vars
    std::unique_ptr<ECS::EventManager> mEventManager;
    SoundManager* mSoundManager;

    StateStack mStates;

    OgreBites::TrayManager* mTrayMgr;
};
} // namespace Game
