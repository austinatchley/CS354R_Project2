#include "MenuState.h"

namespace Game {
MenuState::MenuState() : GameState(Util::ScreenShare::Shared) {}

void MenuState::update() {}

bool MenuState::keyPressed(const OgreBites::KeyboardEvent &evt) {
    return false;
}
}
