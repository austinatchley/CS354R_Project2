#pragma once

#include <Physics/BulletContactCallback.h>
#include <Physics/OgreKinematicMotionState.h>
#include <Physics/OgreMotionState.h>

#include <ECS/EventManager.h>

#include <Ogre.h>
#include <OgreSceneManager.h>

namespace Util {
class GenericObject {
  public:
    GenericObject(Ogre::SceneManager *scnMgr, ECS::EventManager *eventManager,
                  Ogre::SceneManager::PrefabType prefab,
                  const Ogre::String &material, float scale,
                  const btTransform &transform);

    GenericObject(Ogre::SceneManager *scnMgr, ECS::EventManager *eventManager,
                  const Ogre::String &meshName, const Ogre::String &material,
                  float scale, const btTransform &transform);

    ~GenericObject();

    virtual void update(float dt);

    virtual void setTransform(const btTransform &newTransform);

    Ogre::SceneNode *getNode();

  protected:
    GenericObject(Ogre::SceneManager *scnMgr, ECS::EventManager *eventManager,
                  Ogre::Entity *entity, const Ogre::String &material,
                  float scale, const btTransform &transform);

    Ogre::SceneNode *mNode;
    Ogre::Entity *mEntity;

    Ogre::SceneManager *mScnMgr;

    Ogre::String mMaterial;
    Ogre::String mName;

    ECS::EventManager *mEventManager;

    btCollisionShape *mShape;
    Physics::OgreMotionState *mMotionState;
    btRigidBody *mBody;
    btTransform mTransform;
    btVector3 mInertia;

    btScalar mMass;
    btScalar mRestitution;
    btScalar mFriction;

    bool mKinematic;
    bool mStatic;

    float mLastTime;

    Physics::CollisionContext *mContext;
    Physics::BulletContactCallback *mCCallback;
};
}
