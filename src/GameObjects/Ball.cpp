#include <GameObjects/Ball.h>

#include <Util/Util.h>

namespace Game {
Ball::Ball(Ogre::SceneManager *scnMgr, ECS::EventManager *eventManager,
           btDiscreteDynamicsWorld* world,
           const Ogre::String &material = "Examples/SphereMappedRustySteel",
           float scale = 1.f,
           const btTransform& trans = btTransform::getIdentity())
    : GameObject(scnMgr, eventManager, world, Ogre::SceneManager::PT_SPHERE, material,
                 scale) {
    // set mass, motionstate, shape, and inertia before GameObject::addToGame
    // initializes our rigidbody
    mShape = new btSphereShape(btScalar(scale));

    mTransform = trans;

    mMass = 2 * Ogre::Math::PI / 3 * Ogre::Math::Pow(scale, 3);

    mInertia.setZero();
}

Ball::~Ball() {}

void Ball::handleCollision() {
    // Implement the ball specific collision handler here

    mEventManager->event<Util::PlaySoundEvent>(
        new Util::PlaySoundEvent(Util::Sound::Ball));
}
} // namespace Game
