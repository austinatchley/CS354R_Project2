#include <GameObjects/GenericObject.h>

namespace Util {
GenericObject::GenericObject(
    Ogre::SceneNode *parent, ECS::EventManager *eventManager,
    Ogre::Entity *entity, const Ogre::String &material, float scale = 100.f,
    const btTransform &transform = btTransform::getIdentity())
    : mMaterial(material), mEventManager(eventManager), mKinematic(false),
      mStatic(false), mTransform(transform) {
    entity->setCastShadows(true);

    entity->setMaterialName(material);

    if (!parent) {
        throw Ogre::Exception(
            Ogre::Exception::ExceptionCodes::ERR_INVALID_STATE,
            "Parent is nullptr", "");
    }

    mNode = parent->createChildSceneNode();

    if (!mNode) {
        throw Ogre::Exception(
            Ogre::Exception::ExceptionCodes::ERR_INVALID_STATE,
            "Node is nullptr", "");
    }

    mNode->setScale(scale / 100.f, scale / 100.f, scale / 100.f);

    mNode->attachObject(entity);

    mLastTime = 0.f;
}

GenericObject::~GenericObject() {}

void GenericObject::update(float dt) {}

void GenericObject::setTransform(const btTransform &newTransform) {}

Ogre::SceneNode *GenericObject::getNode() { return mNode; }
}
