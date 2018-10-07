#include <GameObjects/Paddle.h>

namespace Game {
Paddle::Paddle(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager,
               const Ogre::String &material = "Examples/SphereMappedRustySteel",
               float scale = 1.f)
    : GameObject(scnMgr, eventManager, Ogre::SceneManager::PT_PLANE, material, scale) {}

void Paddle::handleCollision() {

}
} // namespace Game
