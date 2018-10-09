#include <GameObjects/Ball.h>

#include <Util/Util.h>

namespace Game {
Ball::Ball(Ogre::SceneManager *scnMgr, ECS::EventManager *eventManager,
           btDiscreteDynamicsWorld *world,
           const Ogre::String &material = "Examples/SphereMappedRustySteel",
           float scale = 1.f,
           const btTransform &trans = btTransform::getIdentity())
    : GameObject(scnMgr, eventManager, world, Ogre::SceneManager::PT_SPHERE,
                 material, scale, trans) {
    // set mass, motionstate, shape, and inertia before GameObject::addToGame
    // initializes our rigidbody
    mShape = new btSphereShape(btScalar(scale));

    mMass = 2 * Ogre::Math::PI / 3 * Ogre::Math::Pow(scale, 3);

    mInertia = btVector3(1,1,1);
}

Ball::~Ball() {}

void Ball::handleCollision() {
    // Implement the ball specific collision handler here
    mEventManager->event<Util::PlaySoundEvent>(
        new Util::PlaySoundEvent(Util::Sound::Ball));

    //mBody.applyCentralImpulse(btVector3(Ogre));
}
} // namespace Game
