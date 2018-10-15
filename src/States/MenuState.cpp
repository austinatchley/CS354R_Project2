#include <States/MenuState.h>

namespace Game
{
MenuState::MenuState() : State(ScreenShare::Shared)
{
}

void MenuState::setup()
{
}

void MenuState::update(const Ogre::FrameEvent& evt)
{
}

bool MenuState::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    return false;
}

bool MenuState::mousePressed(const OgreBites::MouseButtonEvent& evt)
{
    return false;
}

bool MenuState::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
    return false;
}
} // namespace Game
