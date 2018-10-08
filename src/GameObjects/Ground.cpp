#include <GameObjects/Ground.h>

namespace Game {
Ground::Ground(Ogre::SceneManager *scnMgr, ECS::EventManager *eventManager,
               const Ogre::String &material = "Examples/SphereMappedRustySteel",
               float scale = 1.f)
    : GameObject(scnMgr, eventManager, Ogre::SceneManager::PT_PLANE, material,
                 scale) {
    // set to static
    mInertia.setZero();
    mMass = 0;
    mStatic = true;

    mShape = new btBoxShape(btVector3(1000, 1000, 0));

    mTransform.setIdentity();
}

// void Ground::handleCollision() {}
}
