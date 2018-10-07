#pragma once

#include <Ogre.h>
#include <OgreSceneManager.h>

#include "btBulletDynamicsCommon.h"

#include <Physics/BulletContactCallback.h>

#include "ECS/Entity.h"

#include "GenericObject.h"

namespace Game {
class GameObject : public Util::GenericObject {
  public:
    void addToGame(GameState* gameState);

    virtual void update(float dt);

  protected:
    GameState::GameID mGameID;
    btDiscreteDynamicsWorld *mWorld;
};
}
