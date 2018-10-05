#include "Ball.h"

namespace Game {
Ball::Ball(Ogre::SceneManager *scnMgr, 
           const Ogre::String &material = "Examples/SphereMappedRustySteel",
           float scale = 1.f,
           const Ogre::Vector3 &velocity = Ogre::Vector3::ZERO)
    : GameObject(scnMgr, Ogre::SceneManager::PT_SPHERE, material, scale)
    , mVelocity(velocity) {
}

const Ogre::Vector3 &Ball::getVelocity() { return mVelocity; }

void Ball::setVelocity(const Ogre::Vector3 &newVel) { mVelocity = newVel; }
} // namespace Game
