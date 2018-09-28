#include "PlayState.h"

namespace Game {
PlayState::PlayState() : GameState(Util::ScreenShare::Full) {}

void PlayState::update() {}

bool PlayState::keyPressed(const OgreBites::KeyboardEvent &evt) {
    return false;
}
}
