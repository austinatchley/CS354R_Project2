#pragma once

#include <Ogre.h>
#include <OgreSceneManager.h>

#include "ECS/Entity.h"

namespace Util {
class GameObject {
  public:
    GameObject(Ogre::SceneManager* scnMgr, Ogre::SceneManager::PrefabType prefab, const Ogre::String& material, float scale = 100.f)
    {
        Ogre::Entity *entity =
            scnMgr->createEntity(prefab);

        GameObject(scnMgr, entity, material, scale);
    }

    GameObject(Ogre::SceneManager* scnMgr, const Ogre::String& meshName, const Ogre::String& material, float scale = 100.f)
    {
        Ogre::Entity *entity =
            scnMgr->createEntity(meshName);

        GameObject(scnMgr, entity, material, scale);
    }

    GameObject(Ogre::SceneManager *scnMgr, Ogre::Entity* entity, const Ogre::String& material, float scale = 100.f)
        : mMaterial(material) {
        entity->setCastShadows(true);

        if (!material.empty()) {
            entity->setMaterialName(material);
        }

        mNode = scnMgr->getRootSceneNode()->createChildSceneNode();

        mNode->setScale(scale / 100.f, scale / 100.f, scale / 100.f);

        mNode->attachObject(entity);
    }

    ~GameObject() {}

    Ogre::SceneNode *getNode() { return mNode; }

  protected:
    Ogre::SceneNode *mNode;
    Ogre::String mMaterial;
};
}