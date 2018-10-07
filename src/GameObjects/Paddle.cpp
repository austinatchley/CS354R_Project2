#include <GameObjects/Paddle.h>

namespace Game {
Paddle::Paddle(Ogre::SceneManager *scnMgr,
               const Ogre::String &material = "Examples/SphereMappedRustySteel",
               float scale = 1.f)
    : GameObject(scnMgr, Ogre::SceneManager::PT_PLANE, material, scale) {}

} // namespace Game
