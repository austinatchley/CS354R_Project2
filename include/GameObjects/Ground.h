#pragma once

#include <GameObjects/GameObject.h>

namespace Game {
class Ground : public GameObject {
  public:
    Ground(Ogre::SceneManager *scnMgr, ECS::EventManager *eventManager,
           const Ogre::String &material, float scale);

    ~Ground() {}

    // void handleCollision() override;
};
}
