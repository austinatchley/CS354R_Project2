#pragma once

#include <GameObjects/GenericObject.h>

#include <Physics/BulletContactCallback.h>

#include <Ogre.h>
#include <OgreSceneManager.h>

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

#include "BulletCollision/CollisionDispatch/btCollisionObject.h"

namespace Game {
class GameState;

class GameObject : public Util::GenericObject {
  public:
    GameObject(Ogre::SceneManager *scnMgr, ECS::EventManager *eventManager,
               btDiscreteDynamicsWorld *world,
               Ogre::SceneManager::PrefabType prefab,
               const Ogre::String &material, float scale);

    GameObject(Ogre::SceneManager *scnMgr, ECS::EventManager *eventManager,
               btDiscreteDynamicsWorld *world,
               const Ogre::String &meshName, const Ogre::String &material,
               float scale);

    // From GenericObject
    virtual void update(float dt) override;
    virtual void setTransform(const btTransform &newTransform) override;

    bool shouldUpdate();

    virtual void handleCollision();

    void addToGame(GameState *gameState);

  protected:
    GameObject(Ogre::SceneManager *scnMgr, ECS::EventManager *eventManager,
               btDiscreteDynamicsWorld *world,
               Ogre::Entity *entity, const Ogre::String &material, float scale);

    std::size_t mGameID;
    btDiscreteDynamicsWorld *mWorld;

    bool mUpdate;
};
}
