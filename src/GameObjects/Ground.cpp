#include <GameObjects/Ground.h>

namespace Game {
Ground::Ground(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager,
           const Ogre::String &material = "Examples/SphereMappedRustySteel",
           float scale = 1.f)
    : GameObject(scnMgr, eventManager, Ogre::SceneManager::PT_PLANE, material, scale)
      {
      	// set to static
      	mMass = 0;
      	mKinematic = false;
      }

Ground::~Ground() {}

//void Ground::handleCollision() {}
}