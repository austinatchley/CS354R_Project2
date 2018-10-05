#pragma once

#include <cstdint>

#include <OgreInput.h>

namespace Util {
enum class ScreenShare : std::size_t { Transparent = 0, Shared, Full };

class State {
  public:
    State(ScreenShare screenShare = ScreenShare::Transparent)
        : mScreenShare(screenShare) {}

    virtual ~State() {}

    virtual void setup() {}

    virtual void update(const Ogre::FrameEvent &evt) {}

    virtual bool keyPressed(const OgreBites::KeyboardEvent &evt) {
        return false;
    }
    virtual bool mousePressed(const OgreBites::MouseButtonEvent &evt) {
        return false;
    }
    virtual bool mouseMoved(const OgreBites::MouseMotionEvent &evt) {
        return false;
    }

    ScreenShare mScreenShare;
};
}
