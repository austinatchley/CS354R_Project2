#pragma once

#include <Ogre.h>
#include <OgreSceneManager.h>

#include <Physics/BulletContactCallback.h>

#include "ECS/Entity.h"

#include "States/State.h"

namespace Util {
class GenericObject {
  public:
    GenericObject(Ogre::SceneManager *scnMgr,
               Ogre::SceneManager::PrefabType prefab,
               const Ogre::String &material, float scale = 100.f) {
        Ogre::Entity *entity = scnMgr->createEntity(prefab);

        GenericObject(scnMgr, entity, material, scale);
    }

    GenericObject(Ogre::SceneManager *scnMgr, const Ogre::String &meshName,
               const Ogre::String &material, float scale = 100.f) {
        Ogre::Entity *entity = scnMgr->createEntity(meshName);

        GenericObject(scnMgr, entity, material, scale);
    }

    ~GenericObject() {}

    virtual void update(float dt) {}

    Ogre::SceneNode *getNode() { return mNode; }

  protected:
    GenericObject(Ogre::SceneManager *scnMgr, Ogre::Entity *entity,
               const Ogre::String &material, float scale = 100.f)
        : mMaterial(material) {
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

    Ogre::SceneNode *mNode;
    Ogre::Entity *mEntity;

    Ogre::SceneManager* mScnMgr;

    Ogre::String mMaterial;
    Ogre::String mName;

    btCollisionShape* mShape;
    btMotionState* mMotionState;
    btRigidBody* mBody;
    btTransform mTransform;
    btVector3 mInertia;

    btScalar mMass;
    btScalar mRestitution;
    btScalar mFriction;

    bool mKinematic;
    bool mNeedsUpdates;

    float mLastTime;

    Physics::CollisionContext* mContext;
    Physics::BulletContactCallback* mCCallback;
};
}
