#pragma once

#include <GameObjects/GameObject.h>

namespace Game {
class Ground : public GameObject {
  public:
    Ground(Ogre::SceneManager *scnMgr, ECS::EventManager *eventManager,
           btDiscreteDynamicsWorld *world, const Ogre::String &material,
           float scale);

    ~Ground() {}

    // void handleCollision() override;
};
}
