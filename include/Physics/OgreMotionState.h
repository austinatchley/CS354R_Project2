#pragma once

#include <Ogre.h>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

namespace Physics {
class OgreMotionState
    : public btMotionState {
public:    
    OgreMotionState(Ogre::SceneNode* node)
        : mNode(node) {
        mTrans.setIdentity();
    }

    virtual ~OgreMotionState() {}

    inline virtual void getWorldTransform(btTransform& trans) const {
        trans = mTrans;
    }

    inline virtual void setWorldTransform(const btTransform& trans) {
        mTrans = trans;

        btQuaternion orientation = mTrans.getRotation();
        btVector3 position = mTrans.getOrigin();

        mNode->setPosition(
                Ogre::Vector3(
                    position.x(),
                    position.y(),
                    position.z()
               ));

        mNode->setOrientation(
            Ogre::Quaternion(
                orientation.w(),
                orientation.x(),
                orientation.y(),
                orientation.z()
            ));
    }

protected:
    Ogre::SceneNode* mNode;
    btTransform mTrans;
};
}
