#include <GameObjects/Ball.h>

#include <Util/Util.h>
#include <Util/Events/Events.h>

namespace Game {
Ball::Ball(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager,
           const Ogre::String &material = "Examples/SphereMappedRustySteel",
           float scale = 1.f)
    : GameObject(scnMgr, eventManager, Ogre::SceneManager::PT_SPHERE, material, scale)
      {}

Ball::~Ball() {}

void Ball::handleCollision() {
    // Implement the ball specific collision handler here

    mEventManager->event<Util::PlaySoundEvent>(new Util::PlaySoundEvent(Util::Sound::Ball));
}
} // namespace Game
