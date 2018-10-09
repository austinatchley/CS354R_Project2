#pragma once

#include <cstdint>

#include <OgreInput.h>
#include <OgreTrays.h>

namespace Game {
enum class ScreenShare : std::size_t { Transparent = 0, Shared, Full };

class State {
  public:
    State(ScreenShare screenShare);

    virtual ~State();

    virtual void setup();

    virtual void update(const Ogre::FrameEvent &evt);

    virtual bool keyPressed(const OgreBites::KeyboardEvent &evt);
    virtual bool mousePressed(const OgreBites::MouseButtonEvent &evt);
    virtual bool mouseMoved(const OgreBites::MouseMotionEvent &evt);
    virtual bool mouseReleased(const OgreBites::MouseButtonEvent& evt);
    virtual void buttonHit(OgreBites::Button *button);

    ScreenShare mScreenShare;
};
}
