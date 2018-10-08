#include <GameObjects/Ball.h>

#include <Util/Util.h>
#include <Util/Events/Events.h>

namespace Game {
Ball::Ball(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager,
           const Ogre::String &material = "Examples/SphereMappedRustySteel",
           float scale = 1.f)
    : GameObject(scnMgr, eventManager, Ogre::SceneManager::PT_SPHERE, material, scale)
      {
      	mShape = new btSphereShape(btScalar(1.0));
      	
      	mTransform.setIdentity();
      	mTransform.setOrigin(btVector3(playerPos.x, playerPos.y, playerPos.z));

      	// set mass, motionstate, shape, and inertia before GameObject::addToGame

      	// set mass = constant density
      	mMass = 2 * Ogre::Math::PI / 3 * Ogre::Math::Pow(scale, 3);

      	mInertia = 1;

      	mMotionState = btDefaultMotionState(mTransform);

      }

Ball::~Ball() {}

void Ball::handleCollision() {
    // Implement the ball specific collision handler here

    mEventManager->event<Util::PlaySoundEvent>(new Util::PlaySoundEvent(Util::Sound::Ball));
}
} // namespace Game
