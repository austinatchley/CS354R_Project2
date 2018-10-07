#pragma once

#include <GameObjects/GenericObject.h>

#include <Physics/BulletContactCallback.h>

#include <Ogre.h>
#include <OgreSceneManager.h>

#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

#include "BulletCollision/CollisionDispatch/btCollisionObject.h"

namespace Game {
class GameState;

class GameObject : public Util::GenericObject {
  public:
    GameObject(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager,
               Ogre::SceneManager::PrefabType prefab,
               const Ogre::String &material, float scale);
        
    GameObject(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager, const Ogre::String &meshName,
               const Ogre::String &material, float scale);
 
    void addToGame(GameState* gameState);

    virtual void update(float dt);
    virtual bool shouldUpdate();

    virtual void handleCollision();

  protected:
    GameObject(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager, Ogre::Entity *entity,
               const Ogre::String &material, float scale);
 
    std::size_t mGameID;
    btDiscreteDynamicsWorld *mWorld;

    bool mUpdate;
};
}
