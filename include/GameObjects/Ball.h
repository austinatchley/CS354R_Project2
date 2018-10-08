#pragma once

#include <OgreVector3.h>
#include <Ogre.h>

#include <ECS/EventManager.h>

#include <Util/Events/EventSubscribers.h>
#include <Util/Events/Events.h>

#include "GameObject.h"

namespace Game {
class Ball : public GameObject {
  public:
    Ball(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager, const Ogre::String &material, float scale, const Ogre::Vector3& pos);

    ~Ball();

    void handleCollision() override;

  private:
    // member vars
};
}
