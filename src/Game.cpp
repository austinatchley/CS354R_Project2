#include "Game.h"

#include "Util/Util.h"
#include "States/MenuState.h"

#include <limits>

using namespace Ogre;
using namespace OgreBites;

namespace Game {
Game::Game() : ApplicationContext("Project2") {}

Game::~Game() {}

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

    //mGameStates.emplace_back(MenuState());
}

bool Game::keyPressed(const KeyboardEvent &evt) {
    if (mGameStates.empty())
    {
        return false;
    }

    return mGameStates.back().keyPressed(evt);
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent &evt) {
    if (mGameStates.empty())
    {
        return false;
    }

    // Tell the EventManager to dispatch the events in the queue
    mEventManager->update();

    // Traverse the stack of states and update the appropriate ones
    auto backIt = mGameStates.end() - 1;
    while (backIt->mScreenShare != Util::ScreenShare::Full && // stop on the first Full
            backIt != mGameStates.begin())
    {
        --backIt;
    }

    // If there are no Full states, we are in an invalid state
    if (backIt == mGameStates.begin())
    {
        throw Ogre::Exception(Ogre::Exception::ExceptionCodes::ERR_INVALID_STATE, "The state stack is invalid", "");
    }

    // Update the appropriate states from the bottom up
    while (backIt != mGameStates.end())
    {
        backIt->update(evt);
        ++backIt;
    }

    return true;
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
