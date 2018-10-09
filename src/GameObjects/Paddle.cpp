#include <GameObjects/Paddle.h>

namespace Game {
Paddle::Paddle(Ogre::SceneManager *scnMgr, ECS::EventManager *eventManager,
               btDiscreteDynamicsWorld* world,
               const Ogre::String &material = "Examples/SphereMappedRustySteel",
               float scale = 1.f,
               const btTransform& trans = btTransform::getIdentity())
    : GameObject(scnMgr, eventManager, world, Ogre::SceneManager::PT_PLANE, material,
                 scale) {
    mShape = new btBoxShape(btVector3(1, 3, 1));

    mTransform = trans;

    mMass = 0.f;
    mInertia.setZero();

    mKinematic = true;
}

void Paddle::handleCollision() {
    // if collide with ball, bounce it
}
} // namespace Game
