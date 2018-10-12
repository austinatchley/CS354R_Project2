#pragma once

#include <iostream>

#include <Util/Util.h>

#include <Ogre.h>

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

namespace Physics {
class OgreMotionState : public btMotionState {
  public:
    OgreMotionState(const btTransform &trans, Ogre::SceneNode *node)
        : mNode(node), mTrans(trans) {}

    virtual ~OgreMotionState() {}

    virtual void getWorldTransform(btTransform &trans) const {
        trans = mTrans;
    }

    virtual void setWorldTransform(const btTransform &trans) {
        if (!mNode) {
            return;
        }

        std::cout << "setWorldTransform" << std::endl;

        mTrans = trans;

        btQuaternion orientation = mTrans.getRotation();
        btVector3 position = mTrans.getOrigin();

        mNode->setPosition(
            Util::makeOgreVector3(position));

        mNode->setOrientation(Ogre::Quaternion(orientation.w(), orientation.x(),
                                               orientation.y(),
                                               orientation.z()));
    }

    // Use the OgreKinematicMotionState instead if you are trying to use this
    virtual void setKinematicTransform(btTransform &trans) { assert(false); }

  protected:
    Ogre::SceneNode *mNode;
    btTransform mTrans;
};
}
