#pragma once

#include <GameObjects/GenericObject.h>

#include <Physics/BulletContactCallback.h>

#include <Ogre.h>
#include <OgreSceneManager.h>

#include "btBulletDynamicsCommon.h"

namespace Game {
class GameState;

class GameObject : public Util::GenericObject {
  public:
    GameObject(Ogre::SceneManager *scnMgr,
               Ogre::SceneManager::PrefabType prefab,
               const Ogre::String &material, float scale);
        
    GameObject(Ogre::SceneManager *scnMgr, const Ogre::String &meshName,
               const Ogre::String &material, float scale);
 
    void addToGame(GameState* gameState);

    virtual void update(float dt);

  protected:
    GameObject(Ogre::SceneManager *scnMgr, Ogre::Entity *entity,
               const Ogre::String &material, float scale);
 
    std::size_t mGameID;
    btDiscreteDynamicsWorld *mWorld;
};
}
