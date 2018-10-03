#include "Ball.h"

namespace Game {
Ball::Ball(Ogre::SceneManager *scnMgr, 
           const Ogre::String &material = "Examples/SphereMappedRustySteel",
           float scale = 1.f,
           const Ogre::Vector3 &velocity = Ogre::Vector3::ZERO)
    : GameObject(scnMgr, Ogre::SceneManager::PT_SPHERE, material, scale)
    , mVelocity(velocity) {}

const Ogre::Vector3 &Ball::getVelocity() { return mVelocity; }

void Ball::setVelocity(const Ogre::Vector3 &newVel) { mVelocity = newVel; }

void Ball::move(const std::vector<Ogre::Plane> &walls,
                ECS::EventManager *eventManager, const Ogre::Real dt) {
    using namespace Ogre;

    const auto &prevPos = mNode->getPosition();

    Vector3 newVel = mVelocity;

    Vector3 deltaPos = Vector3::ZERO;

    // Check each wall to see if our ball has collided with it
    for (int j = 0; j < walls.size(); ++j) {
        if (walls[j].getDistance(prevPos) <= mRadius &&
            mVelocity.dotProduct(walls[j].normal) < 0) {
            const auto &norm = walls[j].normal;

            // Use the plane reflection formula
            newVel -= 2 * norm * (norm.dotProduct(mVelocity));

            // Lift the ball off the plane slightly so it doesn't get stuck
            deltaPos += norm * std::numeric_limits<float>::epsilon();

            // Play the wall hit sound
            eventManager->event<Util::PlaySoundEvent>(
                new Util::PlaySoundEvent(Util::Sound::Ball));
        }
    }

    deltaPos += mVelocity * dt;
    const Vector3 newPos = prevPos + deltaPos;

    mVelocity = newVel;
    mNode->setPosition(newPos);
}
} // namespace Game
