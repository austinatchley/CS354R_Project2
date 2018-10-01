#include "Game.h"

#include "Util/Util.h"

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
    mEventManager->connect<PlaySoundEvent>(mSoundManager);

    mGameStates.push_back(MenuState());
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

    auto backIt = mGameStates.end() - 1;

    while (backIt->mScreenShare != Util::ScreenShare::Full &&
            backIt != mGameStates.begin())
    {
        --backIt;
    }

    if (backIt == mGameStates.begin())
    {
        throw Ogre::Exception(ERR_INVALID_STATE, "The state stack is invalid", "");
    }

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
