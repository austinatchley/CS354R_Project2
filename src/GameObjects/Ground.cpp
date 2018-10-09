#include <GameObjects/Ground.h>

namespace Game {
Ground::Ground(Ogre::SceneManager *scnMgr, ECS::EventManager *eventManager,
               btDiscreteDynamicsWorld* world,
               const Ogre::String &material = "Examples/SphereMappedRustySteel",
               float scale = 1.f)
    : GameObject(scnMgr, eventManager, world, Ogre::SceneManager::PT_PLANE, material,
                 scale) {
    // set to static
    mMass = 0;
    mStatic = true;
}

// void Ground::handleCollision() {}
}
