#pragma once

#include <vector>

#include <Ogre.h>

#include <ECS/EventManager.h>

#include <Util/Events/EventSubscribers.h>
#include <Util/Events/Events.h>

#include "GameObject.h"

namespace Game {
class Ball : public GameObject {
  public:
    Ball(Ogre::SceneManager *scnMgr, const Ogre::String &material, float scale);

    ~Ball();

  private:
    // member vars
};
}
