#pragma once

#include <OgreInput.h>

#include "Util/GameState.h"

namespace Game {
// The game state where you interact with the menu
class MenuState : public Util::GameState {
  public:
    MenuState();
    virtual ~MenuState() {}

    void update(const Ogre::FrameEvent& evt) override;

    bool keyPressed(const OgreBites::KeyboardEvent &evt) override;
};
}
