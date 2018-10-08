#pragma once

#include <Ogre.h>
#include <OgreVector3.h>

#include "ECS/EventManager.h"

#include "Util/Events/EventSubscribers.h"
#include "Util/Events/Events.h"

#include "GameObject.h"

namespace Game {
class Paddle : public GameObject {
  public:
    Paddle(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager, const Ogre::String &material,
           float scale, const Ogre::Vector3& pos);

    ~Paddle() {}

    void handleCollision() override;
};
}
