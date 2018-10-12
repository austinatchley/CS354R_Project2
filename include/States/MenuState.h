#pragma once

#include <OgreInput.h>

#include "State.h"

namespace Game
{
// The game state where you interact with the menu
class MenuState : public State
{
    public:
    MenuState ();
    virtual ~MenuState ()
    {
    }

    void setup () override;

    void update (const Ogre::FrameEvent& evt) override;

    bool keyPressed (const OgreBites::KeyboardEvent& evt) override;
    bool mousePressed (const OgreBites::MouseButtonEvent& evt) override;
    bool mouseMoved (const OgreBites::MouseMotionEvent& evt) override;
};
} // namespace Game
