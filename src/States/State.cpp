#include <States/State.h>

namespace Game {
State::State(ScreenShare screenShare = ScreenShare::Transparent)
    : mScreenShare(screenShare) {}

State::~State() {}

void State::setup() {}

void State::update(const Ogre::FrameEvent &evt) {}

bool State::keyPressed(const OgreBites::KeyboardEvent &evt) { return false; }
bool State::mousePressed(const OgreBites::MouseButtonEvent &evt) {
    return false;
}
bool State::mouseMoved(const OgreBites::MouseMotionEvent &evt) { return false; }
bool State::mouseReleased(const OgreBites::MouseButtonEvent& evt) { return false; }
void State::buttonHit(OgreBites::Button *button) {}
}
