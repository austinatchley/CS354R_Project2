#include <GameObjects/GenericObject.h>

namespace Util {
GenericObject::GenericObject(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager,
           Ogre::SceneManager::PrefabType prefab,
           const Ogre::String &material, float scale = 100.f) {
    Ogre::Entity *entity = scnMgr->createEntity(prefab);

    GenericObject(scnMgr, eventManager, entity, material, scale);
}

GenericObject::GenericObject(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager, const Ogre::String &meshName,
           const Ogre::String &material, float scale = 100.f) {
    Ogre::Entity *entity = scnMgr->createEntity(meshName);

    GenericObject(scnMgr, eventManager, entity, material, scale);
}

GenericObject::~GenericObject() {}

void GenericObject::update(float dt) {}

Ogre::SceneNode *GenericObject::getNode() { return mNode; }

GenericObject::GenericObject(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager, Ogre::Entity *entity,
           const Ogre::String &material, float scale = 100.f)
    : mMaterial(material) , mEventManager(eventManager) {
    entity->setCastShadows(true);

    entity->setMaterialName(material);

    if (!scnMgr) {
        throw Ogre::Exception(
            Ogre::Exception::ExceptionCodes::ERR_INVALID_STATE,
            "Scene Manager is nullptr", "");
    }

    mNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    if (!mNode) {
        throw Ogre::Exception(
            Ogre::Exception::ExceptionCodes::ERR_INVALID_STATE,
            "Node is nullptr", "");
    }

    mNode->setScale(scale / 100.f, scale / 100.f, scale / 100.f);

    mNode->attachObject(entity);

    mLastTime = 0.f;
}
}
