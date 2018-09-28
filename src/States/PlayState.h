#pragma once

#include <OgreInput.h>

#include "Util/GameState.h"

namespace Game {
// The game state where you actually play the game
// This should handle all game-specific logic
class PlayState : public Util::GameState {
  public:
    PlayState();
    virtual ~PlayState() {}

    void update() override;

    bool keyPressed(const OgreBites::KeyboardEvent &evt) override;
};
}
