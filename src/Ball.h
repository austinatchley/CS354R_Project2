#pragma once

#include <vector>

#include <Ogre.h>

#include "ECS/EventManager.h"

#include "Util/GameObject.h"
#include "Util/Events/EventSubscribers.h"
#include "Util/Events/Events.h"

namespace Game {
class Ball : public Util::GameObject {
  public:
    Ball(Ogre::SceneManager *scnMgr, 
           const Ogre::String &material,
           float scale,
           const Ogre::Vector3 &velocity);

    ~Ball() {}

    const Ogre::Vector3 &getVelocity();
    void setVelocity(const Ogre::Vector3 &newVel);

  private:
    Ogre::Real mRadius;
    Ogre::Vector3 mVelocity;
};
}
