#include "Game.h"

#include "States/MenuState.h"
#include "Util/Util.h"

#include <limits>

using namespace Ogre;
using namespace OgreBites;

namespace Game {
Game::Game() : ApplicationContext("Project2") {}

Game::~Game() {
    for (auto* state : mGameStates) {
        delete state;
    }
}

void Game::setup() {
    //////////////////////////////////////////////////////////////////
    // Application Setup
    ApplicationContext::setup();
    addInputListener(this);

    //////////////////////////////////////////////////////////////////
    // Event Manager
    mEventManager.reset(new ECS::EventManager(std::allocator<void>()));

    //////////////////////////////////////////////////////////////////
    // Sound Manager
    mSoundManager = new SoundManager();
    mEventManager->connect<Util::PlaySoundEvent>(mSoundManager);

    pushState(new PlayState(mEventManager.get(), mRoot, getRenderWindow()));
}

bool Game::keyPressed(const KeyboardEvent &evt) {
    if (mGameStates.empty()) {
        return false;
    }

    return mGameStates.back()->keyPressed(evt);
}

bool Game::mousePressed(const MouseButtonEvent &evt) {
    if (mGameStates.empty()) {
        return false;
    }

    return mGameStates.back()->mousePressed(evt);
}

bool Game::mouseMoved(const MouseMotionEvent &evt) {
    if (mGameStates.empty()) {
        return false;
    }

    return mGameStates.back()->mouseMoved(evt);
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent &evt) {
    if (mGameStates.empty()) {
        return false;
    }

    // Tell the EventManager to dispatch the events in the queue
    mEventManager->update();

    // Update the current event
    mGameStates.back()->update(evt);

    return true;
}

void Game::pushState(Util::GameState *state) {
    mGameStates.push_back(state);

    state->setup();
}

void Game::popState() {
    if (mGameStates.empty()) {
        throw Ogre::Exception(
            Ogre::Exception::ExceptionCodes::ERR_INVALID_STATE,
            "The state stack is invalid", "");
    }

    Util::GameState* state = mGameStates.back();
    mGameStates.pop_back();

    delete state;
}

} // namespace Game

int main(int argc, char **argv) {
    try {
        Game::Game app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    } catch (const std::exception &e) {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
