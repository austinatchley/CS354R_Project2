#include "Game.h"

#include "States/MenuState.h"
#include "Util/Util.h"

#include <limits>

using namespace Ogre;
using namespace OgreBites;

namespace Game {
Game::Game() : ApplicationContext("Project2") {}

Game::~Game() {
    for (auto* state : mStates) {
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
    if (mStates.empty()) {
        return false;
    }

    return mStates.back()->keyPressed(evt);
}

bool Game::mousePressed(const MouseButtonEvent &evt) {
    if (mStates.empty()) {
        return false;
    }

    return mStates.back()->mousePressed(evt);
}

bool Game::mouseMoved(const MouseMotionEvent &evt) {
    if (mStates.empty()) {
        return false;
    }

    return mStates.back()->mouseMoved(evt);
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent &evt) {
    if (mStates.empty()) {
        return false;
    }

    // Tell the EventManager to dispatch the events in the queue
    mEventManager->update();

    // Update the current event
    mStates.back()->update(evt);

    return true;
}

void Game::pushState(Util::State *state) {
    mStates.push_back(state);

    state->setup();
}

void Game::popState() {
    if (mStates.empty()) {
        throw Ogre::Exception(
            Ogre::Exception::ExceptionCodes::ERR_INVALID_STATE,
            "The state stack is invalid", "");
    }

    Util::State* state = mStates.back();
    mStates.pop_back();

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
