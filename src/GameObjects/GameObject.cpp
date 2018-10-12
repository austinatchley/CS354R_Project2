#include "GameObjects/GameObject.h"

#include <States/GameState.h>

namespace Game {
GameObject::GameObject(
    Ogre::SceneNode *parent, ECS::EventManager *eventManager,
    btDiscreteDynamicsWorld *world, Ogre::Entity *entity,
    const Ogre::String &material, float scale = 100.f,
    const btTransform &transform = btTransform::getIdentity())
    : GenericObject(parent, eventManager, entity, material, scale, transform),
      mWorld(world) {}

void GameObject::addToGame(GameState *gameState) {
    if (mMass != 0.f) {
        mShape->calculateLocalInertia(mMass, mInertia);
    }

    if (mKinematic) {
        mMotionState = new Physics::OgreKinematicMotionState(mTransform, mNode);
    } else {
        mMotionState = new Physics::OgreMotionState(mTransform, mNode);

        if (mStatic) {
            updateTransform();
        }
    }

    btRigidBody::btRigidBodyConstructionInfo rbInfo(mMass, mMotionState, mShape,
                                                    mInertia);
    rbInfo.m_restitution = mRestitution;
    rbInfo.m_friction = mFriction;

    mBody = new btRigidBody(rbInfo);
    mBody->setUserPointer(this);

    if (mKinematic) {
        mBody->setCollisionFlags(mBody->getCollisionFlags() |
                                 btCollisionObject::CF_KINEMATIC_OBJECT);

        mBody->setActivationState(DISABLE_DEACTIVATION);
    }

    mContext = new Physics::CollisionContext();
    mCCallback = new Physics::BulletContactCallback(*mBody, *mContext);

    mWorld->addRigidBody(mBody);

    mGameID = gameState->addObject(this);
}

void GameObject::update(float dt) {
    if (!mWorld) {
        return;
    }

    mLastTime += dt;

    mWorld->contactTest(mBody, *mCCallback);

    if (mContext->hit &&
        (mContext->velNormal > 2.f || mContext->velNormal < -2.f) &&
        (mLastTime > -0.5 ||
         (mContext->lastBody != mContext->body && mLastTime > 0.1))) {

        // The derived GameObject class should implement its own in
        // overridden handleCollision()

        this->handleCollision();
        mLastTime = 0.f;
    }

    //updateTransform(); 
    mContext->hit = false;
}

void GameObject::handleCollision() {}

void GameObject::setTransform(const btTransform &newTransform) {
    mTransform = newTransform;

    updateTransform(); 
}

void GameObject::updateTransform() {
    if (mKinematic) {
        mMotionState->setKinematicTransform(mTransform);
    }
    else {
        mMotionState->setWorldTransform(mTransform);
    }
}

void GameObject::applyImpulse(const btVector3& impulse) {
    mBody->applyCentralImpulse(impulse);
}
}
