#pragma once

#include <Physics/BulletContactCallback.h>

#include <ECS/EventManager.h>

#include <Ogre.h>
#include <OgreSceneManager.h>

namespace Util {
class GenericObject {
  public:
    GenericObject(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager,
               Ogre::SceneManager::PrefabType prefab,
               const Ogre::String &material, float scale);
        
    GenericObject(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager, const Ogre::String &meshName,
               const Ogre::String &material, float scale);
        
    ~GenericObject();

    virtual void update(float dt);

    Ogre::SceneNode *getNode();

  protected:
    GenericObject(Ogre::SceneManager *scnMgr, ECS::EventManager* eventManager, Ogre::Entity *entity,
               const Ogre::String &material, float scale);
        
    Ogre::SceneNode *mNode;
    Ogre::Entity *mEntity;

    Ogre::SceneManager* mScnMgr;

    Ogre::String mMaterial;
    Ogre::String mName;

    ECS::EventManager* mEventManager;

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
