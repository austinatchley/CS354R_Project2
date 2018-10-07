#include "GameObjects/GameObject.h"

namespace Game {
void GameObject::addToGame(GameState* gameState) {
    //updateTransform();

    if (mMass != 0.f) {
        mShape->calculateLocalInertia(mMass, mInertia);
    }

    btRigidBody::btRigidBodyConstructionInfo rbInfo(mMass, mMotionState, mShape, mInertia);
    rbInfo.m_restitution = mRestitution;
    rbInfo.m_friction = mFriction;

    mBody = new btRigidBody(rbInfo);
    mBody->setUserPointer(this);

    if (mKinematic) {
        mBody->setCollisionFlags(mBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
        mBody->setActivationState(DISABLE_DEACTIVATION);
    }

    mGameID = gameState->addObject(this);
}

void GameObject::update(float dt) {
    mLastTime += dt;

    mWorld->contactTest(mBody, *mCCallback);

    if (mContext->hit &&
            (mContext->velNormal > 2.f || mContext->velNormal < -2.f) &&
            (mLastTime > -0.5 ||
            (mContext->lastBody != mContext->body && mLastTime > 0.1)))
    {
        // Handle the collision here
        mLastTime = 0.f;
    }

    mContext->hit = false;
}
}
