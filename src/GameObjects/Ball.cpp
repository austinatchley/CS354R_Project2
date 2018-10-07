#include <GameObjects/Ball.h>

namespace Game {
Ball::Ball(Ogre::SceneManager *scnMgr,
           const Ogre::String &material = "Examples/SphereMappedRustySteel",
           float scale = 1.f)
    : GameObject(scnMgr, Ogre::SceneManager::PT_SPHERE, material, scale)
      {}

Ball::~Ball() {}
} // namespace Game
